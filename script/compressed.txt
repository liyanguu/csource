#!/bin/bash
#FILENAME: rename.sh - rename all pictures using number appendix under current directory
#DATE: 2015.8.31

count=1

mkdir -p tmp

mv *.jpg *.jpeg *.png tmp 2>err.txt 

for pic in tmp/*; do
	new="picture$count.${pic##*.}"
	mv "$pic" "$new" 2>>err.txt 
	echo rename \""${pic##*/}"\" to \""$new"\"
	let count++
done

rm -r tmp
