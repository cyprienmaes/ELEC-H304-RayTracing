#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>

int numberWall;

typedef struct WALL WALL;

struct WALL{
/*
Creation of different kinds of wall for reflexion and refraction.
*/
    float conductivity;
    float permeability;
    char vertical;
    int epaisseur;
    int largeur;
    // Position of the top left corner of a rectangle.
    SDL_Rect position;
    SDL_Surface *newWall;
};

void createWall(float conductivity, float permeability, char vertical, int epaisseur, int largeur, int hauteur, int posX, int posY, SDL_Surface *screen, WALL *mur) {
/* Création d'un mur suivant les propriétés misent en paramètres :
   - verticale : 1 si oui 0 si non
   - posX et posY : position du coin haut gauche du mur
   - screen : fenêtre dans laquelle s'affiche le mur
*/
    mur->conductivity = conductivity;
    mur->permeability = permeability;
    mur->vertical = vertical;
    // Attention l'epaisseur n'est pas celle affichee a l'ecran. C'est juste pour le calcul de puissance.
    mur->epaisseur = epaisseur;
    mur->largeur = largeur;
    mur->position.x = posX;
    mur->position.y = posY;
    mur->newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    SDL_FillRect(mur->newWall, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(mur->newWall, NULL, screen, &mur->position);
}

WALL *SquareMap(SDL_Surface *screen, WALL *wall, int largeurEcran, int hauteurEcran){
    numberWall = 4;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        createWall(0,0,0,0,largeurEcran, 4, 0,i*(hauteurEcran-4),screen,&wall[i]);
    }
    for(i=0;i<=1;i++) {
        createWall(0,0,1,0,4,hauteurEcran-8,i*(largeurEcran-4),4,screen,&wall[i+2]);
    }
    return wall;
}

void freeWALL(WALL *wall) {
    int i = 0;
    for (i=0; i<numberWall; i++) {
    SDL_FreeSurface(wall[i].newWall);
    }
}

