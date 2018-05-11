#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "line.h"
#include "wall.h"
#include "point.h"
#include "intersection.h"
#include "TXandRX.h"
#include "droite.h"
#include "transmission.h"
/*
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
*/
POINT *premiereImage(TRANSMITTER *transmitter,WALL *wall, POINT *listeDePoints){
/*
    Retourne un tableau dynamique de points. Ces points sont l'images de l'emetteur par rapport
    a chaque mur de la map consideree.
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
    int nbTransGlobal = 0;
    POINT nouvelleImage;
    POINT inter[3];
    DROITE droiteInter[3];
    int i = 0;
    // On regarde tous les murs sauf le mur de la dernier symetrie.
    for (i = 0; i<numberWall; i++) {
        if (i == murNonConsiderer2);
        else {
            // On creer un nouveau point image
            nouvelleImage = image(lePoint2, &wall[i]);
            // On en fait une droite avec le recepteur
            droiteInter[0] = createDroite(nouvelleImage.x,nouvelleImage.y,receiver->pointCentral.x,receiver->pointCentral.y);
            // On calcul l'intersection avec le mur de la symetrie du nouveau point image
            inter[0] = intersection(droiteInter[0],wall[i].droite);
            // On creer une nouvelle droite entre le point d'intersection trouver
            // et le point image precedent.
            droiteInter[1] = createDroite(inter[0].x,inter[0].y,lePoint2.x,lePoint2.y);
            // On calcul l'intersection selon le mur de symetrie precedent
            inter[1] = intersection(droiteInter[1],wall[murNonConsiderer2].droite);
            // On creer une nouvelle droite entre le point d'intersection trouver
            // et le point image precedent le precedent.
            droiteInter[2] = createDroite(inter[1].x,inter[1].y,lePoint1.x,lePoint1.y);
            // On calcul l'intersection selon le mur de symetrie precedent le precedent
            inter[2] = intersection(droiteInter[2],wall[murNonConsiderer1].droite);
            // On test toutes les intersections pour etre sur que la reflexion existe
            if (interExiste(&wall[i],inter[0],inter[1],receiver->pointCentral)==1) {
                if (interExiste(&wall[murNonConsiderer2], inter[1], inter[2], inter[0])==1) {
                    if(interExiste(&wall[murNonConsiderer1], inter[2], transmitter->pointCentral, inter[1])==1) {
                        nbTransGlobal += transmission(3,nbTransGlobal,transmitter->pointCentral,inter[2],wall,screen);
                        nbTransGlobal += transmission(3,nbTransGlobal,inter[2],inter[1],wall,screen);
                        nbTransGlobal += transmission(3,nbTransGlobal,inter[1],inter[0],wall,screen);
                        nbTransGlobal += transmission(3,nbTransGlobal,inter[0],receiver->pointCentral,wall,screen);
                        nbTransGlobal = 0;
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
    printf("T'es moche");
    int nbTransGlobal = 0;
    POINT nouvelleImage;
    POINT inter[2];
    DROITE droiteInter[2];
    int i = 0;
    for (i=0;i<numberWall;i++){
        if (i==murNonConsiderer);
        else {
            nouvelleImage = image(lePoint,&wall[i]);
            droiteInter[0] = createDroite(nouvelleImage.x,nouvelleImage.y,receiver->pointCentral.x,receiver->pointCentral.y);
            inter[0] = intersection(droiteInter[0],wall[i].droite);
            droiteInter[1] = createDroite(inter[0].x,inter[0].y,lePoint.x,lePoint.y);
            inter[1] = intersection(droiteInter[1],wall[murNonConsiderer].droite);
            if(interExiste(&wall[murNonConsiderer],inter[1],transmitter->pointCentral,inter[0]) == 1) {
                if( interExiste(&wall[i],inter[0],inter[1],receiver->pointCentral) == 1){
                    nbTransGlobal += transmission(2,nbTransGlobal,transmitter->pointCentral,inter[1],wall,screen);
                    nbTransGlobal += transmission(2,nbTransGlobal,inter[1],inter[0],wall,screen);
                    nbTransGlobal += transmission(2,nbTransGlobal,inter[0],receiver->pointCentral,wall,screen);
                    nbTransGlobal = 0;
                }
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
    int nbTransGlobal = 0;
    POINT *premierPointImage = NULL;
    premierPointImage = premiereImage(transmitter,wall,premierPointImage);
    POINT interMurDroite;
    DROITE droiteDePoints;
    droiteDePoints.x0 = receiver->pointCentral.x;
    droiteDePoints.y0 = receiver->pointCentral.y;
    for(i=0;i<numberWall;i++){
        droiteDePoints.x1 = premierPointImage[i].x;
        droiteDePoints.y1 = premierPointImage[i].y;
        interMurDroite = intersection(droiteDePoints,wall[i].droite);
        if (interExiste(&wall[i],interMurDroite, transmitter->pointCentral, receiver->pointCentral)==1) {
            nbTransGlobal += transmission(1,nbTransGlobal,transmitter->pointCentral,interMurDroite,wall,screen);
            nbTransGlobal += transmission(1,nbTransGlobal,interMurDroite,receiver->pointCentral,wall,screen);
            nbTransGlobal = 0;
        }
        deuxReflexion(premierPointImage[i],i,receiver,transmitter,wall,screen);
    }
}

void onde(RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen){
    int nbTransGlobal = 0;
    nbTransGlobal += transmission(0,nbTransGlobal,transmitter->pointCentral,receiver->pointCentral,wall,screen);
    printf("nombre total de transmission : %d\n",nbTransGlobal);
    nbTransGlobal = 0;
    reflexion(receiver,transmitter,wall,screen);
}
