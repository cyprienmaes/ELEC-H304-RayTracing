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
    char existe = 0;
    if(wall->vertical == 1){
        if (round(transmission.y) < wall->position.y || round(transmission.y) > wall->position.y + wall->longueur) {
            existe = 0;
        }
        else {
            if((round(transmission.x) > round(avant.x) && round(transmission.x) < round(apres.x)) || (round(transmission.x) > round(apres.x) && round(transmission.x) < round(avant.x))) existe = 1;
            else existe = 0;
        }
    }
    else{
        if (round(transmission.x) < wall->position.x || round(transmission.x) > wall->position.x + wall->longueur) {
            existe = 0;
        }
        else {
            if((round(transmission.y) > round(avant.y) && round(transmission.y) < round(apres.y)) || (round(transmission.y) > round(apres.y) && round(transmission.y) < round(avant.y))) existe = 1;
            else existe = 0;
        }
    }
    return existe;
}

POINT *transList(int compte, POINT transmis, POINT *listeAvant, POINT *listeApres){
    int j = 0;
    listeApres = malloc((compte)*sizeof(POINT));
    // On regarde si l'autre tableau n'a pas deja des elements
    for (j=0;j<compte;j++){
        // On place les points transmis dans le tableau
        listeApres[j] = listeAvant[j];
    }
    listeApres[compte] = transmis;
    return listeApres;
}

POINT *transTrie(int compte, POINT avant, POINT *liste){
    int i = 0;
    POINT sauver = liste[compte-1];
    POINT intermediaire;
    for (i=1;i<compte;i++){
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

void changeCouleur(int changement,Uint8*r,Uint8*v,Uint8*b){
    switch (changement) {
        case 1 :
            // Il ne devrait a priori pas avoir plus de 5 transmissions
            *v +=55;
        case 2 :
            *r +=55;
        case 3 :
            *b +=55;
    }
}

void transLigne(int compte, int colorChange, POINT avant, POINT apres, POINT *listeTransmission, Uint8*r, Uint8*v, Uint8*b, SDL_Surface *screen){
    int j = 0;
    line(avant.x,avant.y,listeTransmission[0].x,listeTransmission[0].y,SDL_MapRGB(screen->format,*r,*v,*b),screen);
    changeCouleur(colorChange,r,v,b);
    for(j=0;j<compte-1;j++){
        line(listeTransmission[j].x,listeTransmission[j].y, listeTransmission[j+1].x,listeTransmission[j+1].y,SDL_MapRGB(screen->format,*r,*v,*b),screen);
        changeCouleur(colorChange,r,v,b);
    }
    line(listeTransmission[compte-1].x,listeTransmission[compte-1].y,apres.x,apres.y,SDL_MapRGB(screen->format,*r,*v,*b),screen);
}

void transmission(int colorChange, POINT avant, POINT apres, Uint8 *rouge,Uint8 *vert,Uint8 *bleu, WALL *wall, SDL_Surface *screen){
    int i = 0;
    POINT transmis;
    // Creation de deux tableaux dynamiques et d'une variable de comptage :
    POINT *transmission1 = NULL;
    POINT *transmission2 = NULL;
    int compte = 0;
    DROITE droiteDesPoints = createDroite(avant.x,avant.y,apres.x,apres.y);
    for (i = 0; i<numberWall;i++){
        transmis = intersection(droiteDesPoints,wall[i].droite);
        if(transExiste(avant,apres,transmis,&wall[i]) == 1){
            if (transmission1 == NULL) {
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
    // Des qu'il n'y a plus de nouveaux points de transmission on regarde les deux tableaux
    // et on verifie celui ou les points de transmission sont mis.
    if (transmission1 == NULL && transmission2 != NULL) {
        transmission2 = transTrie(compte,avant,transmission2);
        transLigne(compte,colorChange,avant,apres,transmission2,rouge,vert,bleu,screen);
    }
    if(transmission2 == NULL && transmission1 != NULL){
        transmission1 = transTrie(compte,avant,transmission1);
        transLigne(compte,colorChange, avant, apres, transmission1,rouge,vert,bleu,screen);
    }
    else if(transmission1 == NULL && transmission2 == NULL){
        line(avant.x,avant.y,apres.x,apres.y,SDL_MapRGB(screen->format,*rouge,*vert,*bleu),screen);
    }
}
