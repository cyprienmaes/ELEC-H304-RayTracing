#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h" // Pour avoir structure POINT

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

char interExiste(WALL *wall, POINT inter, POINT debutReflexion, POINT finReflexion) {
/*
    Fonction qui retourne un si l'intersection existe sur le mur.
*/
    char sens = wall->vertical;
    char ok;
    // On verifie d'abord le sens du mur.
    if (sens == 1) {
        // On verifie que l'intersection est bien sur le mur et pas ailleurs;
        if (inter.y < wall->position.y || inter.y > wall->position.y+wall->longueur) ok = 0;
        // Si c'est le cas, il faut encore verifier que les deux points qui vont donner le debut
        // et la fin de la reflexion se trouver du meme cote du mur.
        else {
            if ((inter.x < debutReflexion.x && inter.x < finReflexion.x) || (inter.x > debutReflexion.x && inter.x > finReflexion.x)) {
                ok = 1;
            }
            else ok = 0;
        }
    }
    else {
        // On refait la meme chose mais dans le cas ou le mur est horizontal.
        if (inter.x < wall->position.x || inter.x > wall->position.x+wall->longueur) ok = 0;
        else {
            if ((inter.y < debutReflexion.y && inter.y < finReflexion.y) || (inter.y > debutReflexion.y && inter.y > finReflexion.y)) {
                ok = 1;
            }
            else ok = 0;
        }
    }
    return ok;
}
