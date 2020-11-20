@echo off

set config=Debug:Release:Release_Dev
for %%c in (%config::= %) do (
    cd %project_folder%\bin\%%c
    
    copy %windows_sdl2_dir%\lib\x86\SDL2.dll SDL2.dll /Y
    copy %windows_openal_dir%\bin\Win32\soft_oal.dll OpenAL32.dll /Y

    xcopy /e /v %data_folder% .\ /Y
    7z a "REDRIVER2_%%c.zip" ".\*"
)
