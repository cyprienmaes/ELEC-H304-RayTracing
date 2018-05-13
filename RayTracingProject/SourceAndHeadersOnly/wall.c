#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "droite.h"

int numberWall;

typedef struct WALL WALL;
struct WALL{
/*
Creation of different kinds of wall for reflexion and refraction.
*/
    float conductivity;
    float permitivity;
    char vertical;
    // Longueur du mur en toute generalite
    float longueur;
    float epaisseur;
    float posReeleX;
    float posReeleY;
    DROITE droite;
    // Position of the top left corner of a rectangle.
    SDL_Rect position;
    SDL_Surface *newWall;
};

void createWall(float echelle, char type, char vertical, float epaisseur, int longueur, int posX, int posY, SDL_Surface *screen, WALL *mur) {
/* Création d'un mur suivant les propriétés misent en paramètres :
   - verticale : 1 si oui 0 si non
   - posX et posY : position du coin haut gauche du mur
   - screen : fenêtre dans laquelle s'affiche le mur
*/
    mur->vertical = vertical;
    mur->longueur = longueur;
    // Attention l'epaisseur n'est pas celle affichee a l'ecran. C'est juste pour le calcul de puissance.
    mur->epaisseur = epaisseur;
    mur->posReeleX = posX;
    mur->posReeleY = posY;
    mur->position.x = round(posX/echelle);
    mur->position.y = round(posY/echelle);
    if(vertical){
            // Points par lequel traverse la droite du mur.
            mur->droite.x0 = posX; mur->droite.y0 = posY; mur->droite.x1 = posX; mur->droite.y1 = (posY+100);
            mur->newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, 4, round(longueur/echelle), 32, 0, 0, 0, 0);
    }
    else {
            mur->droite.x0 = posX; mur->droite.y0 = posY; mur->droite.x1 = (posX+100); mur->droite.y1 = posY;
            mur->newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, round(longueur/echelle)+4, 4, 32, 0, 0, 0, 0);
    }
    switch (type) {
        case 1 :
            // brique
            mur->conductivity = 0.02;
            mur->permitivity = 4.6;
            SDL_FillRect(mur->newWall, NULL, SDL_MapRGB(screen->format, 108, 0, 15));
            break;
        case 2 :
            // cloison
            mur->conductivity = 0.04;
            mur->permitivity = 2.25;
            SDL_FillRect(mur->newWall, NULL, SDL_MapRGB(screen->format, 230, 188, 90));
            break;
        case 3 :
            // beton
            mur->conductivity = 0.014;
            mur->permitivity = 5;
            SDL_FillRect(mur->newWall, NULL, SDL_MapRGB(screen->format, 90, 90, 90));
            break;
    }
    SDL_BlitSurface(mur->newWall, NULL, screen, &mur->position);
}

WALL *UnMur(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall) {
    numberWall = 1;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    // Largeur et hauteur ne doivent pas etre change car elles le sont deja dans le main.
    createWall(echelle,1,1,0,hauteurMap,largeurMap/2,0,screen,&wall[0]);
    return wall;
}

WALL *DeuxMurs(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall) {
    numberWall = 2;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        // Largeur et hauteur ne doivent pas etre change car elles le sont deja dans le main.
        createWall(echelle,1,0,0,largeurMap,0,i*hauteurMap,screen,&wall[i]);
    }
    return wall;
}

WALL *TroisMur(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall) {
    numberWall = 4;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        createWall(echelle,1,0,0,largeurMap,0,i*hauteurMap,screen,&wall[i]);
    }
    createWall(echelle,2,1,0,hauteurMap,largeurMap/2,0,screen,&wall[2]);
    createWall(echelle,2,1,0,hauteurMap,largeurMap/2+100,0,screen,&wall[3]);
    return wall;
}

WALL *SquareMap(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall){
    numberWall = 4;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        createWall(echelle,1,0,0,largeurMap,0,i*hauteurMap,screen,&wall[i]);
    }
    for(i=0;i<=1;i++) {
        createWall(echelle,2,1,0,hauteurMap,i*largeurMap,0,screen,&wall[i+2]);
    }
    return wall;
}

