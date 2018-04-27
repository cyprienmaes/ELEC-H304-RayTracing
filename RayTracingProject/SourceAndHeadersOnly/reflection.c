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
    POINT point;    point.x = (wall[6].position.x);     point.y = wall[6].position.y+100;
    POINT source;   source.x = xSource;     source.y = ySource;

    DROITE droite1; droite1.x0 = xSource; droite1.y0 = ySource; droite1.x1 = point.x; droite1.y1 = point.y;

    POINT intersect = intersection(droite1, wall[6].droite);

    line(source.x, source.y, intersect.x, intersect.y, SDL_MapRGB(screen->format,255,0,100), screen);

    POINT newSource = pointImage(source, intersect, wall[6]);
    line(newSource.x, newSource.y, intersect.x, intersect.y, SDL_MapRGB(screen->format,255,0,100), screen);
}
