#!/usr/bin/env bash
# Build a self-contained REDRIVER2 AppImage with the game data baked in.
#
# usage: ./build-appimage.sh CD1.cue|CD1.bin CD2.cue|CD2.bin [OUTPUT.AppImage]
#
# The disc images are only read here; their content never enters git or the
# Nix store. Everything else (compiler, libraries, Mesa, Java, squashfs) comes
# from flake.nix.
set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

if [ $# -lt 2 ]; then
	echo "usage: $0 CD1.cue|CD1.bin CD2.cue|CD2.bin [OUTPUT.AppImage]" >&2
	exit 1
fi

# resolve a .cue (single BINARY track) or .bin argument to an absolute .bin path
disc_bin() {
	local arg dir file
	arg=$(realpath "$1")
	case "${arg,,}" in
	*.cue)
		dir=$(dirname "$arg")
		file=$(sed -n 's/^[[:space:]]*FILE[[:space:]]*"\(.*\)".*/\1/p' "$arg" | head -n1)
		[ -n "$file" ] || { echo "no FILE entry in $arg" >&2; exit 1; }
		echo "$dir/$file" ;;
	*) echo "$arg" ;;
	esac
}

CD1=$(disc_bin "$1")
CD2=$(disc_bin "$2")
OUT=$(realpath -m "${3:-$ROOT/REDRIVER2-x86_64.AppImage}")
for f in "$CD1" "$CD2"; do
	[ -f "$f" ] || { echo "missing disc image: $f" >&2; exit 1; }
done

BUILD="$ROOT/build/appimage"
APPDIR="$BUILD/AppDir"
WORK="$BUILD/work"

cd "$ROOT"
git submodule update --init

echo "==> Building game, AppDir and tools with Nix"
APPDIR_SRC=$(nix build --no-link --print-out-paths .#appdir)
RUNTIME=$(nix build --no-link --print-out-paths .#appimage-runtime)
TOOLS=$(nix build --no-link --print-out-paths .#tools)
export PATH="$TOOLS/bin:$PATH"

rm -rf "$BUILD"
mkdir -p "$WORK"
cp -a "$APPDIR_SRC" "$APPDIR"
chmod -R u+w "$APPDIR"
DATA="$APPDIR/usr/share/redriver2"

echo "==> Extracting disc file systems"
python3 -I "$ROOT/appimage/extract_iso.py" "$CD1" "$DATA"
python3 -I "$ROOT/appimage/extract_iso.py" "$CD2" "$DATA"

echo "==> Converting FMV and XA audio (jpsxdec, this takes a while)"
JPSXDEC=(java -Djava.awt.headless=true -jar "$ROOT/data/install/jpsxdec.jar")
n=0
for cd in "$CD1" "$CD2"; do
	n=$((n + 1))
	idx="$WORK/cd$n.idx"
	(cd "$WORK" && "${JPSXDEC[@]}" -f "$cd" -x "$idx" > "$WORK/cd$n-index.log")
	# same settings as data/install/conv.sh; output lands in ./DRIVER2/...
	(cd "$DATA" &&
		"${JPSXDEC[@]}" -x "$idx" -a video -quality psx -vf avi:mjpg -up Lanczos3 > "$WORK/cd$n-video.log" &&
		"${JPSXDEC[@]}" -x "$idx" -a audio -quality psx -af wav > "$WORK/cd$n-audio.log")
done
rm -f "$DATA"/*.log # jpsxdec writes its logs to the working directory

echo "==> Adding REDRIVER2 data (overrides disc files)"
cp -a "$ROOT/data/DRIVER2/." "$DATA/DRIVER2/"

for f in LEVELS/CHICAGO.LEV 'FMV/0/RENDER0.STR[0].avi' 'XA/XABNK01.XA[0].wav'; do
	[ -f "$DATA/DRIVER2/$f" ] || { echo "conversion incomplete, missing DRIVER2/$f (see $WORK)" >&2; exit 1; }
done

echo "==> Packing AppImage"
mksquashfs "$APPDIR" "$WORK/image.squashfs" -root-owned -noappend -comp zstd -Xcompression-level 19 -quiet
cat "$RUNTIME" "$WORK/image.squashfs" > "$OUT"
chmod +x "$OUT"
rm -rf "$BUILD"

echo "==> Done: $OUT ($(du -h "$OUT" | cut -f1))"
