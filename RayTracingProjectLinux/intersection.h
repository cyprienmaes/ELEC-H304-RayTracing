#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h" // Pour avoir structure POINT

#ifndef INTERSECTION_H_INCLUDED
#define INTERSECTION_H_INCLUDED



#endif // INTERSECTION_H_INCLUDED

typedef struct DROITE DROITE;

struct DROITE{
    // equation de droite y = mx + b
    float x0, y0, x1, y1;
};

POINT intersection(DROITE droite1, DROITE droite2);
