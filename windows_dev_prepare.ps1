$openal_ver = '1.23.1'
$sdl2_ver = '2.30.2'

$windows_premake_url = 'https://github.com/premake/premake-core/releases/download/v5.0.0-beta1/premake-5.0.0-beta1-windows.zip'
$windows_jpeg_url = 'http://www.ijg.org/files/jpegsr9d.zip'
$windows_openal_url = 'https://github.com/kcat/openal-soft/releases/download/' + $openal_ver + '/openal-soft-' + $openal_ver + '-bin.zip'
$windows_sdl2_url = 'https://github.com/libsdl-org/SDL/releases/download/release-' + $sdl2_ver + '/SDL2-devel-' + $sdl2_ver + '-VC.zip'

$project_folder = '.\\src_rebuild'
$dependency_folder = $project_folder + '\\dependencies'

# Download required dependencies
echo $windows_premake_url
echo $windows_sdl2_url
echo $windows_openal_url
echo $windows_jpeg_url

Invoke-WebRequest -Uri $windows_premake_url -OutFile PREMAKE.zip
Expand-Archive PREMAKE.zip -DestinationPath $project_folder

Invoke-WebRequest -Uri $windows_sdl2_url -OutFile SDL2.zip
Expand-Archive SDL2.zip -DestinationPath $dependency_folder

Invoke-WebRequest -Uri $windows_openal_url -OutFile OPENAL.zip
Expand-Archive OPENAL.zip -DestinationPath $dependency_folder

Invoke-WebRequest -Uri $windows_jpeg_url -OutFile JPEG.zip
Expand-Archive JPEG.zip -DestinationPath $dependency_folder

# Generate project files
$windows_jpeg_dir = '.\\dependencies\\jpeg-9d'
$windows_openal_dir = '.\\dependencies\\openal-soft-' + $openal_ver + '-bin'
$windows_sdl2_dir = '.\\dependencies\\SDL2-' + $sdl2_ver

$env:SDL2_DIR = $windows_sdl2_dir
$env:OPENAL_DIR = $windows_openal_dir
$env:JPEG_DIR = $windows_jpeg_dir

Set-Location -Path $project_folder
Rename-Item -Path ($windows_jpeg_dir + '\\jconfig.vc') -NewName "jconfig.h"

& .\\premake5 vs2022

# Open solution
& .\\project_vs2022_windows\\REDRIVER2.sln