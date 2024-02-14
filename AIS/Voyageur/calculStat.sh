#!/bin/bash

METHODESELECTION=1
METHODEMUTATION=1
NBMAXMUTATIONS=3
NBVILLES=30

function moyenne() {
	total=0.0
	count=0

	while [ $count -lt $1 ]; do
		number=$(./ais $2 $3 $4 $5 $6)
		if [[ "$number" =~ ^[+-]?[0-9]*\.?[0-9]+$ ]]; then
			total=$(awk "BEGIN {printf \"%.10f\", $total + $number}" | tr ',' '.')
			echo "$count : $number"
			((count++))
		else
			echo "Erreur : '$number' n'est pas un nombre à virgule flottante valide."
			exit 1
		fi
		sleep 1
	done

	if [ $count -gt 0 ]; then
		average=$(awk "BEGIN {printf \"%.10f\", $total / $count}")
		echo "Moyenne pour $2 $3 $4 $5 $6 : $average"
	else
		echo "Aucun nombre à virgule flottante valide trouvé."
	fi
}

function set_param() {
	file=./param_change.h

	rm $file
	touch $file

	echo "#define METHODESELECTION $METHODESELECTION" >> $file
	echo "#define METHODEMUTATION $METHODEMUTATION" >> $file
	echo "#define NBMAXMUTATIONS $NBMAXMUTATIONS" >> $file
	echo "#define NBVILLES $NBVILLES" >> $file

	make clean
	make
}

set_param
moyenne $1 1000 50 20 1000 30

NBMAXMUTATIONS=4

set_param
moyenne $1 1000 50 20 1000 30