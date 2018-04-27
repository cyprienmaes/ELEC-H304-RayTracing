#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>

#define scaling 1

int numberWall;

typedef struct DROITE DROITE;
struct DROITE{
    // equation de droite y = mx + b
    float x0, y0, x1, y1;
};


typedef struct WALL WALL;
struct WALL{
/*
Creation of different kinds of wall for reflexion and refraction.
*/
    float conductivity;
    float permitivity;
    char vertical;
    int epaisseur;
    int largeur;
    DROITE droite;
    // Position of the top left corner of a rectangle.
    SDL_Rect position;
    SDL_Surface *newWall;
};

void createWall(char type, char vertical, int epaisseur, int largeur, int hauteur, int posX, int posY, SDL_Surface *screen, WALL *mur) {
/* Création d'un mur suivant les propriétés misent en paramètres :
   - verticale : 1 si oui 0 si non
   - posX et posY : position du coin haut gauche du mur
   - screen : fenêtre dans laquelle s'affiche le mur
*/
    mur->vertical = vertical;
    if(vertical){ mur->droite.x0 = posX; mur->droite.y0 = posY; mur->droite.x1 = posX; mur->droite.y1 = (posY+100);}
    else {        mur->droite.x0 = posX; mur->droite.y0 = posY; mur->droite.x1 = (posX+100); mur->droite.y1 = posY;}
    // Attention l'epaisseur n'est pas celle affichee a l'ecran. C'est juste pour le calcul de puissance.
    mur->epaisseur = epaisseur;
    mur->largeur = largeur;
    mur->position.x = posX;
    mur->position.y = posY;
    mur->newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
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
            mur->conductivity = 0.14;
            mur->permitivity = 5;
            SDL_FillRect(mur->newWall, NULL, SDL_MapRGB(screen->format, 90, 90, 90));
            break;
    }
    SDL_BlitSurface(mur->newWall, NULL, screen, &mur->position);
}

WALL *SquareMap(SDL_Surface *screen, WALL *wall, int largeurEcran, int hauteurEcran){
    numberWall = 4;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        createWall(1,0,0,largeurEcran, 4, 0,i*(hauteurEcran-4),screen,&wall[i]);
    }
    for(i=0;i<=1;i++) {
        createWall(1,1,0,4,hauteurEcran-8,i*(largeurEcran-4),4,screen,&wall[i+2]);
    }
    return wall;
}

WALL *MapUn(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap) {
/*
Creation d'un plan d'etage plus ou moins realiste
*/
    numberWall = 11;
    wall = malloc(numberWall*sizeof(WALL));
    int i = 0;
    // Creation du cadre
    for(i=0;i<=1;i++){
        createWall(1,0,0,largeurMap/scaling, 4, 0,i*((hauteurMap/scaling)-4),screen,&wall[i]);
    }
    for(i=0;i<=1;i++) {
        createWall(1,1,0,4,(hauteurMap/scaling)-8,i*((largeurMap/scaling)-4),4,screen,&wall[i+2]);
    }
    createWall(2,0,0,(100/scaling)-4,4,4,(360/scaling)-4,screen,&wall[4]);
    createWall(2,0,0,100/scaling,4,300/scaling,(360/scaling)-4,screen,&wall[5]);
    createWall(2,1,0,4,138/scaling,(400/scaling)-4,4,screen,&wall[6]);
    createWall(2,1,0,4,138/scaling,(400/scaling)-4,218/scaling,screen,&wall[7]);
    createWall(2,1,0,4,236/scaling,600/scaling,4,screen,&wall[8]);
    createWall(2,1,0,4,40/scaling,600/scaling,316/scaling,screen,&wall[8]);
    createWall(2,0,0,60/scaling,4,600/scaling,(360/scaling)-4,screen,&wall[9]);
    createWall(2,0,0,(384/scaling)-4,4,736/scaling,(360/scaling)-4,screen,&wall[10]);
    return wall;
}

void freeWALL(WALL *wall) {
    int i = 0;
    for (i=0; i<numberWall; i++) {
    SDL_FreeSurface(wall[i].newWall);
    }
}

