echo off
cls
set REDRIVER_FOLDER=%cd%\..

rem Make a symlink
mklink /J %REDRIVER_FOLDER%\PSXToolchain\GameSRC %REDRIVER_FOLDER%\src_rebuild

rem Create a virtual drive
SUBST X: %REDRIVER_FOLDER%\PSXToolchain

set PATH=%PATH%;X:\mipsel-unknown-elf\bin;

if exist %REDRIVER_FOLDER%\PSXToolchain\CDSrc\0_CD_DATA\ (
  rem Yes
) else (
  mkdir %REDRIVER_FOLDER%\PSXToolchain\CDSrc\0_CD_DATA\
)

make

rem Cleanup
rem del GameSRC
SUBST X: /D

pause