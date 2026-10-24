#!/usr/bin/env python3
"""Extract the DRIVER2 directory from a raw (2352 byte/sector, MODE2) Driver 2 disc image.

usage: extract_iso.py IMAGE.bin OUTDIR

Raw .STR/.XA streams are skipped (they are converted by jpsxdec instead) and
files that already exist in OUTDIR are kept, so the second disc only adds
what the first one lacks.
"""
import os
import struct
import sys

SECTOR = 2352
PAYLOAD = 24  # sync + header + subheader of a MODE2 form 1 sector
SKIP_EXT = (".STR", ".XA")


def main():
    image, outdir = sys.argv[1:]
    f = open(image, "rb")

    def read(lba, size):
        out = bytearray()
        for i in range((size + 2047) // 2048):
            f.seek((lba + i) * SECTOR + PAYLOAD)
            out += f.read(2048)
        return bytes(out[:size])

    pvd = read(16, 2048)
    if pvd[1:6] != b"CD001":
        sys.exit(f"{image}: not a raw MODE2/2352 ISO9660 image")

    count = 0

    def walk(lba, size, rel):
        nonlocal count
        data = read(lba, size)
        i = 0
        while i < len(data):
            length = data[i]
            if length == 0:  # records never cross sector boundaries
                i = (i // 2048 + 1) * 2048
                continue
            extent, = struct.unpack_from("<I", data, i + 2)
            fsize, = struct.unpack_from("<I", data, i + 10)
            flags = data[i + 25]
            name = data[i + 33:i + 33 + data[i + 32]]
            i += length
            if name in (b"\0", b"\1"):
                continue
            name = name.decode("ascii").split(";")[0]
            path = os.path.join(rel, name)
            if flags & 2:
                if rel or name == "DRIVER2":
                    walk(extent, fsize, path)
            elif rel and not name.upper().endswith(SKIP_EXT):
                dst = os.path.join(outdir, path)
                if os.path.exists(dst):
                    continue
                os.makedirs(os.path.dirname(dst), exist_ok=True)
                with open(dst, "wb") as o:
                    o.write(read(extent, fsize))
                count += 1

    root = pvd[156:156 + 34]
    walk(*struct.unpack_from("<I", root, 2), *struct.unpack_from("<I", root, 10), "")
    print(f"{image}: extracted {count} files")


if __name__ == "__main__":
    main()
