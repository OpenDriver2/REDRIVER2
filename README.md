# REDRIVER2

PC (Windows and Linux):
[![Build status](https://ci.appveyor.com/api/projects/status/9abepvls6jexapqy/branch/master?svg=true)](https://ci.appveyor.com/project/SoapyMan/redriver2-10jm8/branch/master)

### Timeline: 
- Feb 19, 2019 - created skeleton, one year long preparations
- Mar 28, 2020 - started work on reimplementing the game, game intro running
- Sep 19, 2020 - reimplementing game complete - game is fully playable
- Jan 15, 2021 - refactoring complete

### Information
- Game was completely disassembled and reverse-engineered from MIPS back to C (except Memory Card menu overlay)
- Game has been *significantly improved over the original Playstation version*, original bugs was fixed and completed some unfinished gameplay aspects
- Utilizes [Psy-X (Psy-Cross) (formely extended TOMB5 emulator)](https://github.com/OpenDriver2/REDRIVER2/tree/master/src_rebuild/PsyX) as a layer for porting from Playstation
- Runs on Windows, Linux and soon to be on the other platforms (including backport to Playstation), no emulation involved
- Basic modding support - with textures and models replacement provided with [OpenDriver2Tools](https://github.com/OpenDriver2/OpenDriver2Tools)

### What to expect from it
- ***OpenDriver2*** project - complete rewrite with lots of new features such as *new renderer and sound engine, Lua scripting, Driver 1 content support*

### How is it done?
- All information (variables, types and function names) have been obtained from debugging symbols (.SYM), driver_psx_level and DLE
- Ghidra project (based on Italian SYM) to deal with overlays, simple code complex branching - semi-auto decompilation
- IDB based on Spanish SYM when dealing with things Ghidra can't handle properly - manual decompilation (mostly GTE code)

### How to use
See [Wiki/Installation Instructions](https://github.com/OpenDriver2/REDRIVER2/wiki/Installation-instructions)

### Credits
- Soapy - lead programmer
- Fireboyd78 - code refactoring and improvements
- Krishty, someone972 - formats decoding
- Gh0stBlade - API-level PSY-Q libraries reimplementation (HLE PSX Emulator) [(link)](https://github.com/tomb5/tomb5)
- Ben Lincoln - [This Dust Remembers What It Once Was](https://www.beneaththewaves.net/Software/This_Dust_Remembers_What_It_Once_Was.html) (*TDR*)
- Stohrendorf - [Symdump](https://github.com/stohrendorf/symdump) utility