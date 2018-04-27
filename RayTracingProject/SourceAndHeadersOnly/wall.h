#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>

#define scaling 1

#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED
int numberWall;

struct DROITE{
    // equation de droite y = mx + b
    float x0, y0, x1, y1;
};

typedef struct DROITE DROITE;

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

typedef struct WALL WALL;

void createWall(char type, char vertical, int epaisseur, int largeur, int hauteur, int posX, int posY, SDL_Surface *screen, WALL *mur);

WALL *SquareMap(SDL_Surface *screen, WALL *wall, int largeurEcran, int hauteurEcran);

WALL *MapUn(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap);

void freeWALL(WALL *wall);


#endif // WALL_H_INCLUDED
