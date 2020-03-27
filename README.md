# REDRIVER2

This project attempting to reverse-engineer PS1 game Driver 2;

This is probably NOT going to be a 1:1 recreation of the original source code as a lot of it missing and no one gives DEBUG version of the game

*If you have one, please contact me.*

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