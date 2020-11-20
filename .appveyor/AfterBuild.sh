#!/usr/bin/env bash
set -ex

for config in debug release release_dev
do
    cd "${APPVEYOR_BUILD_FOLDER}/src_rebuild/bin/${config^}"
    tar -czf "REDRIVER2_${config^}.tar.gz" *
done
