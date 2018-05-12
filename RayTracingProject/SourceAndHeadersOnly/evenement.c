#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"

void posSouris(float echelle, int largeurEcran, int hauteurEcran, const char* file, int taillePolice,int posXx, int posYx, int posXy, int posYy, SDL_Surface *screen) {
/*
    Ecrit la position en x et en y de la souris dès qu'elle bouge de l'ecran.
*/
    SDL_Event bougeSouris;
    char posx[20];
    char posy[20];
    int x;
    int y;
    int continuer = 1;
    while (continuer) {
        SDL_WaitEvent(&bougeSouris);
        switch(bougeSouris.type) {
            case SDL_MOUSEMOTION :
                x = bougeSouris.motion.x*echelle;
                y = bougeSouris.motion.y*echelle;
                break;
            case SDL_QUIT:
                continuer = 0;
                break;
        }
        if (x < 0 || x > largeurEcran+4 || y < 0 || y > hauteurEcran) {
            SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,255,255,255));
            createText(file, taillePolice, posXy, posYy, "En dehors", screen);
            createText(file, taillePolice, posXx, posYx, "En dehors", screen);
            SDL_UpdateRect(screen, posXx, posYx, 100, 20);
            SDL_UpdateRect(screen, posXy, posYy, 100, 20);
        }
        else {
            sprintf(posx, "%d",x);
            sprintf(posy, "%d",y);
            SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,255,255,255));
            createText(file, taillePolice, posXy, posYy, posy, screen);
            createText(file, taillePolice, posXx, posYx, posx, screen);
            SDL_UpdateRect(screen, posXx, posYx, 100, 20);
            SDL_UpdateRect(screen, posXy, posYy, 100, 20);
        }
    }
}
