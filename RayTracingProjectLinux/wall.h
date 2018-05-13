#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "droite.h"

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
    float posReeleX;
    float posReeleY;
    DROITE droite;
    // Position of the top left corner of a rectangle.
    SDL_Rect position;
    SDL_Surface *newWall;
};
void createWall(float echelle, char type, char vertical, float epaisseur, int longueur, int posX, int posY, SDL_Surface *screen, WALL *mur);

WALL *UnMur(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall);

WALL *DeuxMurs(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall);

WALL *TroisMur(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall);

WALL *SquareMap(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall);

WALL *MapUn(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall);

WALL *MapDeux(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall);

WALL *MapExempleRapport1(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall);

WALL *MapExempleRapport2(int largeurMap, int hauteurMap, float echelle, SDL_Surface *screen, WALL *wall);

void freeWALL(WALL *wall);


#endif // WALL_H_INCLUDED
