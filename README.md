# REDRIVER2

PC:
<p align="center">
<a href="https://streamable.com/m8d29f"><img src="https://i.ibb.co/9rTkQND/aaa.png"/><a>
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
- Assuming you have compiled the most recent code. Copy DRIVER2 folder from your **game CD** to location where compiled EXE is located.

### Credits
- Soapy - lead programmer
- Gh0stBlade - API-level PSY-Q libraries reimplementation (aka HLE PSX Emulator)
- Ben Lincoln - This Dust Remembers What It Once Was (*TDR*)
- Stohrendorf - Symdump tool