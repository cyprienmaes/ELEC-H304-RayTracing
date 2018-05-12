#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "line.h"
#include "wall.h"
#include "point.h"
#include "intersection.h"
#include "TXandRX.h"
#include "droite.h"

char transExiste(POINT avant, POINT apres, POINT transmission, WALL *wall){
/*
Fonction qui verifie que le point de transmission existe au sein du plan et qu'il soit associe a un mur bien defini.
*/
    char existe = 0;
    // On regarde si le point transmis se trouve bien dans les limites du plans
    // On doit faire -4 pour un mur etant au mimite du plan, car le seul point admis est sur la tranche de gauche ou du dessus.
    if(wall->vertical == 1){
        if (transmission.y < wall->position.y || transmission.y > wall->position.y + wall->longueur) {
            existe = 0;
        }
        else {
            if((transmission.x > avant.x && transmission.x < apres.x) || (transmission.x > apres.x && transmission.x < avant.x)) existe = 1;
            else existe = 0;
        }
    }
    else{
        if (transmission.x < wall->position.x || transmission.x > wall->position.x + wall->longueur) {
            existe = 0;
        }
        else {
            if((transmission.y > avant.y && transmission.y < apres.y) || (transmission.y > apres.y && transmission.y < avant.y)) existe = 1;
            else existe = 0;
        }
    }
    return existe;
}

POINT *transList(int compte, POINT transmis, POINT *listeAvant, POINT *listeApres){
/*
Fonction qui creer une liste selon une ancienne en reprenant ces termes et en ajoutant le point transmis suivant.
*/
    int j = 0;
    listeApres = malloc((compte+1)*sizeof(POINT));
    // On regarde si l'autre tableau n'a pas deja des elements
    for (j=0;j<compte;j++){
        // On place les points transmis dans le tableau
        listeApres[j] = listeAvant[j];
    }
    listeApres[compte] = transmis;
    return listeApres;
}

POINT *transTrie(int compte, POINT avant, POINT *liste){
/*
Fonction qui trie les points en fonction de la distance par rapport au point avant.
*/
    int i = 0;
    POINT sauver = liste[compte-1];
    POINT intermediaire;
    for (i=0;i<compte;i++){
        // On calcul les distances entre le point de source et les points de transmission et on les trie
        // dans le tableau.
        if (distance(avant,sauver)<distance(avant,liste[i])){
            intermediaire = liste[i];
            liste[i] = sauver;
            sauver = intermediaire;
        }
    }
    return liste;
}

void transmission(int INC1, int INC2, POINT avant, POINT apres, WALL *wall, SDL_Surface *screen){
/*
Fonction qui calcul tous les points de transmissions entre deux points. Ces points sont tries suivant la
plus courte distance du point avant. INC sont les indices des murs qu'on ne considerent pas, ceux lies aux
points avant et apres.
*/
    int i = 0;
    POINT transmis; // Variable contenant le point de transmission
    // Creation de deux tableaux dynamiques et d'une variable de comptage :
    POINT *transmission1 = NULL;
    POINT *transmission2 = NULL;
    int compte = 0; // Nombre de transmission calculee et existante
    DROITE droiteDesPoints = createDroite(avant.x,avant.y,apres.x,apres.y);
    for (i = 0; i<numberWall;i++){
        // On ne fait rien si les murs sont ceux lies aux points avant et apres
        if (i == INC1 || i == INC2);
        else {
            transmis = intersection(droiteDesPoints,wall[i].droite); // On calcul le point transmis
            transmis.x = round(transmis.x);                          // Et on l'arrondit pour coresspondre a la fenetre
            transmis.y = round(transmis.y);
            // On test si le point de transmission existe par rapport au longeur du mur et a la fenetre.
            if(transExiste(avant,apres,transmis,&wall[i]) == 1){
                if (transmission1 == NULL) {
                    // On liste un pointeur et puis l'autre. On calcul donc tous les points d'intersections
                    // sur une ligne
                    transmission1 = transList(compte,transmis,transmission2,transmission1);
                    // On vide la memoire du tableau precedent
                    free(transmission2);
                    // On le re-implemente a NULL
                    transmission2 = NULL;
                }
                else if(transmission2 == NULL && compte > 0){
                    transmission2 = transList(compte,transmis,transmission1,transmission2);
                    free(transmission1);
                    transmission1 = NULL;
                }
                compte += 1;
            }
        }
    }
    // Des qu'il n'y a plus de nouveaux points de transmission on regarde les deux tableaux
    // et on verifie celui ou les points de transmission sont mis.
    if (transmission1 == NULL && transmission2 != NULL) {
        // On trie les points selon la distance avant le point avant
        transmission2 = transTrie(compte,avant,transmission2);
    }
    else if(transmission2 == NULL && transmission1 != NULL){
        transmission1 = transTrie(compte,avant,transmission1);
    }
}
