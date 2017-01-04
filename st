for i in $*
do 
	set "`ls -l $i`"; d="$6 $7 $8"
	echo `/usr/bin/wc -l $i` $d 
done
