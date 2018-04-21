#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "wall.h"

typedef struct POINT POINT;

struct POINT {
    /* Donne les coordonnées d'un point */
    float x;
    float y;
};

void pointImage(POINT *pointImage, POINT copier, POINT comparer, WALL wall) {
/* change la valeur d'un point image au point à copier selon un point à comparer et le sens du mur.
   Attention pointImage est un pointeur, il attend donc une adresse, ne pas oublier de mettre &.
*/
    float dx, dy;
    char sens;
    // distances du point copier au point comparer
    dx = comparer.x-copier.x;
    dy = comparer.y-copier.y;
    sens = wall.vertical;
    // différents cas se présentent alors
    if (sens == 0) {
        pointImage->x = copier.x;
        pointImage->y = copier.y+2*dy;
    }
    else {
        pointImage->x = copier.x+2*dx;
        pointImage->y = copier.y;
        }
}
