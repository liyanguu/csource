#!/bin/bash
#FILENAME: view.sh 
#USAGE: view.sh [DIRECTORY] - view all pictures in [DIRECTORY]

if [ -d "$1" ]; then 
	cd $1;
elif [[ -n $1 ]]; then
	pic=$1
	shotwell "$pic" & 2>/dev/null
	exit
fi

for pic in *.NEF *.jpg *.jpeg *.png; do
	if [[ -e $pic ]]; then
		echo open ${pic##*.}s in $1:  $pic
		shotwell "$pic" & 2> /dev/null
	fi
done	
