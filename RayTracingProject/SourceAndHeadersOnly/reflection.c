#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "line.h"
#include "wall.h"

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
