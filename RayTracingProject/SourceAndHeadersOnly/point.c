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
    int x;
    int y;
};

POINT pointImage(POINT copier, POINT comparer, WALL wall) {
/* change la valeur d'un point image au point à copier selon un point à comparer et le sens du mur.
   Attention pointImage est un pointeur, il attend donc une adresse, ne pas oublier de mettre &.
*/
    int dx, dy;
    char sens;
    POINT image;

    // distances du point copier au point comparer
    dx = comparer.x-copier.x;
    dy = comparer.y-copier.y;
    sens = wall.vertical;
    // différents cas se présentent alors
    if (sens == 0) {
        image.x = copier.x;
        image.y = copier.y+2*dy;
    }
    else {
        image.x = copier.x+2*dx;
        image.y = copier.y;
        }
    return image;
}