WALL *MapUn(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall) {
/*
Creation d'un plan d'etage plus ou moins realiste
*/
    numberWall = 12;
    wall = malloc(numberWall*sizeof(WALL));
    int i = 0;
    // Creation du cadre
    for(i=0;i<=1;i++){
        createWall(echelle,1,0,0,largeurMap, 0,i*hauteurMap,screen,&wall[i]);
    }
    for(i=0;i<=1;i++) {
        createWall(echelle,1,1,0,hauteurMap, i*largeurMap,0,screen,&wall[i+2]);
    }
    createWall(echelle,2,0,0,100,0,360,screen,&wall[4]);
    createWall(echelle,2,0,0,100,300,360,screen,&wall[5]);
    createWall(echelle,2,1,0,142,400,0,screen,&wall[6]);
    createWall(echelle,2,1,0,142,400,218,screen,&wall[7]);
    createWall(echelle,2,1,0,240,600,0,screen,&wall[8]);
    createWall(echelle,2,1,0,40,600,316,screen,&wall[9]);
    createWall(echelle,2,0,0,60,600,360,screen,&wall[10]);
    createWall(echelle,2,0,0,662,736,360,screen,&wall[11]);
    return wall;
}

WALL *MapDeux(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall){
    numberWall = 17;
    wall = malloc(numberWall*sizeof(WALL));
    // Les 4 murs exterieurs ont en betons
    createWall(echelle,3,0,19e-2,largeurMap,0,0,screen,&wall[0]);
    createWall(echelle,3,0,19e-2,largeurMap,0,hauteurMap,screen,&wall[1]);
    createWall(echelle,3,1,19e-2,hauteurMap,largeurMap,0,screen,&wall[2]);
    createWall(echelle,3,1,19e-2,325,0,0,screen,&wall[3]);
    createWall(echelle,3,1,19e-2,hauteurMap-425,0,425,screen,&wall[4]);
    // Les murs interieurs sont presque tous en cloisons
    createWall(echelle,2,0,13e-2,175,0,300,screen,&wall[5]);
    createWall(echelle,2,0,13e-2,175,275,300,screen,&wall[6]);
    createWall(echelle,2,1,15e-2,300,450,0,screen,&wall[7]);
    createWall(echelle,2,0,13e-2,75,450,200,screen,&wall[8]);
    createWall(echelle,2,0,13e-2,100,625,200,screen,&wall[9]);
    createWall(echelle,2,1,15e-2,200,700,0,screen,&wall[10]);
    createWall(echelle,2,0,13e-2,24,825,200,screen,&wall[11]);
    createWall(echelle,2,1,15e-2,300,850,0,screen,&wall[12]);
    createWall(echelle,2,0,13e-2,100,850,300,screen,&wall[13]);
    createWall(echelle,2,0,13e-2,350,1050,300,screen,&wall[14]);
    // mur en brique
    createWall(echelle,1,0,20e-2,750,0,450,screen,&wall[15]);
    createWall(echelle,1,1,20e-2,250,850,450,screen,&wall[16]);
    return wall;
}

WALL *MapExempleRapport1(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall){
    numberWall = 1;
    wall = malloc(numberWall*sizeof(WALL));

    createWall(echelle, 2, 1,  0.15, 700,   300,           0, screen, &wall[0]);

    return wall;
}

WALL *MapExempleRapport2(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall){
    numberWall = 3;
    wall = malloc(numberWall*sizeof(WALL));

    createWall(echelle, 3, 0,  0.2, 1400,   0,   0, screen, &wall[0]);
    createWall(echelle, 3, 0,  0.2, 1400,   0, 500, screen, &wall[1]);

    createWall(echelle, 2, 1, 0.15,  500, 600,   0, screen, &wall[2]);

    return wall;
}


void freeWALL(WALL *wall) {
    int i = 0;
    for (i=0; i<numberWall; i++) {
    SDL_FreeSurface(wall[i].newWall);
    }
}
