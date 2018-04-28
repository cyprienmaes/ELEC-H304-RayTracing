#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>

void line(int x0, int y0, int x1, int y1, Uint32 c, SDL_Surface *screen) {
    int dx, dy, x, y, residu, absdx, absdy, pasx, pasy,i;
    dx = x1-x0;
    dy = y1-y0;
    residu = 0;
    x = x0;
    y = y0;
    putPixel(x, y, c, screen);

    if (dx>0) pasx=1;
    else pasx=-1;
    if (dy>0) pasy=1;
    else pasy=-1;

    absdx = abs(dx);
    absdy = abs(dy);

    if (dx == 0) {
        for(i=0;i<absdy;i++){
            y+=pasy;
            putPixel(x,y,c,screen);
        }
    }
    else if (dy == 0) {
        for(i=0; i<absdx;i++){
            x+=pasx;
            putPixel(x,y,c,screen);
        }
    }
    else if (absdx == absdy) {
        for (i=0;i<absdx;i++){
            x+=pasx;
            y+=pasy;
            putPixel(x,y,c,screen);
        }
    }
    else if (absdx>absdy) {
        for(i=0;i<absdx;i++){
            x+=pasx;
            residu+=absdy;
            if(residu >= absdx){
                residu-=absdx;
                y+=pasy;
            }
            putPixel(x,y,c,screen);
        }
    }
    else {
        for(i=0;i<absdy;i++){
            y+=pasy;
            residu+=absdx;
            if(residu >= absdy) {
                residu-=absdy;
                x+=pasx;
            }
            putPixel(x,y,c,screen);
        }
    }
}

void putPixel(int x, int y, Uint32 c, SDL_Surface *screen) {
    Uint32 *numeroCase;
    numeroCase = (Uint32 *)(screen->pixels)+x+y*screen->w;
    *numeroCase = c;
}
