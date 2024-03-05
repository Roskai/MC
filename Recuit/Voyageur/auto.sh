#!/bin/bash

echo "" >result
i=0
while [ $i -le 20 ]; do
	Ti=$1
	Tf=$2
	alpha=$3
	ampli=$4
	repMax=$5
	repMax=$(awk "BEGIN {printf \"%.10f\", $repMax * $i}")
	param="$Ti $Tf $alpha $ampli $repMax"
	echo $param | ./recuitVoyageur >>result
	sleep 1
	((i++))
done

grep fxopt result | cut -d '=' -f 2 >opti

total=0.0
IFS=$'\n'           # make newlines the only separator
while read line; do # A chaque ligne
	total=$(awk "BEGIN {printf \"%.10f\", $total + $line}" | tr ',' '.')
done <opti

average=$(awk "BEGIN {printf \"%.10f\", $total / $i}")
echo $average
