#!/usr/bin/env bash
set -ex

# Configure
cd "$APPVEYOR_BUILD_FOLDER/src_rebuild"
./premake5 gmake2
cd project_gmake2_linux

# Build
for config in debug_x86 release_x86 release_dev_x86
do
    make config=$config -j$(nproc)
done

cd ${APPVEYOR_BUILD_FOLDER}

# Creating flatpak directories
mkdir -p "${APPVEYOR_BUILD_FOLDER}/.flatpak/lib" "${APPVEYOR_BUILD_FOLDER}/.flatpak/data" "${APPVEYOR_BUILD_FOLDER}/.flatpak/bin"
find ${APPVEYOR_BUILD_FOLDER}/src_rebuild/bin/Release -name 'REDRIVER2*' -exec cp -t ${APPVEYOR_BUILD_FOLDER}/.flatpak/bin {} +

# Copy missing libraries in the runtime
for lib in libjpeg libopenal libsndio libbsd
do
    cp -Lf $(ldd "${APPVEYOR_BUILD_FOLDER}/src_rebuild/bin/Release/REDRIVER2" | awk '/ => / { print $3 }' | grep ${lib}) "${APPVEYOR_BUILD_FOLDER}/.flatpak/lib"
done

cp -r "${APPVEYOR_BUILD_FOLDER}/data" "${APPVEYOR_BUILD_FOLDER}/.flatpak/"

# Editing metadatas with the current version
export APPVEYOR_BUILD_DATE=$(date "+%Y-%m-%d")
sed -i -e "s/V_VERSION/$APPVEYOR_BUILD_VERSION/g" -e "s/V_DATE/$APPVEYOR_BUILD_DATE/g" .flatpak/io.github.opendriver2.Redriver2.appdata.xml

# Build the flatpak
flatpak-builder --user --install build io.github.opendriver.redriver2.yaml --force-clean --arch=x86_64
flatpak build-bundle ~/.local/share/flatpak/repo io.github.opendriver2.Redriver2.flatpak io.github.opendriver2.Redriver2
rm -rf build/ .flatpak-builder/
