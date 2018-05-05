#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>
#include <SDL/SDL.h>
#include "line.h"
#include "wall.h"
#include "point.h"
#include "intersection.h"
#include "TXandRX.h"

POINT reflection(POINT point0, POINT point1, int* indice_self, WALL* wall, SDL_Surface *screen){
    // Algorithme pour effectuer une reflection.
    // - point0 : est le point image d'une source, ou le transmitter lui-même pour le premier envoi.
    // - point1 : est la 'nouvelle source', point d'intersection avec le mur précédant
    // - indice_self : est l'indice du mur de la 'nouvelle source' que l'on va rentrer en condition pou ne pas analyser le mur
    //                 sur le lequel on réfléchi
    // - RETOURNE : le point la prochaine reflexion

    //On crée une droite passant par point0 et point1
    DROITE droite; droite.x0 = point0.x; droite.y0 = point0.y; droite.x1 = point1.x; droite.y1 = point1.y;
    POINT intersect;

    float vx = (droite.x1 - droite.x0); // composante x du vecteur directeur de la droite allant dans le sens de la reflection (on aurait bien pu le faire avec vy...)
    float distance=0; //Important car sinon l'opération distance==0 retourne faux...
    int j, i=0; // i utilisé dans le 'for', et j indice de l'intersecion de distance minimum depuis le mur indice_self
    float x, y, dx, dy,xMur,yMur,longueur;
    char enVue;

    for(i; (i<numberWall) ; i++){
        if ( i!= *indice_self ){ // On saute l'indice du mur sur lequel il y a reflexion

            intersect = intersection(droite, wall[i].droite);
            x = intersect.x;         y = intersect.y;
            dx = (x - point1.x);        dy = (y - point1.y);
            enVue = (dx/vx) > 0; // Résolution de l'équation lambda > 0, où x1 = x0 + lambda*vx
                                 // Ceci permet de voir dans la bonne direction par rapport à l'intersection
            xMur = wall[i].position.x;
            yMur = wall[i].position.y;
            longueur = wall[i].longueur;

            if( enVue && y>yMur && y<(yMur+longueur) ){
                if(distance == 0){
                    distance = sqrt((dx*dx) + (dy*dy));
                    j = i;
                }
                else if( sqrt((dx*dx) + (dy*dy)) < distance){
                    distance = sqrt((dx*dx) + (dy*dy));
                    j = i;
                }
            }

            else if( enVue && x>xMur && x<(xMur+longueur)){
                if(distance == 0){
                    distance = sqrt((dx*dx) + (dy*dy));
                    j = i;
                }
                else if( sqrt((dx*dx) + (dy*dy)) < distance){
                    distance = sqrt((dx*dx) + (dy*dy));
                    j = i;
                }
            }
        }
    }

    intersect = intersection(droite, wall[j].droite);
    *indice_self = j;
    line(point1.x, point1.y, intersect.x, intersect.y, SDL_MapRGB(screen->format,255,0,100), screen);

    return intersect;
}

void emission(float xSource, float ySource, WALL *wall, SDL_Surface *screen){
    int* indice_self;
    POINT point;    point.x = (wall[0].position.x);     point.y = wall[0].position.y+(wall[0].longueur/2);
    POINT source;   source.x = xSource;     source.y = ySource;

    DROITE droite1; droite1.x0 = xSource; droite1.y0 = ySource; droite1.x1 = point.x; droite1.y1 = point.y;

    POINT intersect = intersection(droite1, wall[0].droite);
    *indice_self = 0;
    line(source.x, source.y, intersect.x, intersect.y, SDL_MapRGB(screen->format,255,0,100), screen);

    POINT image = pointImage(source, intersect, wall[0]);

    intersect = reflection(image, intersect, indice_self, wall, screen);

    for(int count=0; count <10; count++){
        image = pointImage(image, intersect, wall[*indice_self]);
        intersect = reflection(image, intersect, indice_self, wall, screen);
    }
}

POINT *premiereImage(TRANSMITTER *transmitter,WALL *wall, POINT *listeDePoints){
/*
    Retourne un tableau dynamique de points. Ces points sont les images de l'emetteur par rapport
    a chaque mur de la map consideree, donc ils sont la première image de l'emetteur pour un cas de reflexion
    donné
*/
    int i = 0;
    // On alloue un espace egale au nombre de mur.
    listeDePoints = malloc(numberWall*sizeof(POINT));
    // On cree un point correspondant a la position centrale de l'emetteur.
    POINT recu;
    for (i=0;i<numberWall;i++){
        recu = image(transmitter->pointCentral,&wall[i]);
        listeDePoints[i].x = recu.x;
        listeDePoints[i].y = recu.y;
    }
    return listeDePoints;
}

