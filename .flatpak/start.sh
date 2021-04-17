#!/bin/bash

cd /app/game/data/
AppVersion=$(cat /app/share/appdata/io.github.opendriver2.Redriver2.appdata.xml | awk  -F'"' 'NR==15 {print $2":"$4}')

function importDefaultData {
  cp -rf `ls /app/game/data/ | grep -v '^config.ini$'` /var/data/
	if [ ! -f /var/data/config.ini ]; then
	  echo "Config file not found, importing default config."
	  cp /app/game/data/config.ini /var/data/config.ini
	fi
	echo "$AppVersion" > /var/cache/REDRIVER2.cache
}

if [ ! -d /var/data/DRIVER2 ]; then
	zenity --error --no-wrap --text="`printf "DRIVER2 files are missing! Add the folder in:\n ${HOME}/.var/io.github.opendriver2.Redriver2/data"`"
	exit 0
fi

if [ ! -f /var/cache/REDRIVER2.cache ]; then
  echo "Cache not found, overwriting files."
	importDefaultData
fi

if [[ $(< /var/cache/REDRIVER2.cache) != "$AppVersion" ]]; then
  echo "REDRIVER2 version not matching, overwriting files."
  importDefaultData
fi

args=""
while [[ "$#" -gt 0 ]]; do
	args+="$1 "
	shift
done

cd /app/game/bin/
case $REDRIVER2_BUILD in
	release) ./REDRIVER2 $([ ! -z "$args" ] && echo "$args"); shift;;
	dev) ./REDRIVER2_dev $([ ! -z "$args" ] && echo "$args"); shift;;
	debug) ./REDRIVER2_dbg $([ ! -z "$args" ] && echo "$args"); shift;;
	*) ./REDRIVER2 $([ ! -z "$args" ] && echo "$args"); # Fallback
esac
