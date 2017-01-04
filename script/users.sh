#!/bin/bash

line="root:x:0:0:root:/root:/bin/bash"
function readline() {

oldIFS=$IFS
IFS=":"
count=0
for item in $1
do
	[ $count -eq 0 ] && user=$item
	[ $count -eq 6 ] && shell=$item
	let count++
done
IFS=$oldIFS
echo "$user: $shell"

}

fpath="/etc/passwd"
if [ -f $fpash ]
then
	list="`cat $fpath`"
	for line in $list
	do
		readline $line
	done
else
	echo "/etc/passwd doesn't exist"
fi
