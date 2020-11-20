@echo off

cd %project_folder%

ren "%windows_jpeg_dir%\jconfig.vc" "jconfig.h"

set JPEG_DIR=%windows_jpeg_dir%
set OPENAL_DIR=%windows_openal_dir%
set SDL2_DIR=%windows_sdl2_dir%

premake5 vs2019

set config=Debug:Release:Release_dev
for %%c in (%config::= %) do (
    msbuild .\REDRIVER2.sln /p:Configuration="%%c" /p:Platform=Win32 /m ^
        /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll" ^
        /nologo /ConsoleLoggerParameters:NoSummary;Verbosity=quiet
)
