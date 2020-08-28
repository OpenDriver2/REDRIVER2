# Contributing
Pull requests which drastically alter the structure or architecture of the code will not be accepted. 
This is to maintain "sanity" whilst going back through code, comparing to the original MIPS disassembled output.
Best pull requests are which resolve bugs, finish existing decompiled methods, improve readability, introduce new decompiled methods and improve code documentation.

# Compiling
Project **must** be built only for 32 bit platform because there are 32 bit pointers everywhere
Use [premake5](https://github.com/premake/premake-core/releases/download/v5.0.0-alpha15/premake-5.0.0-alpha15-windows.zip) to generate project files.

Dependencies (Windows):
- [SDL2](https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip)
- [GLEW](https://netix.dl.sourceforge.net/project/glew/glew/2.1.0/glew-2.1.0-win32.zip)
- [OpenAL-Soft](https://kcat.strangesoft.net/openal-binaries/openal-soft-1.20.1-bin.zip)

Before running premake you need to download all dependencies.
After set next environment variables:
```
SDL2_DIR = <your_dependency_folder>\SDL2-2.0.12
GLEW_DIR = <your_dependency_folder>\glew-2.1.0
OPENAL_DIR = <your_dependency_folder>\openal-soft-1.20.1-bin
```
and run premake.

#### Markers for decompiled function names, code, etc

- [D] = decompiled
- [F] = final
- [T] = debugged and tested

- [A] = altered code - debugging purposes or not being able to compile or run...

# Base Versions
- **SLES-02997/SLES-12997** - 1.0 Spanish version (look for SPANISH.SYM existance)
- **SLES-02996/SLES-12996** - 1.0 Italian version (look for ITALIAN.SYM existance)

