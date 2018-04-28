#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"

void posSouris(const char* file, int taillePolice,int posXx, int posYx, int posXy, int posYy, SDL_Surface *screen) {
/*
    Ecrit la position en x et en y de la souris dès qu'elle bouge de l'ecran.
*/
    SDL_Event bougeSouris;
    char posx[3];
    char posy[3];
    int continuer = 1;
    while (continuer) {
        SDL_WaitEvent(&bougeSouris);
        switch(bougeSouris.type) {
            case SDL_MOUSEMOTION :
                sprintf(posx, "%d",bougeSouris.motion.x);
                sprintf(posy, "%d",bougeSouris.motion.y);
                createText(file, taillePolice, posXx, posYx, posx, screen);
                createText(file, taillePolice, posXy, posYy, posy, screen);
                break;
            case SDL_QUIT:
                continuer = 0;
                break;
        }
        SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,255,255,255));
        createText(file, taillePolice, posXx, posYx, posx, screen);
        createText(file, taillePolice, posXy, posYy, posy, screen);
        SDL_UpdateRect(screen, posXx, posYx, 100, 20);
        SDL_UpdateRect(screen, posXy, posYy, 100, 20);
    }
}
