# Contributing
Pull requests which drastically alter the structure or architecture of the code will not be accepted. 
This is to maintain "sanity" whilst going back through code, comparing to the original MIPS disassembled output.
Best pull requests are which resolve bugs, finish existing decompiled methods, improve readability, introduce new decompiled methods and improve code documentation.

It's also good to see which issues have more priority to work with here:
https://github.com/OpenDriver2/REDRIVER2/contribute

#### Markers for decompiled function names, code, etc

- [D] = decompiled
- [T] = debugged and tested
- [A] = altered code - debugging purposes or not being able to compile or run.... Can be used anywhere in the code, structures etc

# Base Versions
- **SLES-02996/SLES-12996** - 1.0 Italian version (look for `ITALIAN.SYM` existence)
- **SLES-02997/SLES-12997** - 1.0 Spanish version (look for `SPANISH.SYM` existence)

# Game Content
See [Wiki/Installation Instructions](https://github.com/OpenDriver2/REDRIVER2/wiki/Installation-instructions)

# Prerequisites
You'll need to acquire a few dependencies in order to start developing for **REDRIVER2**.

The default location for dependencies are in the `src_rebuild\dependencies` folder:
```
SDL2_DIR = <dependencies>\SDL2
OPENAL_DIR = <dependencies>\openal-soft
JPEG_DIR = <dependencies>\jpeg
```

Alternatively, you can set environment variables like so:
```
SDL2_DIR = <your_dependency_folder>\SDL2-2.0.12
OPENAL_DIR = <your_dependency_folder>\openal-soft-1.20.1-bin
JPEG_DIR = <your_dependency_folder>\jpeg-9d
```

Once you've got your folder(s) setup, you'll need to download the following dependencies.

## SDL 2
- [Download](https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip)

Place all files in your `SDL2_DIR` directory.

## OpenAL-Soft
- [Download](https://openal-soft.org/openal-binaries/openal-soft-1.20.1-bin.zip)

Place all files in your `OPENAL_DIR` directory.

## JPEG
- [Download](http://www.ijg.org/files/jpegsr9d.zip)

Place all files in your `JPEG_DIR` directory.

You'll also need to rename `jconfig.xx` (proper one for your platform) to `jconfig.h`. 
For *Windows / Visual Studio* this means renaming `jconfig.vc` to `jconfig.h`.

## Premake 5
- [Download](https://github.com/premake/premake-core/releases/download/v5.0.0-alpha15/premake-5.0.0-alpha15-windows.zip)

Place `premake5.exe` in your `src_rebuild` folder in order to generate project files.

Make sure you have downloaded all other dependencies first before running premake.

Next you need to run `premake5 <target IDE>`, see premake documentation;
Or just run `gen_vc2019.bat` (Windows only)

# Compiling
Project **must** be targeted for **32-bit** platforms only. This is due to the size of pointers and other types (such as *long* in GCC) being different on 64-bit platforms.

You can also download pre-compiled [nightly builds](https://ci.appveyor.com/project/SoapyMan/redriver2-10jm8/branch/master) or the latest [release builds](https://github.com/OpenDriver2/REDRIVER2/releases) as well.
