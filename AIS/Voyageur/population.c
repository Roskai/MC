/* population.c : la population d'anticorps */
#include <stdio.h>
#include <math.h>	/* Pour fabs  */
#include <stdlib.h> /* Pour qsort */
#include <unistd.h> /* Pour sleep */

#include "params.h"
#include "anticorps.h"
#include "population.h"

/**********************************************************************/
/********* Une Population *********************************************/
/**********************************************************************/
/*
typedef struct { Ac* *individus;     // Tableau alloue dynamiquement d'Ac*
				 Ac* *clones;        // Pointeur vers la zone des clones
				 int nbIndividus;
				 int nbClones;
			   }                             Population;
*/

/* Generation d'une Population */
void generePopulation(Population *population,
					  int nbIndividus, int nbClones)
{
	int i = 0;
	int nbIndividus_Plus_nbClones; /* Par la suite, aura pour valeur:
									  population->nbIndividus
												+
									  population->nbClones
								   */
	if (nbIndividus <= 0)
	{
		printf("**** Warning ! **** : nbIndividus <= 0 (generePopulation)\n");
		nbIndividus = 0;
		exit(EXIT_FAILURE); /* Travailler avec une population vide ...? bof ! */
	}

	if (nbClones <= 0)
	{
		printf("**** Warning ! **** : nbClones <= 0 (generePopulation)\n");
		nbClones = 0;
	}

	if (nbClones > nbIndividus)
	{
		printf("**** Warning ! **** : nbClones > nbIndividus (generePopulation)\n");
		nbClones = nbIndividus;
	}

	population->nbIndividus = nbIndividus;
	population->nbClones = nbClones;

	nbIndividus_Plus_nbClones = population->nbIndividus + population->nbClones;

	if (nbIndividus_Plus_nbClones == 0)
	{
		population->individus = NULL;
		population->clones = NULL;
	}
	else
	{
		/* Allocation pour les individus et pour les clones d'un seul coup */
		population->individus = (Ac **)malloc(nbIndividus_Plus_nbClones * sizeof(Ac *));
		if (population->individus == NULL)
		{
			printf("Erreur::generePopulation, "
				   "probleme sur malloc Ac*\n");
			exit(EXIT_FAILURE);
		}
		/* Et on positionne le pointeur population->clones ou il faut */
		population->clones = population->individus + population->nbIndividus;
	}

	for (i = 0; i < population->nbIndividus; i++)
	{
		Ac *ac = (Ac *)malloc(sizeof(Ac));
		if (ac == NULL)
		{
			printf("Erreur::generePopulation,"
				   "probleme sur malloc Ac-1\n");
			exit(EXIT_FAILURE);
		}
		population->individus[i] = ac;
	}

	for (i = 0; i < population->nbIndividus; i++)
	{
		genereAc(population->individus[i]);
	}

	for (i = 0; i < population->nbClones; i++)
	{
		Ac *ac = (Ac *)malloc(sizeof(Ac));
		if (ac == NULL)
		{
			printf("Erreur::generePopulation,"
				   "probleme sur malloc Ac-2\n");
			exit(EXIT_FAILURE);
		}
		population->clones[i] = ac;
	}

	/* Pas utile... sauf si la suite est mal utilisee */
	for (i = 0; i < population->nbClones; i++)
	{
		genereAc(population->clones[i]);
	}
}

/* Destruction d'une population: individus + clones    */
void supprimePopulation(Population *population)
{
	int i = 0;

	if (population->individus)
	{
		for (i = 0; i < population->nbIndividus; i++)
		{
			free(population->individus[i]);
		}
	}

	if (population->clones)
	{
		for (i = 0; i < population->nbClones; i++)
		{
			free(population->clones[i]);
		}
	}

	if (population->individus)
		free(population->individus);
}

/* Affichage des meilleurs individus de la Population  */
/* Pour afficher toute la population =>  nbIndividus=0 */
void printIndividusPopulation(Population *population, int nbIndividus)
{
	int i = 0, borne = 0;

	if (nbIndividus == 0)
		borne = 0;
	else
		borne = population->nbIndividus - nbIndividus;
	borne = (borne < 0) ? 0 : borne;

	if (borne == 0)
		printf("Affichage de la population entiere\n");
	else
		printf("Affichage des %d meilleurs individus de la population\n",
			   population->nbIndividus - borne);

	for (i = borne; i < population->nbIndividus; i++)
	{
		printAc(population->individus[i]);
	}
}

/* Dessin des meilleurs individus de la Population     */
/* Pour dessiner toute la population =>  nbIndividus=0 */
void dessineIndividusPopulation(FILE *flot,
								Population *population, int nbIndividus)
{
	int i = 0, borne = 0;

	if (nbIndividus == 0)
		borne = 0;
	else
		borne = population->nbIndividus - nbIndividus;
	borne = (borne < 0) ? 0 : borne;

	if (borne == 0)
		printf("Dessin de la population entiere\n");
	else
		printf("Dessin des %d meilleurs individus de la population\n",
			   population->nbIndividus - borne);

	for (i = borne; i < population->nbIndividus; i++)
	{
		dessineAc(flot, population->individus[i]);
		sleep(1);
	}
}

/*-------------*/
/* Comparaison du COUT de deux Anti-Corps :            */
/* Si vis a vis du cout :                              */
/* ac1 < ac2 => retour < 0                             */
/* ac1 = ac2 => retour = 0                             */
/* ac1 > ac2 => retour > 0                             */
static int compareAc(const void *ac1, const void *ac2)
{
	Ac *ac1P = (Ac *)ac1;
	Ac *ac2P = (Ac *)ac2;

	if (fabs(ac1P->cout - ac2P->cout) < 0.00001)
		return 0;
	if (ac1P->cout < ac2P->cout)
		return -1;
	else
		return 1;
}

