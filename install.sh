#!/bin/bash

if [ $# == 1 ]; then
	if [ ! -d $1 ]; then
		mkdir -p $1
	fi
	repository=$(pwd)
	cd $1
	if [ ! -d ./include ]; then
		mkdir include
	fi
	if [ -d "${repository}/include" ] && [ -f "${repository}/include/merlin_random" ]; then
		cp "${repository}/include/merlin_"*.hpp ./include/
		cp "${repository}/include/merlin_random" ./include/
	else
		echo "[Error] Sources not found - The installation script must be called from the repository (cd to Merlin-random/)."
	fi
else
	echo "[Error] Expected 1 argument ($# given) - (Only) the installation directory is required."
fi

