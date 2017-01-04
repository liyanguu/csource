#!/bin/bash
#FILENAME: album.sh - generate a webpage album of photos/pictures under current directory
#DATE: 2015.8.31

count=1

echo generating...

mkdir -p .thumbs

cat <<EOF > index.html
<html>
<head>
<style>
body { background-color: black; padding: 200px }
h1 { color: white }
img { padding: 10px }
</style>
</head>
<body>
<h1>my album</h1>
<div>
EOF

for pic in *.jpg *.jpeg *.png ; do
	convert "$pic" -auto-orient -resize "100x" ".thumbs/$pic" 2>>mylog.txt
	if [ $? -eq 0 ]; then
		echo "<a href=\"$pic\"><img src=\".thumbs/$pic\" title=\"$pic\" /></a>" >> index.html
		[ $(( count % 4 )) -eq 0 ] && echo "<br/>" >> index.html
		let count++	
	fi
done

cat <<EOF >> index.html
</div>
</body>
</html>
EOF

if [ $count -gt 1 ]; then
	echo album generated to index.html
else
	echo album not generated
	rm index.html -r .thumbs
fi
