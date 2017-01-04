#! /bin/bash
function debug() {
	[ "$_DEBUG" == "on" ] && $@ || :
}

for i in {1..6}
do
	debug echo $i
done
echo "script executed"
