$REDRIVER_FOLDER=[string](Get-Location) + "\.."
$cdDataPath = "$($REDRIVER_FOLDER)\PSXToolchain\CDSrc\0_CD_DATA\"

Write-Host $cdDataPath

# Make a symlink
$link_exist = Get-Item -Path "$($REDRIVER_FOLDER)\PSXToolchain\GameSRC" -ErrorAction Ignore
if (-Not $link_exist) {
    New-Item -ItemType Junction -Path "$($REDRIVER_FOLDER)\PSXToolchain\GameSRC" -Target "$($REDRIVER_FOLDER)\src_rebuild"
}

# Create a virtual drive
Invoke-Expression "SUBST X: $($REDRIVER_FOLDER)\PSXToolchain"

# Set tools path
$envPath = $env:PATH
$env:PATH="$($envPath);X:\mipsel-unknown-elf\bin";

Write-Host $env:PATH

$folder_exist = Get-Item -Path $cdDataPath -ErrorAction Ignore
if (-Not $folder_exist) {
    New-Item -ItemType Directory -Path "$($REDRIVER_FOLDER)\PSX]Toolchain\CDSrc\0_CD_DATA"
}

Write-Host "Starting build process..."

Invoke-Expression "make"

# Cleanup
Invoke-Expression "SUBST X: /D"

Read-Host -Prompt "Build completed, press any key"
