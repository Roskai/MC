# Logique Flou

Pour développer et enrichir ces deux parties du rapport, commençons par approfondir le contexte du problème avant de détailler la méthode adoptée.

## Problème Approfondi

Le pilotage autonome d'un robot mobile dans un environnement inconnu représente un défi significatif en robotique. L'objectif principal de ce projet est de développer un système permettant à un robot de naviguer de manière autonome, en identifiant et en rejoignant des cibles définies aléatoirement, tout en évitant les obstacles qui se présentent sur son chemin. Cette tâche implique plusieurs sous-problèmes complexes :

- **Perception de l'environnement** : Le robot doit être capable de percevoir son environnement avec précision. Cela inclut la détection d'obstacles, la reconnaissance de l'espace navigable, et l'identification des cibles. La perception doit être effective même dans des environnements non structurés ou dynamiques, où les obstacles et les cibles peuvent changer de position ou apparaître soudainement.

- **Planification de chemin** : Après avoir perçu son environnement, le robot doit planifier un chemin pour atteindre ses cibles tout en évitant les obstacles. Cette planification doit être dynamique, s'adaptant en temps réel aux changements perçus dans l'environnement.

- **Exécution et adaptation** : Le robot doit ensuite exécuter le chemin planifié. Pendant l'exécution, il doit continuellement adapter sa trajectoire en réponse à de nouvelles informations sensorielles, corrigeant tout écart par rapport au chemin prévu et répondant efficacement aux imprévus.

## Méthode Adoptée Développée

Pour aborder ce problème, une approche méthodologique incrémentale a été choisie, permettant une validation progressive des solutions développées et une adaptation flexible aux défis rencontrés.

### Phase 1 : Navigation dans un Environnement Vide

La première étape a consisté à tester la capacité du robot à se déplacer dans un environnement complètement vide. Cette phase initiale avait pour but de vérifier l'efficacité de nos règles de base pour la navigation et la détection de direction.

### Phase 2 : Gestion des Obstacles Simples

Après avoir confirmé que le robot pouvait naviguer efficacement dans un espace vide, l'étape suivante a introduit des obstacles simples dans l'environnement (map1). Cette phase visait à :

- **Développer et Tester la Perception des Obstacles** : Intégrer et affiner les capacités de perception sensorielle du robot pour détecter et identifier correctement les obstacles simples.
- **Implémenter la Stratégie d'Évitement** : Développer et tester des stratégies d'évitement d'obstacles, en utilisant la logique floue pour permettre au robot de prendre des décisions de navigation en temps réel basées sur les données sensorielles.

### Phase 3 : Navigation dans des Environnements Complexes

La finalité de cette approche incrémentale est de préparer le robot à opérer dans des environnements de plus en plus complexes, avec de multiples obstacles (map3). Cette phase inclut :

- **Complexification de l'Environnement** : Introduire une variété d'obstacles et de configurations spatiales pour tester la robustesse des stratégies d'évitement et de navigation du robot.
- **Optimisation de la Planification de Chemin** : Améliorer les algorithmes de planification de chemin pour optimiser l'efficacité du parcours, en tenant compte de la dynamique de l'environnement et de la position aléatoire des cibles.
- **Adaptation et Apprentissage** : Permettre au robot d'apprendre de son environnement et de ses expériences passées pour améliorer continuellement ses capacités de navigation et d'évitement d'obstacles.

En suivant cette méthodologie incrémentale, le projet vise à construire progressivement un système de navigation autonome robuste et adaptable, capable de relever les défis posés par des environnements inconnus et en constante évolution.

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
