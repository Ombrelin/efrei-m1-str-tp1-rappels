# TP 1 - Rappels / compléments - Thread & Synchronisation en langage C

Auteur : Fabien Calcado (tous droits réservés)

## Exercice 1.1

Ecrivez un programme composé de deux threads (lancés par votre fonction main). Le premier thread devra faire
deux affichages : "je "et "mes". Le deuxième fera également deux affichages : " synchronise " et "threads".
Utilisez des sémaphores pour que l'exécution du programme produise l'affichage de "je synchronise mes threads"
à l'écran quelque soit l'ordre de lancement des threads. Vous pourrez rajouter des attentes avant ou après les
affichages pour bien vérifier que cela n’a aucune influence sur l’ordre d’exécution une fois que les
synchronisations sont présentes.

Faire 2 versions du programme : l’une en utilisant des sémaphores et l’autre en utilisant des mutex.

Note :

- Utilisez la bibliothèque `<pthread.h>` pour créer les threads et la bibliothèque `<semaphore.h>` pour la
    gestion des sémaphores.
- Pour plus de lisibilité vous redéfinirez les primitives `sem_wait()` et `sem_post()` par des macro-fonctions
    `P()` et `V()`;
- Utilisez le flag ` -lpthread` pour pouvoir compiler le programme.

## Exercice 1.2

Ecrire un programme permettant de créer une barrière entre un groupe de N threads et un thread particulier qu’on
nommera « barrier_thread »par la suite. Une fois que « barrier_thread » aura atteint cette barrière il devra
attendre que chaque thread ait atteint un point bien particulier dans leur code (qui ne correspond pas forcément à
la fin des threads). On pourra simuler dans ces N threads l’exécution d’instructions avant d’atteindre ce point par
des attentes aléatoires (même si cela correspondra à une attente passive et non active).

Exemple d’exécution avec 3 threads + barrier_thread :

[thread 1] Point atteint
[b_thread] Barrière atteinte, en attente...
[thread 3] Point atteint
[thread 2] Point atteint
[b_thread] Je peux continuer!


## Exercice 1.3

Ecrire un programme permettant de lire et écrire dans un tampon partagé. Le problème est composé de deux
thread et d'un tampon partagé de taille N. Le thread "ecrivain" appelle une fonction ecrire_tampon(data) chargée
d'écrire dans le tampon partagé. Le thread "lecteur" appelle une fonction lecture_tampon() chargée de lire une
donnée précédemment écrite par la thread "ecrivain". Le tampon sera un simple tableau de N cases.

Indications :

- Le tampon est circulaire pour traiter les données dans l'ordre de production;
- Une lecture et une écriture doivent pouvoir se faire en parallèle si c'est pour des cases différentes;
- Pour plus de lisibilité vous redéfinirez les primitives `sem_wait()` et `sem_post()` par des macro-fonctions
    P() et V();
- Utilisez le flag -lpthread pour pouvoir compiler le programme.

## Exercice 1.4

L'exercice consiste à modéliser (très succinctement) un aérodrome possédant une unique piste d'atterrissage et de
décollage. L'aérodrome est composé d'une zone d'attente (limitée) proche de la piste permettant aux avions
d'attendre leur tour pour décoller et d'une zone d'approche (limitée) pour les avions souhaitant atterrir. Ce
système peut être représenté par deux files d'attente et quatre tâches (threads). Quand un avion se trouve dans
une ces files d'attente, il n'aura pas encore décollé ou atterri. Il aura effectivement décollé ou atterri lorsqu'il
disparaitra d'une des files d'attente.
Files d'attente:

- Air[] de taille N contenant les avions souhaitant atterrir représentant la zone d'approche;
- Sol[] de taille M contenant les avions souhaitant décoller représentant la zone d'attente de décollage.

Threads:

- SortirAvion qui sort les avions du hangar et les place dans le buffer d'attente de décollage;
- Decollage qui prend un avion du buffer d'attente et le fait décoller en utilisant la piste;
- ApprocheAvion qui place des avions dans le buffer d'attente d'atterrissage;
- Atterrissage qui prend un avion dans le buffer d'attente d'atterrissage et le fait atterrir en utilisant la piste.

### Question 1.4.1 
Quels sont les problèmes de type "producteur/consommateur" et de type "exclusion mutuelle"?
Préciser ensuite le nombre de sémaphore/mutex à utiliser ainsi que leurs valeurs initiales.

### Question 1.4.2 
Décrire de façon simple chaque processus à l'aide des primitives P et V et des sémaphores de la
question précédente. Indications : Il n'est pas nécessaire de faire apparaître la gestion des files d'attente pour cette
question.

### Question 1.4.3 
L'ordre de prise des sémaphores /mutex est-il important? Si oui, précisez le(s) problème(s) que
cela peut engendrer.

Question 1.4.4 
Implémentez le problème en utilisant la bibliothèque `<pthread.h>` pour créer les deux processus
et la bibliothèque `<semaphore.h>` pour la gestion des sémaphores.

Indications :

- Deux variables représenteront le nombre d'avions à faire atterrir et le nombre d'avions à faire décoller;
- En ce qui concerne la gestion des files d'attentes vous pourrez utiliser le travail effectué dans la première partie;
- Définition et gestion d'un mutex avec la bibliothèque <pthread.h> : pthread_mutex_t mutex ,pthread_mutex_lock(), pthread_mutex_unlock()
- Utilisez le flag -lpthread pour pouvoir compiler le programme

## Question 1.4.5 
Que faudrait-il modifier dans le programme (uniquement au niveau de la gestion des synchronisations) pour prendre en compte le fait qu'il y ait plusieurs pistes?


