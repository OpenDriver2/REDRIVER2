@echo off
@cls

echo BUILDING INDEXES
java -jar %JPSXDEC_PATH%\jpsxdec.jar -f %1 -x %2

echo ---- CONVERTING VIDEO ----
java -jar %JPSXDEC_PATH%\jpsxdec.jar -x %2 -a video -quality psx -vf avi:mjpg -up Lanczos3

echo ---- CONVERTING AUDIO ----
java -jar %JPSXDEC_PATH%\jpsxdec.jar -x %2 -a audio -quality psx -af wav

