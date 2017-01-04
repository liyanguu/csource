#!/bin/bash

if [ $# -ne 1 ]; then
	echo "usage: $0 file"
	exit -1
fi

filename=$1

egrep -o "\b[[:alpha:]]+\b" $filename | \

awk '{ count[$0]++ }
END {
for (i in count) { printf("%-14s %d\n", i, count[i]) } 
}' | \

sort
