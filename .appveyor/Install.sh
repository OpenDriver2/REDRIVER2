#!/usr/bin/env bash
set -ex

cd "$APPVEYOR_BUILD_FOLDER/src_rebuild"

# Download premake5
# because it isn't in the repos (yet?)
curl "$linux_premake_url" -Lo premake5.tar.gz
tar xvf premake5.tar.gz

sudo apt-get update -qq -y
sudo apt-get install --no-install-recommends -y gcc-multilib g++-multilib
sudo apt-get install -qq aptitude -y

# fix Ubuntu's broken mess of packages using aptitude
sudo aptitude install --quiet=2 \
    libsdl2-dev:i386 \
    libopenal-dev:i386 \
    libjpeg-turbo8-dev:i386 \
    flatpak flatpak-builder -y

# Setting XDG_DATA_DIRS environement variable for flatpak
export XDG_DATA_DIRS="/var/lib/flatpak/exports/share:${HOME}/.local/share/flatpak/exports/share:$XDG_DATA_DIRS"

# Adding the flathub repo
flatpak --user remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

# Adding Platform/SDK for the Linux flatpak release
flatpak --user install flathub org.freedesktop.Platform/x86_64/20.08 -y
flatpak --user install flathub org.freedesktop.Sdk/x86_64/20.08 -y
flatpak --user install flathub org.freedesktop.Sdk.Compat.i386/x86_64/20.08 -y
flatpak --user install flathub org.freedesktop.Sdk.Extension.toolchain-i386/x86_64/20.08 -y
