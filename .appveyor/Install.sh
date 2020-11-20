#!/usr/bin/env bash
set -ex

cd "$APPVEYOR_BUILD_FOLDER/src_rebuild"

# Download premake5
# because it isn't in the repos (yet?)
curl "$linux_premake_url" -Lo premake5.tar.gz
tar xvf premake5.tar.gz

sudo apt-get update -qq -y
sudo apt-get install -qq aptitude -y

# fix Ubuntu's broken mess of packages using aptitude
sudo aptitude install --quiet=2 \
    g++-multilib libsdl2-2.0-0:i386 libsdl2-dev:i386 \
    libopenal1:i386 libopenal-dev:i386 libjpeg-turbo8:i386 \
    libjpeg-turbo8-dev:i386 -y

