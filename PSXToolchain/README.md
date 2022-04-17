# Playstation build toolchain

This is an instruction to build Playstation version of **REDRIVER2**

### Windows
 - Install **make** (In powershell `choco install make`)
 - Put **mipsel-unknown-elf** toolchain to this folder (https://github.com/majenkotech/mipsel-unknown-elf/releases)
 - Put Nugget version of **Psy-Q SDK**
 - Copy (https://github.com/pcsx-redux/nugget/tree/main/common) to `/PSXToolchain/PsyQ/common`
 - Execute **psx_build.bat**
 - Install [mkpsxiso](https://github.com/Lameguy64/mkpsxiso/releases)
 - Execute **psx_makecd.bat**
 - Locate and use **CDSrc/REDRIVER2.bin** and **cue** files