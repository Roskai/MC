#!/bin/bash

function moyenne() {
	total=0.0
	count=0

	while [ $count -lt $1 ]; do
		number=$(echo $param | ./recuitVoyageur | grep "Cout optimal" | cut -d "=" -f 2)
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
# Cela permet de changer les différentes méthode 
# cela permet de tester les differentes façon
####
function set_param() {
	param="$TEMPERATUREINITIALE $TEMPERATUREFINALE $ALPHA $AMPLITUDE $NB_REP_MAX"
	sed -i 's/\#define DECROISSEMENT_TEMP .*/\#define DECROISSEMENT_TEMP '"$DECROISSEMENT_TEMP"'/g' params.h
	sed -i 's/\#define NBVILLES .*/\#define NBVILLES '"$NBVILLES"'/g' params.h
	make clean &> /dev/null
	make &> /dev/null
}

### --- 

TEMPERATUREINITIALE=5000
TEMPERATUREFINALE=0.1
ALPHA=0.99
AMPLITUDE=5
NB_REP_MAX=5000
# Decroissement de la temperature :
# 	- 0 : T - alpha 
# 	- 1 : T * alpha
DECROISSEMENT_TEMP=1
NBVILLES=30

set_param

make

echo "Pour les paramètres :"
echo "    TEMPERATUREINITIALE=$TEMPERATUREINITIALE"
echo "    TEMPERATUREFINALE=$TEMPERATUREFINALE"
echo "    ALPHA=$ALPHA"
echo "    AMPLITUDE=$AMPLITUDE"
echo "    NB_REP_MAX=$NB_REP_MAX"
echo "    NBVILLES=$NBVILLES"
echo "    DECROISSEMENT_TEMP=$DECROISSEMENT_TEMP"
echo "Résultat :"
echo "    $(moyenne 20)"

make clean
