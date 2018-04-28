#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h" // Pour avoir structure POINT

typedef struct DROITE DROITE;

struct DROITE{
    // equation de droite y = mx + b
    float x0, y0, x1, y1;
};

POINT intersection(DROITE droite1, DROITE droite2){
    POINT intersect;

    float m1 = (droite1.y1-droite1.y0)/(droite1.x1-droite1.x0);
    float m2 = (droite2.y1-droite2.y0)/(droite2.x1-droite2.x0);

    float b1 = droite1.y0 - m1*droite1.x0;
    float b2 = droite2.y0 - m2*droite2.x0;

    if(droite1.x1-droite1.x0 == 0 && droite2.x1-droite2.x0 != 0){
        intersect.x = droite1.x0;
        intersect.y = m2*(intersect.x)+b2;
    }

    else if(droite1.x1-droite1.x0 != 0 && droite2.x1-droite2.x0 == 0){
        intersect.x = droite2.x0;
        intersect.y = m1*(intersect.x)+b1;
    }

    // Si le produit vectoriel n'est pas nul
    else if (m1 != m2){

        intersect.x = (b2-b1)/(m1-m2); //SOLUTIONS du systeme y1 = m1*x + b1
        intersect.y = m1*intersect.x + b1; //                 y2 = m2*x +b2
    }

    return intersect;
}

