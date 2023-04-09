FROM fedora:37
LABEL Description="Build environment"

ENV HOME /root

SHELL ["/bin/bash", "-c"]

RUN dnf update -y && \
    dnf groupinstall -y 'Development Tools' && \
    dnf install -y make gcc gcc-c++ \
    libjpeg-turbo-devel.i686 \
    glibc-devel.i686 \
    SDL2-devel.i686 \
    openal-soft-devel.i686 \
    flatpak flatpak-builder

ENV APPVEYOR_BUILD_FOLDER=/src

# Setting XDG_DATA_DIRS environement variable for flatpak
ENV XDG_DATA_DIRS="/var/lib/flatpak/exports/share:${HOME}/.local/share/flatpak/exports/share:$XDG_DATA_DIRS"

# Adding the flathub repo
RUN flatpak --user remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

# Adding Platform/SDK for the Linux flatpak release
RUN flatpak --user install flathub org.freedesktop.Platform/x86_64/22.08 -y
RUN flatpak --user install flathub org.freedesktop.Sdk/x86_64/22.08 -y
RUN flatpak --user install flathub org.freedesktop.Sdk.Compat.i386/x86_64/22.08 -y
RUN flatpak --user install flathub org.freedesktop.Sdk.Extension.toolchain-i386/x86_64/22.08 -y

WORKDIR /src

CMD ["/bin/bash"]

# Building example:
#   docker build -t builder/multiarch_build:1.0 -f Dockerfile .

# Running example:
#   docker run -it --privileged=true --rm --name=builder --mount type=bind,source=${PWD},target=/src builder/multiarch_build:1.0 bash
