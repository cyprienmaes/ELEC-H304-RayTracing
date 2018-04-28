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

void methodImage(int xTX, int yTX, int xRX, int yRX, WALL *wall, SDL_Surface *screen, int flag) {
    if (flag >0){
        int i, dy, dx, xIm, yIm, yMur, xMur;
        char sens;
        float tgTheta;
        flag-=1;
        for (i=0;i<numberWall;i++){
            yMur = wall[i].position.y;
            xMur = wall[i].position.x;
            sens = wall[i].vertical;
            if (yMur > yTX && sens == 0){
                dy = yMur - yTX;
                yIm = yTX + 2*dy;
                xIm = xTX;
                if(xRX-xIm == 0) xMur = xRX;
                else {
                    tgTheta = (float) (yIm-yRX)/(xRX-xIm);
                    xMur = (yMur-yTX+(xTX*tgTheta))/tgTheta;
                }
                line(xTX, yTX, xMur, yMur, SDL_MapRGB(screen->format,0,100,255), screen);
                line(xMur, yMur, xRX, yRX, SDL_MapRGB(screen->format,0,100,255), screen);
            }

            else if(xMur>xTX && sens == 1){
                dx = xMur-xTX;
                xIm = xTX+2*dx;
                yIm=yTX;
                if(yIm-yRX == 0) yMur=yRX;
                else {
                    tgTheta=(float)(xIm-xRX)/(yIm-yRX);
                    yMur = (xTX-xMur+(yTX*tgTheta))/tgTheta;
                }
                line(xTX, yTX, xMur, yMur, SDL_MapRGB(screen->format,0,255,100), screen);
                line(xMur, yMur, xRX, yRX, SDL_MapRGB(screen->format,0,255,100), screen);
            }
            else if (yMur<yTX && sens == 0){
                yMur = yMur+4;
                dy = yTX-yMur;
                yIm = yTX-(2*dy);
                xIm = xTX;
                if(xRX-xIm == 0) xMur = xTX;
                else{
                    tgTheta = (float) (yRX-yIm)/(xRX-xIm);
                    xMur = (yTX-yMur+(xTX*tgTheta))/tgTheta;
                }
                line(xTX, yTX, xMur, yMur, SDL_MapRGB(screen->format,255,0,100), screen);
                line(xMur, yMur, xRX, yRX, SDL_MapRGB(screen->format,255,0,100), screen);
            }
            else if (xMur<xTX && sens == 1){
                xMur = xMur+4;
                dx = xTX-xMur;
                xIm = xTX-2*dx;
                yIm = yTX;
                if(yIm-yRX == 0) yMur = yTX;
                else{
                    tgTheta = (float) (xRX-xIm)/(yIm-yRX);
                    yMur = (xMur - xTX +(yTX*tgTheta))/tgTheta;
                }
                line(xTX, yTX, xMur, yMur, SDL_MapRGB(screen->format,108,226,236), screen);
                line(xMur, yMur, xRX, yRX, SDL_MapRGB(screen->format,108,226,236), screen);
            }
        }
    }
}

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
    POINT point;    point.x = (wall[6].position.x);     point.y = wall[6].position.y+(wall[6].longueur/2);
    POINT source;   source.x = xSource;     source.y = ySource;

    DROITE droite1; droite1.x0 = xSource; droite1.y0 = ySource; droite1.x1 = point.x; droite1.y1 = point.y;

    POINT intersect = intersection(droite1, wall[6].droite);
    *indice_self = 6;
    line(source.x, source.y, intersect.x, intersect.y, SDL_MapRGB(screen->format,255,0,100), screen);

    POINT image = pointImage(source, intersect, wall[6]);

    intersect = reflection(image, intersect, indice_self, wall, screen);

    for(int count=0; count <20; count++){
        image = pointImage(image, intersect, wall[*indice_self]);
        intersect = reflection(image, intersect, indice_self, wall, screen);
    }
}
