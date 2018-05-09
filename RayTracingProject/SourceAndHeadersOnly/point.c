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

float distance(POINT entrer, POINT sortie) {
    float dist;
    dist = sqrt(pow(sortie.x-entrer.x,2)+pow(sortie.y-entrer.y,2));
    return dist;
}

POINT image(POINT reel, WALL *wall){
    // Creation d'un point image a partir de la position d'un mur
    float dx, dy;
    char sens;
    POINT point;
    // distances du point reel a la position du mur
    // On sait que la largeur des mur fait 4, pour avoir le centre du mur
    // on fait -2
    sens = wall->vertical;
    dx = reel.x - (float)(wall->position.x);
    dy = reel.y - (float)(wall->position.y);
    if (sens == 1) {
        point.x = reel.x - 2*dx;
        point.y = reel.y;
    }
    else {
        point.y = reel.y - 2*dy;
        point.x = reel.x;
    }
    return point;
}

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
