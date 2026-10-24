# REDRIVER2 AppImage

A single, self-contained `REDRIVER2-x86_64.AppImage` for any x86_64 Linux system (made with the Steam Deck in mind).
The game data from your own Driver 2 discs is baked into the image. It needs no disc images, Java, SDL or other system libraries at runtime.

## Building

Requirements: [Nix](https://nixos.org) with flakes enabled, and both Driver 2 discs dumped as BIN/CUE (MODE2/2352).
Any [supported version](https://github.com/OpenDriver2/REDRIVER2/wiki/Installation-instructions#game-version-information) works.
The build targets NTSC (`GAME_REGION=NTSC_VERSION`, the premake default).

```sh
./build-appimage.sh "path/to/Driver 2 (Disc 1).cue" "path/to/Driver 2 (Disc 2).cue"
# -> ./REDRIVER2-x86_64.AppImage
```

What it does:

1. `nix build .#appdir` builds the game (`flake.nix`, premake 5.0.0-beta1 + gmake, `release_x64`). It bundles the binary with its complete library closure, glibc's loader and Mesa (`appimage/bundle_libs.py`).
2. It extracts the `DRIVER2` file tree from both discs (`appimage/extract_iso.py`).
3. It converts FMVs and XA audio with jpsxdec, using the same settings as `data/install/conv.sh`.
4. It overlays the repository's `data/DRIVER2`, then packs everything as squashfs behind the static AppImage type2 runtime.

The disc content never enters git or the Nix store, so keep the resulting AppImage to yourself.

## Running

```sh
chmod +x REDRIVER2-x86_64.AppImage
./REDRIVER2-x86_64.AppImage
```

- Config: `~/.local/share/redriver2/config.ini` is created on first run. It defaults to fullscreen at desktop resolution. Replays are saved next to it. Set `REDRIVER2_HOME` to use another directory.
- Saves (progress and settings): `~/.driver2/`.
- Arguments are passed to the game (e.g. `-nofmv`).

### Steam Deck

1. Copy the AppImage to the Deck (e.g. `~/Games/`) and make it executable (in Dolphin: Properties → Permissions → "Is executable").
2. In Desktop Mode, open Steam → *Add a Game* → *Add a Non-Steam Game* → browse to the AppImage.
3. In Game Mode, set the controller layout to *Gamepad*. The game uses SDL's game controller mapping (see `[controls_game]` in `config.ini`).

### Analog controls

Like a real DualShock, the controller starts in **digital mode**. Press **Select + Start** together (on the Steam Deck, **View ⧉ + Menu ☰**) to switch analog mode on or off. In analog mode:

- the left stick steers proportionally and moves Tanner on foot
- the right stick turns Tanner and lets him look around
- rumble works

Analog mode is not remembered between launches. Pressing a keyboard key while a pad is connected switches back to digital.

## Notes

- Graphics use the bundled Mesa (radeonsi/iris/llvmpipe…), launched through the bundled `ld-linux`. That's why the image works on any distribution and needs no user namespaces. On systems with the proprietary NVIDIA driver it renders with llvmpipe (software).
- Audio goes through PulseAudio (PipeWire's pulse server on modern systems). Override this with `ALSOFT_DRIVERS`.
- If FUSE is unavailable, run `./REDRIVER2-x86_64.AppImage --appimage-extract-and-run`.
