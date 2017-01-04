#!/bin/bash

lines=`tput lines`
i=1
while [ $i -lt $lines ]
do
	echo
	let i++
done
tput cup 0 0
