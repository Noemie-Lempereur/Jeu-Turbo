# **TURBO**

**_Turbo_** est un jeu de course développé en C++/Qt dans le cadre d'un projet noté.
Le but était de créer un jeu avec un personnage controlé avec les flèches du clavier. Des voitures vont vers le personnage et il faut les éviter. Les voitures vont de plus en plus vite. Les meilleurs scores doivent être enregistrés.


## Description

Vous incarnez une tortue ninja perdue en pleine autoroute !
Essayer de survivre en évitant les voitures.
Mais attention, plus vous survivez, plus les voitures iront vite.
Lorsque le niveau augmente, la vitesse augmente.

Il y a trois mode de jeux et un mode d'entrainement :

* Le mode normal :
     - 3 vies
     - 1 voiture à la fois

* Le mode difficile :
     - 3 vies
     - 1 à 2 voitures à la fois
     - plus rapide

* Le mode extreme :
     - 1 vie
     - 1 à 2 voitures à la fois
     - encore plus rapide

* Le mode entrainement :
     - Donne le nombre de collisions (infinité de vies)
     - vous decidez du nombre de voitures (à définir dans le menu Jeu->Entrainement)
     - vous decidez de la rapidité (à définir dans le menu Jeu->Entrainement) 

Serez vous capable de battre le meilleur score de chaque mode?


## Jouer

Pour jouer au jeu il suffit d'ouvrir le projet sur Clion et de lancer MobaXterm. Dans MobaXterm, faites "start a local terminal". Dans Clion, il faudra aller dans Run>EditConfigurations et changer le DISPLAY dans Environnement variables par le display de notre ordinateur.
La version du CMake utilisé est la version 3.10, si vous n'avez pas cette version, vous pouvez essayer de changer la ligne 1 du CMake.txt cmake_minimum_required(VERSION 3.10)

Les commandes minimales pour jouer sont :

 - Pour se déplacer d'une voie vers la gauche, utilisez la flèche de gauche.

 - Pour se déplacer d'une voie vers la droite, utilisez la flèche de droite.

Si vous voulez connaitre toutes les commandes, celles-ci sont affichés ci-dessous et vous pourrez les retrouver dans le menu Jeu->Commandes
Les règles sont affichées dans le menu Jeu->Règles

Pour connaitre les meilleurs scores de chaque mode, il faut aller dans le menu Jeu->Meilleurs Scores

N'oubliez pas de modifier les parametres du mode entrainement pour faire des entrainements personnalisés en fonction de vos faiblesses (plus rapide, 2 voitures...). Pour cela aller dans le menu Jeu->Entrainement

Si vous ne souhaitez pas jouer une tortue, vous pouvez changer la tortue en un escargot ou un humain dans le menu Jeu->Préferences->Skin

Si vous souhaitez changé la couleur des voitures, c'est possible dans le menu Jeu->Préferences->Voitures. Actullement, il y a deux couleurs possibles : rouge ou jaune


##Commandes

 - Touches "<-" et "->" pour se déplacer

 - Touche "P" pour mettre en pause ou reprendre le jeu

 - Touche "G" pour lancer la partie

 - Touche "N" pour redémarrer une partie

 - Touche "Q" pour arrêter la partie en enregistrant le score

 - Touche "R" pour afficher les règles du jeu

 - Touche "Echap" pour quitter l'application