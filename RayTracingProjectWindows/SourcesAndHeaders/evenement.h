#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED

void posSouris(float echelle, int largeurEcran, int hauteurEcran, const char* file, int taillePolice,int posXx, int posYx, int posXy, int posYy, SDL_Surface *screen);

#endif // EVENEMENT_H_INCLUDED
