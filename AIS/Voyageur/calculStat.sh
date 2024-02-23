#!/bin/bash

METHODESELECTION=1
METHODEMUTATION=1
NBMAXMUTATIONS=3
NBVILLES=30
MUTATIONDYNAMIQUE=0

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

POPULATION=3500
POURCENTAGECLONES=45
POURCENTAGENOUVEAUX=25
NBGENERATIONS=1650
NBGENERATIONSINJECTION=75
set_param

echo "Pour les paramètres :"
echo "    NBVILLES=$NBVILLES"
echo "    METHODESELECTION=$METHODESELECTION"
echo "    METHODEMUTATION=$METHODEMUTATION"
echo "    NBMAXMUTATIONS=$NBMAXMUTATIONS"
echo "    MUTATIONDYNAMIQUE=$MUTATIONDYNAMIQUE"
echo "    "
echo "    POPULATION=$POPULATION"
echo "    POURCENTAGECLONES=$POURCENTAGECLONES"
echo "    POURCENTAGENOUVEAUX=$POURCENTAGENOUVEAUX"
echo "    NBGENERATIONS=$NBGENERATIONS"
echo "    NBGENERATIONSINJECTION=$NBGENERATIONSINJECTION"
echo "Résultat :"
echo "    $(moyenne 20 $POPULATION $POURCENTAGECLONES $POURCENTAGENOUVEAUX $NBGENERATIONS $NBGENERATIONSINJECTION)"