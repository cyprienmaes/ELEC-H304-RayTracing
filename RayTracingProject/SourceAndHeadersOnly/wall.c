#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "droite.h"

#define scaling 1.7

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
    DROITE droite;
    // Position of the top left corner of a rectangle.
    SDL_Rect position;
    SDL_Surface *newWall;
};

void createWall(char type, char vertical, float epaisseur, float longueur, int posX, int posY, SDL_Surface *screen, WALL *mur) {
/* Création d'un mur suivant les propriétés misent en paramètres :
   - verticale : 1 si oui 0 si non
   - posX et posY : position du coin haut gauche du mur
   - screen : fenêtre dans laquelle s'affiche le mur
*/
    mur->vertical = vertical;
    mur->longueur = longueur;
    // Attention l'epaisseur n'est pas celle affichee a l'ecran. C'est juste pour le calcul de puissance.
    mur->epaisseur = epaisseur;
    mur->position.x = posX;
    mur->position.y = posY;
    if(vertical){
            // Points par lequel traverse la droite du mur.
            mur->droite.x0 = posX; mur->droite.y0 = posY; mur->droite.x1 = posX; mur->droite.y1 = (posY+100);
            mur->newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, 4, longueur, 32, 0, 0, 0, 0);
    }
    else {
            mur->droite.x0 = posX; mur->droite.y0 = posY; mur->droite.x1 = (posX+100); mur->droite.y1 = posY;
            mur->newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, longueur, 4, 32, 0, 0, 0, 0);
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

WALL *DeuxMurs(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap) {
    numberWall = 2;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        createWall(1,0,0,largeurMap/scaling,0,i*((hauteurMap/scaling)-4),screen,&wall[i]);
    }
    return wall;
}

WALL *UnMur(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap) {
    numberWall = 1;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    createWall(1,1,0,(hauteurMap/scaling)-8,(largeurMap/scaling)/2,4,screen,&wall[0]);
    return wall;
}

WALL *TroisMur(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap) {
    numberWall = 4;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        createWall(1,0,0,largeurMap/scaling,0,i*((hauteurMap/scaling)-4),screen,&wall[i]);
    }
    createWall(1,1,0,(hauteurMap/scaling)-8,(largeurMap/scaling)/2,4,screen,&wall[2]);
    createWall(1,1,0,(hauteurMap/scaling)-8,(largeurMap/scaling)/2+100,4,screen,&wall[3]);
    return wall;
}

WALL *SquareMap(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap){
    numberWall = 4;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        createWall(1,0,0,largeurMap/scaling,0,i*((hauteurMap/scaling)-4),screen,&wall[i]);
    }
    for(i=0;i<=1;i++) {
        createWall(1,1,0,(hauteurMap/scaling)-8,i*((largeurMap/scaling)-4),4,screen,&wall[i+2]);
    }
    return wall;
}

WALL *MapUn(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap) {
/*
Creation d'un plan d'etage plus ou moins realiste
*/
    numberWall = 12;
    wall = malloc(numberWall*sizeof(WALL));
    int i = 0;
    // Creation du cadre
    for(i=0;i<=1;i++){
        createWall(1,0,0,largeurMap/scaling, 0,i*((hauteurMap/scaling)-4),screen,&wall[i]);
    }
    for(i=0;i<=1;i++) {
        createWall(1,1,0,(hauteurMap/scaling)-8, i*((largeurMap/scaling)-4),4,screen,&wall[i+2]);
    }
    createWall(2,0,0,(100/scaling)-4,4,(360/scaling)-4,screen,&wall[4]);
    createWall(2,0,0,100/scaling,300/scaling,(360/scaling)-4,screen,&wall[5]);
    createWall(2,1,0,138/scaling,(400/scaling)-4,4,screen,&wall[6]);
    createWall(2,1,0,138/scaling,(400/scaling)-4,218/scaling,screen,&wall[7]);
    createWall(2,1,0,236/scaling,600/scaling,4,screen,&wall[8]);
    createWall(2,1,0,40/scaling,600/scaling,316/scaling,screen,&wall[9]);
    createWall(2,0,0,60/scaling,600/scaling,(360/scaling)-4,screen,&wall[10]);
    createWall(2,0,0,(384/scaling)-4,736/scaling,(360/scaling)-4,screen,&wall[11]);
    return wall;
}

WALL *MapDeux(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap){
    numberWall = 18;
    wall = malloc(numberWall*sizeof(WALL));
    // Les 4 murs exterieurs ont en betons
    createWall(3,0,19e-2,largeurMap/scaling,0, 0,screen,&wall[0]);
    createWall(3,0,19e-2,largeurMap/scaling,0, (hauteurMap/scaling)-4,screen,&wall[1]);
    createWall(3,1,19e-2,(hauteurMap/scaling)-8,(largeurMap/scaling)-4,4,screen,&wall[2]);
    createWall(3,1,19e-2,325/scaling,0,4,screen,&wall[3]);
    createWall(3,1,19e-2,((hauteurMap-425)-4)/scaling,0,425/scaling,screen,&wall[4]);
    // Les murs interieurs sont presque tous en cloisons
    createWall(2,0,13e-2,175/scaling,1,300/scaling,screen,&wall[5]);
    createWall(2,0,13e-2,175/scaling+4,276/scaling,300/scaling,screen,&wall[6]);
    createWall(2,1,15e-2,299/scaling,451/scaling,1,screen,&wall[7]);
    createWall(2,0,13e-2,75/scaling,452/scaling,200/scaling,screen,&wall[8]);
    createWall(2,0,13e-2,104/scaling,627/scaling,200/scaling,screen,&wall[9]);
    createWall(2,1,15e-2,199/scaling,702/scaling,1,screen,&wall[10]);
    createWall(2,0,13e-2,25/scaling,831/scaling,200/scaling,screen,&wall[11]);
    createWall(2,1,15e-2,299/scaling,856/scaling,1,screen,&wall[12]);
    createWall(2,0,13e-2,100/scaling,856/scaling,300/scaling,screen,&wall[13]);
    createWall(2,0,13e-2,340/scaling,1056/scaling,300/scaling,screen,&wall[14]);
    // mur en brique
    createWall(1,0,20e-2,750/scaling,1,450/scaling,screen,&wall[15]);
    createWall(1,1,20e-2,244/scaling,856/scaling,450/scaling,screen,&wall[16]);
    createWall(2,0,0,244/scaling,900/scaling,450/scaling,screen,&wall[17]);
    return wall;
}

WALL *MapExempleRapport1(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap){
    numberWall = 1;
    wall = malloc(numberWall*sizeof(WALL));

    createWall(2, 1,  0.15, 700/scaling,   300/scaling,           0, screen, &wall[0]);

    return wall;
}

WALL *MapExempleRapport2(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap){
    numberWall = 3;
    wall = malloc(numberWall*sizeof(WALL));

    createWall(3, 0,  0.2, 1400/scaling,   0/scaling,           0, screen, &wall[0]);
    createWall(3, 0,  0.2, 1400/scaling,   0/scaling, 500/scaling, screen, &wall[1]);

    createWall(2, 1, 0.15,  500/scaling, 600/scaling,           0, screen, &wall[2]);

    return wall;
}

void freeWALL(WALL *wall) {
    int i = 0;
    for (i=0; i<numberWall; i++) {
    SDL_FreeSurface(wall[i].newWall);
    }
}
