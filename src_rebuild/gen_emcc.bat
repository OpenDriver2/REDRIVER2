set SDL2_DIR=%cd%\dependencies\SDL2
set OPENAL_DIR=%cd%\dependencies\openal-soft
set JPEG_DIR=%cd%\dependencies\jpeg
premake5 gmake2 --os=emscripten
pause