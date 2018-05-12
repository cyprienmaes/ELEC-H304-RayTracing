#ifndef TRANSMISSION_H_INCLUDED
#define TRANSMISSION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "line.h"
#include "wall.h"
#include "point.h"
#include "intersection.h"
#include "TXandRX.h"
#include "droite.h"

char transExiste(POINT avant, POINT apres, POINT transmission, WALL *wall);

POINT *transList(int compte, POINT transmis, POINT *listeAvant, POINT *listeApres);

POINT *transTrie(int compte, POINT avant, POINT *liste);

void transmission(int INC1, int INC2, POINT avant, POINT apres, WALL *wall, SDL_Surface *screen);

#endif // TRANSMISSION_H_INCLUDED
