# Systèmes Teampe Réel - TP - 1 - Rappels

## Exercice 1.4

### Question 1.4.1

On a deux problèmes producteur/consommateur :

* Air : 
    * Producteur : `ApprocheAvion`
    * Buffer : `Air`
    * Consommatteur : `Aterrissage`
* Sol : 
    * Producteur : `SortirAvion`
    * Buffer : `Sol`
    * Consommatteur : `Decollage`

Il pour résoudre ce problème, il faut deux sémaphores pour chaque problème producteur / consommateur.
Il en faut donc quatre en tout.

Appellons les : 
* Air : 
    * Semaphore 1 : `libAir` a pour valeur initiale `N`
    * Semaphore 2 : `occAir` a pour valeur initiale 0
* Sol : 
    * Semaphore 1 : `libSol` a pour valeur initiale `M`
    * Semaphore 2 : `occSol` a pour valeur initiale 0
    
### Question 1.4.2

#### ApprocheAvion
```
P(libAir)
Faire approcher un avion
V(occAir)
```
#### Aterrissage
```
P(occAir)
Faire atterir l'avion
V(libAir)
```
#### SortirAvion
```
P(libSol)
Faire sortir un avion du hangar
V(occSol)
```
#### Decollage
```
P(occSol)
Faire décoller l'avion
V(libSol)
```
### Question 1.4.3
L'odre de prise des sémaphore est très important, sinon il y a risque d'interblocage (deadlock)

### Question 1.4.4

Voir `main.c`

### Question 1.4.5

Pour gérer plusieurs piste, il faudrait rajouter quatre mutex, deux pour l'air et deux pour le sol.
Respectivement : `mutexApproche`, `mutexAtterissage`, `mutexSortie`, `mutexDecollage`.
Elles seraient utilisées ainsi : 

#### ApprocheAvion
```
P(libAir)
P(mutexApproche)
Faire approcher un avion
V(mutexApproche)
V(occAir)
```
#### Aterrissage
```
P(occAir)
P(mutexAtterissage)
Faire atterir l'avion
V(mutexAtterissage)
V(libAir)
```
#### SortirAvion
```
P(libSol)
P(mutexSortie)
Faire sortir un avion du hangar
V(mutexSortie)
V(occSol)
```
#### Decollage
```
P(occSol)
P(mutexDecollage)
Faire décoller l'avion
V(mutexDecollage)
V(libSol)
```