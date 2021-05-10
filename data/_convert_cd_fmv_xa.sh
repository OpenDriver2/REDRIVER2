#!/bin/sh

export CD1_PATH="./install/Driver2CD1.bin"
export CD2_PATH="./install/Driver2CD2.bin"
export JPSXDEC_PATH="./install"

# -- Check if Java is installed --
if !(java -version 2>&1 >/dev/null | grep "java version\|openjdk version"); then
  echo "Java NOT installed!"
  exit
fi

# -- Extract CD movies and audios --

echo "Processing CD1..."
./install/conv.sh ${CD1_PATH} Driver2temp.idx

echo "Processing CD2..."
./install/conv.sh ${CD2_PATH} Driver2temp.idx

rm Driver2temp.idx

echo "DONE"
