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
DECROISSEMENT_TEMP=0
NBVILLES=30

rm -f res.csv
touch res.csv
echo "\"nb_villes\",\"meth_decroiss_temp\",\"amplitude\",\"temp_init\",\"temp_finale\",\"nb_rep_max\",\"alpha\",\"resultat\"" >> res.csv

make
do_make=false

for NBVILLES in 30 100
do
	for DECROISSEMENT_TEMP in 0 1
	do
		do_make=true
		for AMPLITUDE in 1 3 5 10
		do
			for temperature_tries in 1 2 3 4 5
			do
				case $temperature_tries in
					1)
						TEMPERATUREINITIALE=1000
						TEMPERATUREFINALE=1
						;;
					2)
						TEMPERATUREINITIALE=500
						TEMPERATUREFINALE=1
						;;
					3)
						TEMPERATUREINITIALE=100
						TEMPERATUREFINALE=1
						;;
					4)
						TEMPERATUREINITIALE=1000
						TEMPERATUREFINALE=501
						;;
					5)
						TEMPERATUREINITIALE=1000
						TEMPERATUREFINALE=901
						;;
				esac
				for NB_REP_MAX in 100 500 1000
				do
					if [ $DECROISSEMENT_TEMP -eq 1 ];
					then
						for ALPHA in 0.99 #0.30 0.70 0.90 0.99
						do
							set_param
							if [ $do_make = true ];
							then
								make clean
								make
								do_make=false
							fi
							echo "$NBVILLES,$DECROISSEMENT_TEMP,$AMPLITUDE,$TEMPERATUREINITIALE,$TEMPERATUREFINALE,$NB_REP_MAX,$(echo "\"$ALPHA\"" | tr '.' ','),\"$(moyenne 5)\"" >> ./res.csv
						done
					else # Decroissement Temp : 1
						for ALPHA in 1.453 #0.5 1 3 5
						do
							set_param
							if [ $do_make = true ];
							then
								make clean
								make
								do_make=false
							fi
							echo "$NBVILLES,$DECROISSEMENT_TEMP,$AMPLITUDE,$TEMPERATUREINITIALE,$TEMPERATUREFINALE,$NB_REP_MAX,$(echo "\"$ALPHA\"" | tr '.' ','),\"$(moyenne 5)\"" >> ./res.csv
						done
					fi
				done
			done
		done
	done
done

make clean
