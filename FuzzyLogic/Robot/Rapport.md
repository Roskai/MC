# Logique Flou

## Problème

Le problème auquel on s’interesse est celui du pilotage d’un robot mobile dans un environnement inconnu. L’objectif du robot est de rejoindre un ensemble de buts placés aleatoirement tout en evitant les obstacles presents.

## Méthode adopté

Nous avons adopté une methode incrémental. Nous avons commencer par faire fonctionner le robot dans la map vide, pour nous assurer que le robot arrive a ce déplacer dans un environnement.
Puis nous avons ajouter des règle pour gérer des obstacles simple comme dans la map1. Une fois que nous avons le robot qui arrive à contourner un obstacle simple, nous allons pouvoir passer avec plus d'obstacle avec la map3.

## Resultat

Nous avons un robot qui arrive a ce déplacer dans un labyrinthe de façon flou. Sous certaine condition il entre en colision avec un mur. Lorsque le robot est coincé il applique la technique du "Balancement". Il il se balance de droite a gauche avec un angle de plus en plus agrand jusqu'à trouvé une voix qui lui permette de sortir. Il se balance jusqu'a qu'il trouve une règle permettant de pouvoir continuer la recherche du but.

## Difficulté rencontré

Le fait de pouvoir contourner des obstacles et le fait de pouvoir soritr d'un cuvette ont fait partie des difficulté rencontrée.

## Point de blocage
