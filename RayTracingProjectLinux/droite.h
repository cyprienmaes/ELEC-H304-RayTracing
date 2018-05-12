#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>

#ifndef DROITE_H_INCLUDED
#define DROITE_H_INCLUDED

typedef struct DROITE DROITE;
struct DROITE{
    // equation de droite y = mx + b
    float x0, y0, x1, y1;
};

DROITE createDroite(float x0, float y0, float x1, float y1);

#endif // DROITE_H_INCLUDED
