#!/bin/bash
#FILENAME: ftype.sh 
#DATE: 2015-9-8

if [ $# -ne 1 ]; then
	echo usage: $0 DIR 
	exit 1
fi

path=$1
count=0
declare -A tarray;

while read line; do
	ftype=`file -b "$line" | cut -d, -f1`
	let count++
	let tarray["$ftype"]++
done< <(find "$path" -maxdepth 3 -type f -print 2>/dev/null)

echo total files: $count

for ftype in "${!tarray[@]}"; do
	printf "%5d %s\n" ${tarray["$ftype"]} "$ftype"
done

