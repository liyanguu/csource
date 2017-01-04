#! /bin/bash

start=$(date +%s)
$@
end=$(date +%s)
dif=$(( end - start ))
echo "time taken to execute '$@' is $dif seconds."
