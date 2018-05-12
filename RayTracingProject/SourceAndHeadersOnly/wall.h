#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "droite.h"

#define scaling 1.7

#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

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

void createWall(char type, char vertical, float epaisseur, float longueur, int posX, int posY, SDL_Surface *screen, WALL *mur);

WALL *DeuxMurs(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap);

WALL *UnMur(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap);

WALL *TroisMur(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap);

WALL *SquareMap(SDL_Surface *screen, WALL *wall, int largeurEcran, int hauteurEcran);

WALL *MapUn(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap);

WALL *MapDeux(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap);

WALL *MapExempleRapport(SDL_Surface *screen, WALL *wall, int largeurMap, int hauteurMap);


void freeWALL(WALL *wall);


#endif // WALL_H_INCLUDED
