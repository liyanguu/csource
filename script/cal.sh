#!/bin/bash

case $# in
0)	set `date`; m=${2%月##*0}; y=${1%年} ;;
1)	m=$1; set `date`; y=${1%年} ;;
*)	m=$1; y=$2 ;;
esac

case $m in
jan*|一月|1月)	m=1 ;;
feb*|二月|2月)	m=2 ;;
mar*|三月|3月)	m=3 ;;
apr*|四月|4月)	m=4 ;;
may*|五月|5月)	m=5 ;;
jun*|六月|6月)	m=6 ;;
jul*|七月|7月) 	m=7 ;;
aug*|八月|8月) 	m=8 ;;
sep*|九月|9月)	m=9 ;;
oct*|十月|10月)		m=10 ;;
nov*|十一月|11月)	m=11 ;;
dec*|十二月|12月)	m=12 ;;
[1-9]|10|11|12)	;;
*)		y=$m; m="" ;;
esac

/usr/bin/cal $m $y
