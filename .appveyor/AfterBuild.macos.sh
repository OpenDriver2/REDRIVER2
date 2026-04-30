#!/usr/bin/env bash
set -ex

cd "$APPVEYOR_BUILD_FOLDER/src_rebuild"

for renderer in opengl vulkan
do
    for config in Debug Release Release_dev
    do
        cd "$APPVEYOR_BUILD_FOLDER/src_rebuild/bin/macos_arm64_${renderer}/${config}"
        cp -R "$APPVEYOR_BUILD_FOLDER/data/"* ./
        tar -czf "REDRIVER2_macOS_arm64_${renderer}_${config}.tar.gz" *
        mv "REDRIVER2_macOS_arm64_${renderer}_${config}.tar.gz" "$APPVEYOR_BUILD_FOLDER/src_rebuild/bin/${config}/"
    done
done
