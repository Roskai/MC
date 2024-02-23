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
			((count++))
		else
			echo "Erreur : '$number' n'est pas un nombre."
		fi
		#sleep 1
	done

	if [ $count -gt 0 ]; then
		average=$(awk "BEGIN {printf \"%.10f\", $total / $count}")
		echo $average
	else
		echo "Aucun nombre valide trouvé."
	fi
}
####
# Supprimer et le fichier params_change
# Cela permet de changer les différentes méthode 
# cela permet de tester les differentes façon
####
function set_param() {
	sed -i 's/\#define METHODESELECTION .*/\#define METHODESELECTION '"$METHODESELECTION"'/g' params.h
	sed -i 's/\#define METHODEMUTATION .*/\#define METHODEMUTATION '"$METHODEMUTATION"'/g' params.h
	sed -i 's/\#define NBMAXMUTATIONS .*/\#define NBMAXMUTATIONS '"$NBMAXMUTATIONS"'/g' params.h
	sed -i 's/\#define NBVILLES .*/\#define NBVILLES '"$NBVILLES"'/g' params.h
	make clean &> /dev/null
	make &> /dev/null
}

METHODESELECTION=1
METHODEMUTATION=1
NBMAXMUTATIONS=3
NBVILLES=10000
set_param
echo "$(moyenne $1 1000 100 0 1000 0)"

# for mutation in 0 1 2
# do
# 	METHODEMUTATION=$mutation
# 	echo change1
# 	for nbnouveaux in 25 50 75
# 	do
# 		for nbvilles in 100 30
# 		do
# 			NBVILLES=$nbvilles
# 			for selection in 0 1
# 			do
# 				METHODESELECTION=$selection
# 				set_param
# 				for nbgeninjection in 25 85 175
# 				do
# 					for taillepop in 350
# 					do
# 						for nbgeneration in 350
# 						do
# 							for nbclones in 45
# 							do
# 								echo "$(moyenne $1 $taillepop $nbclones $nbnouveaux $nbgeneration $nbgeninjection)"
# 							done
# 						done
# 					done
# 				done
# 			done
# 		done
# 	done
# done