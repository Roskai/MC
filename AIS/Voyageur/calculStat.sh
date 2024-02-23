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
			#echo "$count : $number"
			((count++))
		else
			echo "Erreur : '$number' n'est pas un nombre à virgule flottante valide."
		fi
		#sleep 1
	done

	if [ $count -gt 0 ]; then
		average=$(awk "BEGIN {printf \"%.10f\", $total / $count}")
		#echo "Moyenne pour $2 $3 $4 $5 $6 : $average"
		echo $average
	else
		echo "Aucun nombre à virgule flottante valide trouvé."
	fi
}

function set_param() {
	file=./params_change.h

	rm $file
	touch $file

	echo "#define METHODESELECTION $METHODESELECTION" >> $file
	echo "#define METHODEMUTATION $METHODEMUTATION" >> $file
	echo "#define NBMAXMUTATIONS $NBMAXMUTATIONS" >> $file
	echo "#define NBVILLES $NBVILLES" >> $file

	make clean > null
	make > null
}

touch ./result.csv

for nbgeninjection in 20 50 100
do
	echo change1
	for nbnouveaux in 25 50 75
	do
		echo change2
		for nbvilles in 100 30
		do
			NBVILLES=$nbvilles
			for mutation in 0 1 2
			do
				METHODEMUTATION=$mutation
				for selection in 0 1
				do
					METHODESELECTION=$selection
					set_param
					for taillepop in 350
					do
						for nbgeneration in 350
						do
							for nbclones in 45
							do
								echo "$(moyenne $1 $taillepop $nbclones $nbnouveaux $nbgeneration $nbgeninjection)"
							done
						done
					done
				done
			done
		done
	done
done



# for nbvilles in 100 30 8
# do
# 	NBVILLES=$nbvilles
# 	echo "NbVilles : $nbvilles" >> ./result.txt
# 	for selection in 0 1
# 	do
# 		METHODESELECTION=$selection
# 		echo "   Selection : $selection" >> ./result.txt
# 		for mutation in 0 1 2
# 		do
# 			METHODEMUTATION=$mutation
# 			echo "      Mutation : $mutation" >> ./result.txt
# 			for nbmaxmutations in 3 1
# 			do
# 				NBMAXMUTATIONS=$nbmaxmutations
# 				echo "         NbMutations : $nbmaxmutations" >> ./result.txt
# 				set_param
# 				for taillepop in 100 350 1000
# 				do
# 					for nbclones in 25 50 75
# 					do
# 						for nbnouveaux in 25 50 75
# 						do
# 							for nbgeneration in 100 350 1000
# 							do
# 								for nbgeninjection in 20 50 100
# 								do
# 									echo "            $(moyenne $1 $taillepop $nbclones $nbnouveaux $nbgeneration $nbgeninjection)" >> ./result.txt
# 								done
# 							done
# 						done
# 					done
# 				done
# 			done
# 		done
# 	done
# done