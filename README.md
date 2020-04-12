# REDRIVER2

PC:
<p align="center">
<a href="https://streamable.com/s5f9kt"><img src="https://i.ibb.co/cQZtX2Q/aaa.png"/><a>
 </p>
 
This project attempting to reverse-engineer PS1 game Driver 2;
This is probably NOT going to be a 1:1 recreation.

### Goals
- Understand what's going on with all of this and how it works
- Implement LEV file and other loaders as the game does
- Reverse-engineer basic gameplay stuff (core mechanics - car physics, pedestrians, etc)
- Build the game both for PSX and PSXPC targets
- *OpenDriver2?*

### How done
- Ghidra project (based on Italian SYM) to deal with overlays and very simple logic
- IDB based on Spanish SYM when dealing with things Ghidra can't handle

### Credits
- Soapy - lead programmer
- Gh0stBlade - HLE PSX Emulator
- Ben Lincoln - This Dust Remembers What It Once Was (*TDR*)
- Stohrendorf - Symdump tool