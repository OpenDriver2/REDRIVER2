# REDRIVER2

PC (Windows):
[![Build status](https://ci.appveyor.com/api/projects/status/smxrjad2rf4fg0py/branch/master?svg=true)](https://ci.appveyor.com/project/SoapyMan/redriver2/branch/master)
<p align="center">
<a href="https://streamable.com/4p8rx5"><img src="https://i.ibb.co/qJ5PJXj/aaa.png"/><a>
 </p>
 
Project attempting to reverse-engineer PS1 game Driver 2;

### Goals
- Rebuild all source code from assembly
- Compile native version for **PC** (and for **PSX** later)
- Make game playeble from start to finish, all game modes should function properly
- Fix some existing critical bugs and performance issues
- ***OpenDriver2?*** rewrite code, implement various cool stuff, PC rendering and audio engine, get rid of hard-coded stuff

### How is it done?
- All information (variables, types and function names) have been obtained from debugging symbols (.SYM), driver_psx_level and DLE
- Ghidra project (based on Italian SYM) to deal with overlays, simple code complex branching - semi-auto decompilation
- IDB based on Spanish SYM when dealing with things Ghidra can't handle properly - manual decompilation (mostly GTE code)

### Usage
- Assuming you have compiled the most recent code or got artifacts from Appveyor. Copy DRIVER2 folder from your **game CD** to location where compiled EXE is located.

### Credits
- Soapy - lead programmer
- Fireboyd78 - code refactoring and improvements
- Krishty, someone972 - formats decoding
- Gh0stBlade - API-level PSY-Q libraries reimplementation (HLE PSX Emulator)
- Ben Lincoln - This Dust Remembers What It Once Was (*TDR*)
- Stohrendorf - Symdump tool