/* Pour qsort,                                                */
/* comparaison du cout de deux Anti-Corps (via les pointeurs) */
/* Avec qsort, tri avec un cout CROISSANT                     */

static int compareAcPtr(const void *ac1, const void *ac2)
{
	Ac **ac1P = (Ac **)ac1;
	Ac **ac2P = (Ac **)ac2;

	return compareAc(*ac1P, *ac2P);
}
/*---*/
/* Pour qsort,                                                */
/* comparaison du cout de deux Anti-Corps (via les pointeurs) */
/* Avec qsort, tri avec un cout DECROISSANT                   */
static int compareInvAcPtr(const void *ac1, const void *ac2)
{
	return -compareAcPtr(ac1, ac2);
}

/*-------------*/
/* Tri d'une Sous Population et calcul du meilleur avec       */
/* un COUT DECROISSANT =>                                     */
/* les moins bons sont a gauche, les meilleurs a droite       */
static void triSousPopulation(Population *population,
							  int indiceDebut, int nbIndividusSousPopulation)
{
	if (nbIndividusSousPopulation > 0)
	{
		qsort(population->individus + indiceDebut, nbIndividusSousPopulation,
			  sizeof(Ac *), compareInvAcPtr);
	}
}
/*---*/
void triPopulation(Population *population)
{
	triSousPopulation(population, 0, population->nbIndividus);
}

/*** Il faut un tri avant ***/
/* Recuperation du meilleur individu */
Ac meilleurIndividu(Population *population)
{
	return *(population->individus[population->nbIndividus - 1]);
}

/*** Il faut que la population soit triee   ***/
/*** (les meilleurs doivent etre a droite). ***/
void clonageMeilleurs(Population *population)
{
	int i = 0;
	int nbClones = population->nbClones;

	for (i = 0; i < nbClones; i++)
	{
		int indiceAc;
		int indiceClone;

		indiceAc = population->nbIndividus - nbClones + i; /*  meilleur  */
		indiceClone = i;								   /*   clone    */

		cloneAc(population->individus[indiceAc],
				population->clones[indiceClone]);
	}
}

/*** Il faut un clonage avant ....                               ***/
void mutationClones(Population *population)
{
	/* Plus un clone est a droite, meilleur il est.                   */
	/* On peut ainsi faire varier le nombre de mutations a effectuer. */
	/* Dans un premier temps, le nombre de mutations peut etre fixe.  */

	for (size_t i = 0; i < population->nbClones; i++)
	{
		muteAc(population->clones[i], 1);
	}
}
/**
 * Sélectionne les meilleurs individus et les clones mutés dans la population.
 *
 * Cette fonction compare chaque paire d'individus (meilleur, clone muté) et conserve
 * le meilleur entre les deux. Il existe deux méthodes de sélection, activées par la
 * directive METHODESELECTION.
 *
 * - Si METHODESELECTION est défini à 0 :
 *   - La sélection se fait en comparant chaque paire (meilleur, clone) individuellement.
 *   - Le meilleur individu est conservé dans le tableau des clones, et le clone dans le tableau des individus.
 *
 * - Si METHODESELECTION est défini à 1 :
 *   - La population totale (individus et clones) est triée par ordre décroissant de .
 *   - Les meilleurs individus (en haut du classement) sont conservés dans le tableau des individus.
 *   - Les clones mutés sont placés dans le tableau des clones, en correspondance avec les meilleurs individus.
 *
 * @param population Pointeur vers la structure Population contenant les individus et les clones.
 */
void selectionMeilleursEtClonesMutes(Population *population)
{
	int deltaNbIndividusEtNbClones = population->nbIndividus - population->nbClones;
#if METHODESELECTION == 0 // Selection 2 à 2
	for (size_t i = 0; i < population->nbClones; i++)
	{
		Ac *indiv = population->individus[deltaNbIndividusEtNbClones + i];
		Ac *clone = population->clones[i];

		if (compareAc(indiv, clone) > 0)
		{
			population->clones[i] = indiv;
			population->individus[deltaNbIndividusEtNbClones + i] = clone;
		}
	}
#else // Selection par tri ensemble

	triSousPopulation(population,
					  deltaNbIndividusEtNbClones,
					  2 * population->nbClones);

	for (size_t i = 0; i < population->nbClones; i++)
	{
		Ac *temp = population->individus[deltaNbIndividusEtNbClones + i];
		population->individus[deltaNbIndividusEtNbClones + i] = population->clones[i];
		population->clones[i] = temp;
	}

#endif
}

/*** Les moins bons doivent etre a gauche (apres un tri par exemple) ***/
void mutationMoinsBons(Population *population)
{
	/* Plus un mauvais est a droite, meilleur il est!                 */
	/* On peut ainsi faire varier le nombre de mutations a effectuer. */
	/* Dans un premier temps, le nombre de mutations peut etre fixe.  */
	int nbMutation = 1; // TODO : Fixe pour l'instant

	for (size_t i = 0; i < population->nbIndividus - population->nbClones; i++)
	{
		muteAc(population->individus[i], nbMutation);
	}
}

/*** Les moins bons doivent etre a gauche (apres un tri par exemple) ***/
void remplacementMauvaisParNouveaux(Population *population, int nbNouveaux)
{
	for (size_t i = 0; i < nbNouveaux; i++)
	{
		genereAc(population->individus[i]);
	}
}
