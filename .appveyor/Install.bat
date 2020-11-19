@echo off

appveyor DownloadFile %windows_premake_url% -FileName premake5.zip
7z x premake5.zip -o%project_folder%

appveyor DownloadFile %windows_jpeg_url% -FileName JPEG.zip
7z x JPEG.zip -o%dependency_folder%

appveyor DownloadFile %windows_openal_url% -FileName OPENAL.zip
7z x OPENAL.zip -o%dependency_folder%

appveyor DownloadFile %windows_sdl2_url% -FileName SDL2.zip
7z x SDL2.zip -o%dependency_folder%
