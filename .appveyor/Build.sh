#!/usr/bin/env bash
set -ex

cd "$APPVEYOR_BUILD_FOLDER/src_rebuild"

./premake5 gmake2

for config in debug release Release_Dev
do
    make config=$config -j$(nproc)
done
