#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "wall.h"

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED



#endif // POINT_H_INCLUDED

typedef struct POINT POINT;

struct POINT {
    /* Donne les coordonnées d'un point */
    float x;
    float y;
};

void pointImage(POINT *pointImage, POINT copier, POINT comparer, WALL wall);
