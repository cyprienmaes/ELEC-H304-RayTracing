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

#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED

void methodImage(int xTX, int yTX, int xRX, int yRX, WALL *wall, SDL_Surface *screen, int flag);
void emission(float xSource, float ySource, WALL *wall, SDL_Surface *screen);
POINT *premiereImage(TRANSMITTER *transmitter,WALL *wall, POINT *listeDePoints);
void troisReflexion(POINT lePoint1, POINT lePoint2, int murNonConsiderer1, int murNonConsiderer2, RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen);
void deuxReflexion(POINT lePoint, int murNonConsiderer, RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen);
void reflexion(RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen);

#endif // REFLECTION_H_INCLUDED