void troisReflexion(POINT lePoint1, POINT lePoint2, int murNonConsiderer1, int murNonConsiderer2, RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen) {
/*
Dessine toutes les possibilites de faire 3 reflexions entre l'emetteur et le recepteur.
*/
    POINT nouvelleImage;
    POINT inter1;
    POINT inter2;
    POINT inter3;
    DROITE droiteInter1;
    DROITE droiteInter2;
    DROITE droiteInter3;
    droiteInter1.x1 = receiver->pointCentral.x;
    droiteInter1.y1 = receiver->pointCentral.y;
    int i = 0;
    // On regarde tous les murs sauf le mur de la dernier symetrie.
    for (i = 0; i<numberWall; i++) {
        if (i == murNonConsiderer2);
        else {
            // On creer un nouveau point image
            nouvelleImage = image(lePoint2, &wall[i]);
            // On en fait une droite avec le recepteur
            droiteInter1.x0 = nouvelleImage.x;
            droiteInter1.y0 = nouvelleImage.y;
            // On calcul l'intersection avec le mur de la symetrie du nouveau point image
            inter1 = intersection(droiteInter1,wall[i].droite);
            // On creer une nouvelle droite entre le point d'intersection trouver
            // et le point image precedent.
            droiteInter2.x0 = inter1.x;
            droiteInter2.y0 = inter1.y;
            droiteInter2.x1 = lePoint2.x;
            droiteInter2.y1 = lePoint2.y;
            // On calcul l'intersection selon le mur de symetrie precedent
            inter2 = intersection(droiteInter2,wall[murNonConsiderer2].droite);
            // On creer une nouvelle droite entre le point d'intersection trouver
            // et le point image precedent le precedent.
            droiteInter3.x0 = inter2.x;
            droiteInter3.y0 = inter2.y;
            droiteInter3.x1 = lePoint1.x;
            droiteInter3.y1 = lePoint1.y;
            // On calcul l'intersection selon le mur de symetrie precedent le precedent
            inter3 = intersection(droiteInter3,wall[murNonConsiderer1].droite);
            // On test toutes les intersections pour etre sur que la reflexion existe
            if (interExiste(wall[i],inter1,inter2,receiver->pointCentral)) {
                if (interExiste(wall[murNonConsiderer2], inter2, inter3, inter1)) {
                    if(interExiste(wall[murNonConsiderer1], inter3, transmitter->pointCentral, inter2)) {
                        line(inter1.x,inter1.y,receiver->pointCentral.x,receiver->pointCentral.y,SDL_MapRGB(screen->format,255,128,0),screen);
                        line(inter1.x,inter1.y,inter2.x,inter2.y,SDL_MapRGB(screen->format,255,128,0),screen);
                        line(inter2.x,inter2.y,inter3.x,inter3.y,SDL_MapRGB(screen->format,255,128,0),screen);
                        line(transmitter->pointCentral.x,transmitter->pointCentral.y,inter3.x,inter3.y,SDL_MapRGB(screen->format,255,128,0),screen);
                    }
                }
            }
        }
    }
}

void deuxReflexion(POINT lePoint, int murNonConsiderer, RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen) {
/*
Dessine toutes les possibilites de faire 2 reflexions entre l'emetteur et le recepteur.
Fonctionne sur le meme principe que troisReflexion.
*/
    POINT nouvelleImage;
    POINT inter1;
    POINT inter2;
    DROITE droiteDePoints;
    DROITE droiteIntersection;
    droiteDePoints.x1 = receiver->pointCentral.x;
    droiteDePoints.y1 = receiver->pointCentral.y;
    int i = 0;
    for (i=0;i<numberWall;i++){
        if (i==murNonConsiderer);
        else {
            nouvelleImage = image(lePoint,&wall[i]);
            droiteDePoints.x0 = nouvelleImage.x;
            droiteDePoints.y0 = nouvelleImage.y;
            inter1 = intersection(droiteDePoints,wall[i].droite);
            droiteIntersection.x0 = inter1.x;
            droiteIntersection.y0 = inter1.y;
            droiteIntersection.x1 = lePoint.x;
            droiteIntersection.y1 = lePoint.y;
            inter2 = intersection(droiteIntersection,wall[murNonConsiderer].droite);
            if(interExiste(wall[murNonConsiderer],inter2,transmitter->pointCentral,inter1) && interExiste(wall[i],inter1,inter2,receiver->pointCentral)){
                line(inter1.x,inter1.y,receiver->pointCentral.x,receiver->pointCentral.y,SDL_MapRGB(screen->format,0,255,100),screen);
                line(inter1.x,inter1.y,inter2.x,inter2.y,SDL_MapRGB(screen->format,0,255,100),screen);
                line(transmitter->pointCentral.x,transmitter->pointCentral.y,inter2.x,inter2.y,SDL_MapRGB(screen->format,0,255,100),screen);
            }
            // On envoie le point de symetrie de la premiere image et la nouvelleImage calculee
            // dans troisReflexion
            troisReflexion(lePoint,nouvelleImage,murNonConsiderer,i,receiver,transmitter,wall,screen);
        }
    }
}

void reflexion(RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen){
/*
    Dessine toutes les possibilites de faire 1 reflexion entre l'emetteur et le recepteur.
    Fonctionne sur le meme principe que deuxReflexion.
*/
    int i = 0;
    POINT *premierPointImage = NULL;
    premierPointImage = premiereImage(transmitter,wall,premierPointImage);
    POINT interMurDroite;
    DROITE droiteDePoints;
    droiteDePoints.x0 = receiver->pointCentral.x;
    droiteDePoints.y0 = receiver->pointCentral.y;
    for(i=0;i<1;i++){
        droiteDePoints.x1 = premierPointImage[i].x;
        droiteDePoints.y1 = premierPointImage[i].y;
        interMurDroite = intersection(droiteDePoints,wall[i].droite);
        if (interExiste(wall[i],interMurDroite, transmitter->pointCentral, receiver->pointCentral)) {
            line(transmitter->pointCentral.x, transmitter->pointCentral.y, interMurDroite.x, interMurDroite.y, SDL_MapRGB(screen->format,255,0,100),screen);
            line(interMurDroite.x, interMurDroite.y, receiver->pointCentral.x, receiver->pointCentral.y, SDL_MapRGB(screen->format,255,0,100),screen);
        }
        deuxReflexion(premierPointImage[i],i,receiver,transmitter,wall,screen);
    }
}
