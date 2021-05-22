# REDRIVER2 (Reverse-Engineered Driver 2)

![REDRIVER2 running on Windows](https://i.ibb.co/2q1pp06/red2.png)

Build status (Windows and Linux):
[![Build status](https://ci.appveyor.com/api/projects/status/9abepvls6jexapqy/branch/master?svg=true)](https://ci.appveyor.com/project/SoapyMan/redriver2-10jm8/branch/master)

### Information
- This is an original game - it was carefully and completely disassembled and translated from MIPS back to C (except Memory Card menu) - ***no emulation involved***
- Game has been *significantly improved over the original Playstation version*, original bugs were fixed and completed some unfinished gameplay aspects
- It now runs on Windows, Linux and soon to be on the other platforms (including backport to Playstation) and utilizes [Psy-X (Psy-Cross) (formely extended TOMB5 emulator)](https://github.com/OpenDriver2/REDRIVER2/tree/master/src_rebuild/PsyX) as a layer for porting from Playstation
- Basic modding support - with textures and models replacement provided with [OpenDriver2Tools](https://github.com/OpenDriver2/OpenDriver2Tools)

### How is it done?
- All information (variables, types and function names) have been obtained from debugging symbols (.SYM), driver_psx_level and DLE
- Ghidra project (based on Italian SYM) to deal with overlays, simple code complex branching - semi-auto decompilation
- IDB based on Spanish SYM when dealing with things Ghidra can't handle properly - manual decompilation (mostly GTE code)

History:
- Feb 19, 2019 - created skeleton, one year long preparations
- Mar 28, 2020 - started work on reimplementing the game, game intro running
- Sep 19, 2020 - reimplementing game complete - game is fully playable
- Jan 15, 2021 - refactoring complete

### How to use
See [Wiki/Installation Instructions](https://github.com/OpenDriver2/REDRIVER2/wiki/Installation-instructions)

### How can I contribute?
See [Contributing to project](https://github.com/OpenDriver2/REDRIVER2/wiki/Contributing-to-project) page

### What's next
- ***OpenDriver2*** project - complete rewrite with lots of new features such as *new renderer and sound engine, Lua scripting, Driver 1 content support*

### Credits
- **SoapyMan** - lead reverse engineer and programmer
- **Fireboyd78** - code refactoring and improvements
- **Krishty, someone972** - early formats decoding
- **Gh0stBlade** - HLE Emulator code used as a base for Psy-Cross [(link)](https://github.com/TOMB5/TOMB5/tree/master/EMULATOR)
- **Ben Lincoln** - [This Dust Remembers What It Once Was](https://www.beneaththewaves.net/Software/This_Dust_Remembers_What_It_Once_Was.html) (*TDR*)
- **Stohrendorf** - [Symdump](https://github.com/stohrendorf/symdump) utility
