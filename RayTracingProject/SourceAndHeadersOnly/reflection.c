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

void emission(float xSource, float ySource, WALL *wall, SDL_Surface *screen){
    POINT point;    point.x = (wall[6].position.x);     point.y = wall[6].position.y+(wall[6].longueur/2);
    POINT source;   source.x = xSource;     source.y = ySource;

    DROITE droite1; droite1.x0 = xSource; droite1.y0 = ySource; droite1.x1 = point.x; droite1.y1 = point.y;

    POINT intersect = intersection(droite1, wall[6].droite);

    line(source.x, source.y, intersect.x, intersect.y, SDL_MapRGB(screen->format,255,0,100), screen);

    POINT image = pointImage(source, intersect, wall[6]);


    DROITE droite2; droite2.x0 = image.x; droite2.y0 = image.y; droite2.x1 = intersect.x; droite2.y1 = intersect.y;
    float vx = (droite2.x1 - droite2.x0);
    float distance=0;
    int j, i=0;

    for(i; i< numberWall ; i++){
        POINT intersect2 = intersection(droite2, wall[i].droite);
        float x = intersect2.x; float y = intersect2.y;
        float dx = (x - intersect.x);
        float dy = (y - intersect.y);
        char enVue = ((intersect2.x - intersect.x)/vx) > 0;

        float xMur = wall[i].position.x;
        float yMur = wall[i].position.y;
        float longueur = wall[i].longueur;

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

    POINT intersect3 = intersection(droite2, wall[j].droite);
    line(intersect.x, intersect.y, intersect3.x, intersect3.y, SDL_MapRGB(screen->format,255,0,100), screen);


}

/*
void reflection(POINT point0, POINT point0){

    DROITE droite; droite.x0 = point0.x; droite.y0 = point0.y; droite.x1 = point1.x; droite2.y1 = point1.y;
    float vx = (droite.x1 - droite.x0);
    float distance=0;
    int j, i=0;
    float x, dx, dy,xMur,yMur,largeur;
    char enVue;

    for(i; i< numberWall ; i++){
        POINT intersect2 = intersection(droite2, wall[i].droite);
        x = intersect2.x; float y = intersect2.y;
        dx = (x - intersect.x);
        dy = (y - intersect.y);
        enVue = ((intersect2.x - intersect.x)/vx) > 0;

        xMur = wall[i].position.x;
        yMur = wall[i].position.y;
        largeur = (float)wall[i].largeur;

        if( enVue && y>yMur && y<(yMur+largeur) ){
            if(distance == 0){
                distance = sqrt((dx*dx) + (dy*dy));
                j = i;
            }
            else if( sqrt((dx*dx) + (dy*dy)) < distance){
                distance = sqrt((dx*dx) + (dy*dy));
                j = i;
            }
        }

        else if( enVue && x>xMur && x<(xMur+largeur)){
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


} */
