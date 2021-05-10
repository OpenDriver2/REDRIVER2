@echo off
@cls

set CD1_PATH=install/Driver2CD1.bin
set CD2_PATH=install/Driver2CD2.bin
set JPSXDEC_PATH=install

rem -- Check if Java is installed --
java -version 1>nul 2>nul || (
   echo Please install Java runtime to continue.
   pause
   exit /b 2
)

rem -- Extract CD movies and audios --

echo "Processing CD1..."
call install/conv.bat %CD1_PATH% Driver2temp.idx

echo "Processing CD2..."
call install/conv.bat %CD2_PATH% Driver2temp.idx

rem del Driver2temp.idx

echo DONE

pause
