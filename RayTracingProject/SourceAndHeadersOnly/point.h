#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "wall.h"

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "wall.h"

typedef struct POINT POINT;

struct POINT {
    /* Donne les coordonnées d'un point */
    float x;
    float y;
};
POINT image(POINT reel, WALL *wall);

POINT pointImage(POINT copier, POINT comparer, WALL wall);


#endif // POINT_H_INCLUDED

