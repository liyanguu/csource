#!/BIN/bash
# FILENAME: files.sh 
# USAGE: files.sh DIR - list file types in DIR

if [ $# -ne 1 ]; then
	echo usage: files.sh DIR
	exit
fi

path=$1
declare -A tarray

IFS="\0"
while read fname; do 
	ftype=`file "$fname" -b | cut -d, -f1`
	let tarray["$ftype"]++
done< <(find $path -type f -print0)

echo "file type count:" 

for ftype in ${!tarray[@]}; do
	printf "%-50s %d\n" "$ftype" ${tarray["$ftype"]}
done


