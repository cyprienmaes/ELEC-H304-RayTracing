#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>

#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED
int numberWall;

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

typedef struct WALL WALL;

void createWall(float conductivity, float permeability, char vertical, int epaisseur, int largeur, int hauteur, int posX, int posY, SDL_Surface *screen, WALL *mur);

WALL *SquareMap(SDL_Surface *screen, WALL *wall, int largeurEcran, int hauteurEcran);

void freeWALL(WALL *wall);


#endif // WALL_H_INCLUDED
