# Playstation build toolchain

In order to start building a Playstation version of **REDRIVER2** you'll need to perform following steps:

 - Put **mipsel-unknown-elf** toolchain to this folder (https://github.com/majenkotech/mipsel-unknown-elf/releases)
 - Install **make**
 - Obtain **Psy-Q SDK** converted for *latest GCC*
 - Copy (https://github.com/pcsx-redux/nugget/tree/main/common) to `/PSXToolchain/PsyQ/common`
 - Execute **psx_build.bat**
 - Install [mkpsxiso](https://github.com/Lameguy64/mkpsxiso/releases)
 - Execute **psx_makecd.bat**
 - Locate and use **CDSrc/REDRIVER2.bin** and **cue** files