#!/usr/bin/env bash
set -ex

cd "$APPVEYOR_BUILD_FOLDER/src_rebuild"

# Strip any cached project files between renderer variants so premake
# regenerates the makefile with the right --renderer option.
rm -rf project_gmake_macosx

NCPU=$(sysctl -n hw.ncpu)

# ---------- OpenGL build (default) ----------
premake5 gmake
pushd project_gmake_macosx > /dev/null
for config in debug_arm64 release_arm64 release_dev_arm64
do
    make config=$config -j$NCPU
done
popd > /dev/null

# Stash the OpenGL artifacts before regenerating for Vulkan.
mkdir -p bin/macos_arm64_opengl
cp -R bin/Debug bin/Release bin/Release_dev bin/macos_arm64_opengl/

# ---------- Vulkan / MoltenVK build ----------
rm -rf project_gmake_macosx
premake5 --renderer=vulkan gmake
pushd project_gmake_macosx > /dev/null
for config in debug_arm64 release_arm64 release_dev_arm64
do
    make config=$config -j$NCPU
done
popd > /dev/null

mkdir -p bin/macos_arm64_vulkan
cp -R bin/Debug bin/Release bin/Release_dev bin/macos_arm64_vulkan/
