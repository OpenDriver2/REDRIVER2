#!/usr/bin/env python3
"""Copy ELF files and their whole DT_NEEDED closure into one flat lib dir.

usage: bundle_libs.py OUTDIR SEARCHDIRS_FILE ROOT...

ROOT is either a path to an ELF file (only its dependencies are copied) or a
soname (the library itself is copied too, e.g. things that are dlopen()ed).
SEARCHDIRS_FILE lists one library directory per line, in priority order.
"""
import os
import shutil
import sys

from elftools.elf.dynamic import DynamicSection
from elftools.elf.elffile import ELFFile


def needed(path):
    with open(path, "rb") as f:
        elf = ELFFile(f)
        for sec in elf.iter_sections():
            if isinstance(sec, DynamicSection):
                return [t.needed for t in sec.iter_tags() if t.entry.d_tag == "DT_NEEDED"]
    return []


def main():
    outdir, dirs_file, *roots = sys.argv[1:]
    with open(dirs_file) as f:
        search = [d.strip() for d in f if d.strip()]

    def find(soname):
        for d in search:
            p = os.path.join(d, soname)
            if os.path.isfile(p):
                return p
        return None

    os.makedirs(outdir, exist_ok=True)
    queue = []
    for r in roots:
        if os.sep in r:
            queue.extend(needed(r))
        else:
            queue.append(r)

    done, missing = set(), []
    while queue:
        soname = queue.pop()
        if soname in done:
            continue
        done.add(soname)
        src = find(soname)
        if src is None:
            missing.append(soname)
            continue
        dst = os.path.join(outdir, soname)
        shutil.copyfile(src, dst)  # dereferences symlinks
        os.chmod(dst, 0o755)
        queue.extend(needed(dst))

    print(f"bundled {len(done) - len(missing)} libraries")
    for m in sorted(missing):
        print(f"warning: not found: {m}", file=sys.stderr)


if __name__ == "__main__":
    main()
