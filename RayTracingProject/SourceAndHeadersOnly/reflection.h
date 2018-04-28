#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "line.h"
#include "wall.h"

#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED



#endif // REFLECTION_H_INCLUDED

void methodImage(int xTX, int yTX, int xRX, int yRX, WALL *wall, SDL_Surface *screen, int flag);
void emission(float xSource, float ySource, WALL *wall, SDL_Surface *screen);

