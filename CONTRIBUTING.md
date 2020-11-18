# Contributing
Pull requests which drastically alter the structure or architecture of the code will not be accepted. 
This is to maintain "sanity" whilst going back through code, comparing to the original MIPS disassembled output.
Best pull requests are which resolve bugs, finish existing decompiled methods, improve readability, introduce new decompiled methods and improve code documentation.

Also it's good to see which issues have more priority to work with here:
https://github.com/SoapyMan/REDRIVER2/contribute

# Compiling
Project **must** be built only for **32 bit** platform because there are 32 bit pointers everywhere (and use of *long* which with GCC can be a 64 bit numbers)

First use [premake5](https://github.com/premake/premake-core/releases/download/v5.0.0-alpha15/premake-5.0.0-alpha15-windows.zip) to generate project files.

Dependencies (links for Windows):
- [SDL 2](https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip)
- [OpenAL-Soft](https://openal-soft.org/openal-binaries/openal-soft-1.20.1-bin.zip)
- [JPEG](http://www.ijg.org/files/jpegsr9d.zip)

#### Before running premake ####
You need to download all the dependencies and extract them.
After set next environment variables like:
```
SDL2_DIR = <your_dependency_folder>\SDL2-2.0.12
OPENAL_DIR = <your_dependency_folder>\openal-soft-1.20.1-bin
JPEG_DIR = <your_dependency_folder>\jpeg-9d
```

*JPEG* itself needs to be configured - go to your *JPEG_DIR* folder and rename `jconfig.xx` (proper one for your platform) to `jconfig.h`. 
For *Windows / Visual Studio* you need to choose `jconfig.vc`

Next you need to run `premake5 <target IDE>`, see premake documentation;
Or just run `gen_vc2019.bat` (Windows only)

#### Markers for decompiled function names, code, etc

- [D] = decompiled
- [T] = debugged and tested
- [A] = altered code - debugging purposes or not being able to compile or run.... Can be used anywhere in the code, structures etc

# Base Versions
- **SLES-02997/SLES-12997** - 1.0 Spanish version (look for SPANISH.SYM existance)
- **SLES-02996/SLES-12996** - 1.0 Italian version (look for ITALIAN.SYM existance)

# Game Content
See [Wiki/Installation Instructions](https://github.com/OpenDriver2/REDRIVER2/wiki/Installation-instructions)
