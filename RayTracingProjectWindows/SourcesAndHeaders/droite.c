#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>

typedef struct DROITE DROITE;

struct DROITE{
    // equation de droite y = mx + b
    float x0, y0, x1, y1;
};

DROITE createDroite(float x0, float y0, float x1, float y1) {
    DROITE nouvelleDroite;
    nouvelleDroite.x0 = x0;
    nouvelleDroite.y0 = y0;
    nouvelleDroite.x1 = x1;
    nouvelleDroite.y1 = y1;
    return nouvelleDroite;
}

