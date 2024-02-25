#!/usr/bin/env bash
set -ex

docker build -t builder/multiarch_build:1.0 -f Dockerfile .
docker run -it --privileged=true --rm --name=builder --mount type=bind,source=${PWD},target=/src builder/multiarch_build:1.0 ./.appveyor/Build.sh
