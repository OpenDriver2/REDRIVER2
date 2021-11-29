set REDRIVER_FOLDER=%cd%\..

rem Make a symlink
mklink /J %REDRIVER_FOLDER%\PSXToolchain\GameSRC %REDRIVER_FOLDER%\src_rebuild

rem Create a virtual drive
SUBST X: %REDRIVER_FOLDER%\PSXToolchain

set PATH=%PATH%;X:\mipsel-unknown-elf\bin;
make

rem Cleanup
rem del GameSRC
SUBST X: /D

pause