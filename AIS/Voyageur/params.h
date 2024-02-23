#ifndef PARAMS_H
#define PARAMS_H

/**
 * @def AFFICHE
 * @brief Si a false (0) affiche uniquement le cout du meilleur resultat
 * @note Active ou désactive les GNU Plots et le détails des résultats (équivalent a un --verbose)
*/
#define AFFICHE 0

/**
 * @def METHODESELECTION
 * @brief Choix de la méthode de sélection pour l'algorithme génétique.
 *
 *
 * @note Valeurs possibles :\n
  @note - 0 : Méthode "2 à 2" \n
  @note - 1 : Tri de la population (sélection des meilleurs individus)\n
 */
#define METHODESELECTION 0
/**
 * @def METHODEMUTATION
 * @brief Choix de la méthode de mutation pour l'algorithme génétique.
 *
 *
  @note Valeurs possibles : \n
  @note - 0 : Échange de deux éléments dans l'individu \n
  @note - 1 : Inversion d'une portion de l'individu \n
  @note - 2 : Translation d'une portion de l'individu \n
 */
#define METHODEMUTATION 1

/**
 * @def NBMUTATIONDYNAMIQUE
 * @brief Determine si le nombre de mutations doit être fixe.
 * @see population.c
*/
#define NBMUTATIONDYNAMIQUE 1

#define NBMAXMUTATIONS 3

#define NBVILLES 1000


#define COTECARTE 100

/* DANS LA SUITE, NE PAS TOUCHER:
   TAILLEPOP, N, D, NBGENERATIONS, NBGENERATIONSINJECTION !!!
   ==> agir sur les parametres de la ligne de commande                */

#define TAILLEPOP 100
#define N 50 /* Selection: En % de TAILLEPOP (Max 100%!) */
#define D 20 /* Injection: En % de TAILLEPOP (Max 100%!) */

#define NBGENERATIONS 100
#define NBGENERATIONSINJECTION 20

#define NBCLONES (N * TAILLEPOP) / 100
#define NBNOUVEAUX (D * TAILLEPOP) / 100

/*********************************************************************/
/************ Verification contraintes sur les defines ***************/
/*********************************************************************/

#if NBVILLES > COTECARTE * COTECARTE
#error "Attention: NBVILLES>COTECARTE*COTECARTE"
#endif

#if N > 100
#error "Attention: N trop grand"
#endif

#if D > 100
#error "Attention: D trop grand"
#endif

#if METHODESELECTION > 1 || METHODESELECTION < 0
#error "Choix de la méthode de selection incorrecte"
#error "Doit être contenu ente 0 et 1"
#error " Valeurs possibles : "
#error "0 : Méthode 2 à 2 "
#error "1 : Tri de la population (sélection des meilleurs individus) "
#endif 

#if METHODEMUTATION > 3 || METHODEMUTATION < 0
#error "Choix de la méthode de mutation incorrecte"
#error "Doit être contenu ente 0 et 3"
#error " Valeurs possibles : "
#error "0 : Échange de deux éléments dans l'individu "
#error "1 : Inversion d'une portion de l'individu "
#error "2 : Translation d'une portion de l'individu "
#endif

#define ERROR_PARAM 0
#if TAILLEPOP != 100
#error "Attention: params.h, ne pas toucher TAILLEPOP !"
#error "==> agir sur les parametres de la ligne de commande"
#endif
#if N != 50
#error "Attention: params.h, ne pas toucher N !"
#error "==> agir sur les parametres de la ligne de commande"
#endif
#if D != 20
#error "Attention: params.h, ne pas toucher D !"
#error "==> agir sur les parametres de la ligne de commande"
#endif
#if NBGENERATIONS != 100
#error "Attention: params.h, ne pas toucher NBGENERATIONS !"
#error "==> agir sur les parametres de la ligne de commande"
#endif
#if NBGENERATIONSINJECTION != 20
#error "Attention: params.h, ne pas toucher NBGENERATIONSINJECTION !"
#error "==> agir sur les parametres de la ligne de commande"
#endif

#endif /* PARAMS_H */
