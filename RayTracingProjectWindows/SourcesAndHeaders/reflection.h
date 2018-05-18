#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h"
#include "line.h"
#include "wall.h"
#include "TXandRX.h"
#include "droite.h"
#include "transmission.h"
#include "coefficients.h"

#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED

double coeffRef(POINT avant, POINT inter, WALL wall);
double troisReflexion(float echelle, POINT lePoint1, POINT lePoint2, int murNonConsiderer1, int murNonConsiderer2, RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen);
double deuxReflexion(float echelle, POINT lePoint, int murNonConsiderer, RECEIVER receiver, TRANSMITTER transmitter, WALL *wall, SDL_Surface *screen);
POINT *premiereImage(TRANSMITTER transmitter,WALL *wall, POINT *listeDePoints);
double reflexion(float echelle, RECEIVER receiver, TRANSMITTER transmitter, WALL *wall, SDL_Surface *screen);
double onde(float echelle, RECEIVER receiver, TRANSMITTER transmitter, WALL *wall, SDL_Surface *screen);

#endif // REFLECTION_H_INCLUDED
