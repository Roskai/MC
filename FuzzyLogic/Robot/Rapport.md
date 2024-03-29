# Logique Flou

Pour développer et enrichir ces deux parties du rapport, commençons par approfondir le contexte du problème avant de détailler la méthode adoptée.
Pour rédiger les sections améliorées du rapport sur le travail pratique (TP) qui implique l'utilisation de la logique floue pour contrôler le comportement réactif d'un robot mobile dans un environnement inconnu, voici une version détaillée et enrichie :

## Problème Posé

Au cœur de ce TP réside le défi de piloter un robot mobile à travers un espace confiné de 20 mètres de côté, semé d'obstacles divers. L'objectif du robot est de localiser et de rejoindre plusieurs cibles disposées de manière aléatoire, tout en naviguant habilement pour éviter les obstacles présents. La complexité de cette tâche est exacerbée par le fait que le robot doit s'appuyer sur une perception locale et limitée de son environnement.

## Méthode Adoptée

Pour aborder ce problème complexe, une méthodologie incrémentale a été choisie, favorisant une approche étape par étape pour développer et affiner les capacités de navigation du robot. Cette approche méthodique permet une compréhension approfondie des principes de la logique floue appliquée à la robotique mobile et offre une opportunité de tester et d'ajuster les règles floues dans des scénarios de complexité croissante.

### Étapes de Développement

1. **Validation des Fonctionnalités de Base** : La première phase se concentre sur la confirmation des capacités motrices et de navigation de base du robot dans un environnement vierge. Cela comprend des tests de déplacement et d'orientation assurant ainsi que le robot est apte à entreprendre des tâches de navigation plus complexes.

2. **Introduction et Gestion des Obstacles Simples** : Avec les capacités de base validées, le projet passe à l'introduction d'obstacles simples dans l'environnement (map1). Cette étape vise à développer et tester des mécanismes de perception et d'évitement d'obstacles, utilisant des règles floues pour naviguer efficacement autour des obstacles sans assistance.

3. **Navigation dans des Environnements Complexes** : Finalement, le robot est mis à l'épreuve dans des scénarios de plus en plus complexes (map3), où il doit démontrer sa capacité à intégrer dynamiquement les informations sensorielles pour planifier et ajuster son trajet vers des cibles tout en naviguant autour d'une variété d'obstacles.
  
4. **Méthode du balancement** : Lorsque le robot détecte qu'il est face à un obstacle et qu'un mouvement en avant direct n'est plus possible, il commence à tourner alternativement à droite et à gauche, augmentant progressivement l'angle de rotation à chaque oscillation. Ce processus continue jusqu'à ce que le robot identifie une voie libre lui permettant de contourner l'obstacle et de reprendre sa progression. Le balancement permet ainsi au robot de sonder l'environnement proche pour des chemins alternatifs, offrant une solution simple mais efficace pour surmonter les blocages sans nécessiter un recalcul complet du trajet.

##  Règle et valeurs linguistiques

Dans ce chapitre, nous allons explorer en détail le système de règles de la logique floue mis en place pour piloter un robot mobile dans un environnement inconnu. Ce système utilise des variables linguistiques pour traduire les données sensorielles et les états du robot en termes compréhensibles, permettant ainsi de définir des comportements complexes à travers un ensemble de règles floues.

### Définition des variables et valeurs linguistiques

La première étape dans la conception de notre système de contrôle flou consiste à définir les variables linguistiques et leurs valeurs. Ces variables représentent les entrées (la distance et la direction par rapport à l'objectif ou un obstacle) et les sorties (la vitesse et la direction du robot) du système. Voici les variables linguistiques et leurs valeurs utilisées :

- **DistGoal (Distance jusqu'à l'objectif)**
  - `proche` : Une distance faible entre le robot et son objectif, définie par une rampe basse entre 30 et 80 cm.
  - `aBonneDistance` : Une distance optimale pour le mouvement, définie par un triangle entre 30, 55, et 80 cm.
  - `loin` : Une distance importante nécessitant potentiellement d'accélérer, définie par une rampe haute entre 30 et 80 cm.
  - `doitFreiner` : Une distance critique où le robot doit ralentir ou s'arrêter, définie par une rampe basse entre 100 et 200 cm.

- **DirecGoal (Direction de l'objectif)**
  - `derriereADroite`, `aDroite`, `devant`, `aGauche`, `derriereAGauche` : Ces valeurs décrivent la position relative de l'objectif par rapport au robot, facilitant la décision de tourner à droite, à gauche, ou de continuer tout droit.

- **Slin (Vitesse linéaire) et Sang (Vitesse angulaire)**
  - Ces variables contrôlent respectivement la vitesse à laquelle le robot avance ou recule, et la rapidité avec laquelle il tourne. Les valeurs vont de mouvements avant/arrière rapides à des ajustements plus fins, comme `enMarcheAvant`, `aLArret`, ou `tourneADroite`.

### Règles de la logique floue

Le cœur de notre système de contrôle est un ensemble de règles floues qui décrivent comment le robot doit réagir en fonction de différentes situations. Ces règles utilisent les valeurs linguistiques des variables d'entrée pour déterminer les actions à effectuer (variables de sortie). Voici quelques exemples de règles :

- **Gestion de la vitesse :**
  - Si le robot est orienté vers son objectif (`toutDroit`) et qu'aucun obstacle ne requiert de freiner (`pas doitFreiner`), alors il peut avancer (`enMarcheAvant`).
  - Si face à un obstacle nécessitant un freinage (`doitFreiner`) et si le robot avançait (`enMarcheAvant`), il passe en marche arrière (`enMarcheArriere`) pour éviter la collision.

- **Ajustement de la direction :**
  - Si le robot doit tourner extrêmement à droite pour atteindre son objectif derrière lui à droite (`derriereADroite`), la vitesse angulaire est ajustée pour un virage serré (`tourneExtremementADroite`).

- **Gestion des blocages :**
  - Lorsque le robot est à l'arrêt (`aLArret`) et bloqué par un obstacle sur le côté droit (`procheDeCote`), il doit tourner à gauche (`tourneAGauche`) pour se dégager.

## Resultat

Nous avons un robot qui arrive a ce déplacer dans un labyrinthe de façon flou. Sous certaine condition il entre en colision avec un mur. Lorsque le robot est coincé il applique la technique du "Balancement". Il il se balance de droite a gauche avec un angle de plus en plus agrand jusqu'à trouvé une voix qui lui permette de sortir. Il se balance jusqu'a qu'il trouve une règle permettant de pouvoir continuer la recherche du but.

## Difficulté rencontré

Le fait de pouvoir contourner des obstacles et le fait de pouvoir soritr d'un cuvette ont fait partie des difficulté rencontrée.

## Point de blocage
