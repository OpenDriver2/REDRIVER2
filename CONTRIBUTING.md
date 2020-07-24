# Contributing
Pull requests which drastically alter the structure or architecture of the code will not be accepted. This is to maintain "sanity" whilst going back through code, comparing to the original MIPS disassembled output.

# Compiling
Project **must** be built only for 32 bit platform because there are 32 bit pointers everywhere
Use premake5 to generate project files

Dependencies:
- SDL2
- GLEW
- OpenAL-Soft

#### Markers for decompiled function names, code, etc

- [D] = decompiled
- [F] = final
- [T] = debugged and tested

- [A] = altered code - debugging purposes or not being able to compile or run...

