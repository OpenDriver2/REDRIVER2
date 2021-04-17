# Emscripten info on how to build

1. install VSExtForEmscripten for VS 2019
2. with chocolatey - `choco install emsdk`

#### Where chocolatey places SDK on windows:
`\AppData\Local\emsdk\upstream\emscripten`

## Building

- switch optimization to O3 (Full optimization)

- remove `/SAFESEH:NO` everywhere (if using VSExtForEmscripten)

- remove Windows defines if copied from Win32 configuration

- disable warnings: 
c++11-narrowing;constant-conversion;writable-strings;unused-value;switch;shift-op-parentheses;parentheses;format

add Clang parameters (Psy-X, REDRIVER2): 
`-s USE_SDL=2 -s FULL_ES2=1 -s USE_WEBGL2=1 -s ASYNCIFY=1 -s ALLOW_MEMORY_GROWTH=1`

add linker parameters (REDRIVER2): 
`-s TOTAL_MEMORY=33554432 -s USE_SDL=2 -s FULL_ES2=1 -s USE_WEBGL2=1 -s ASYNCIFY=1 -s ALLOW_MEMORY_GROWTH=1 --preload-file ../data@/`

