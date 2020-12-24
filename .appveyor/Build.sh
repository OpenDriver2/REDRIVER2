#!/usr/bin/env bash
set -ex

cd "$APPVEYOR_BUILD_FOLDER/src_rebuild"

./premake5 gmake2

for config in debug_x86 release_x86 release_dev_x86
do
    make config=$config -j$(nproc)
done
