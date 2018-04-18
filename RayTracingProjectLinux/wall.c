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

void StayDisplay() {
/*
Function which wait the event of exit screen. It's better than a while(1).
*/
    int continu = 1;
    SDL_Event event;

    while (continu){
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT :
                continu = 0;
        }
    }
}

void createWall(float conductivity, float permeability, char vertical, int epaisseur, int largeur, int posX, int posY, SDL_Surface *screen, WALL *mur) {
/* Création d'un mur suivant les propriétés misent en paramètres :
   - verticale : 1 si oui 0 si non
   - posX et posY : position du coin haut gauche du mur
   - screen : fenêtre dans laquelle s'affiche le mur
*/
    mur->conductivity = conductivity;
    mur->permeability = permeability;
    mur->vertical = vertical;
    mur->epaisseur = epaisseur;
    mur->largeur = largeur;
    mur->position.x = posX;
    mur->position.y = posY;
    if (vertical == 0) {
        mur->newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, largeur, epaisseur, 32, 0, 0, 0, 0);
    }
    else {
        mur->newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, epaisseur, largeur, 32, 0, 0, 0, 0);
    }
    SDL_FillRect(mur->newWall, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(mur->newWall, NULL, screen, &mur->position);
}

WALL *SquareMap(SDL_Surface *screen, WALL *wall){
    numberWall = 4;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        createWall(0,0,0,4,600,0,i*596,screen,&wall[i]);
    }
    for(i=0;i<=1;i++) {
        createWall(0,0,1,4,596,i*596,4,screen,&wall[i+2]);
    }
    return wall;
}

void freeWALL(WALL *wall) {
    int i = 0;
    for (i=0; i<numberWall; i++) {
    SDL_FreeSurface(wall[i].newWall);
    }
}

