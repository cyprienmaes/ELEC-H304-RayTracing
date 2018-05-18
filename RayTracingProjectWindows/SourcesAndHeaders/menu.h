#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



#endif // MENU_H_INCLUDED

void createRectangle(int posX, int posY, int largeur, int hauteur, char R, char G, char B, SDL_Surface *screen);

void createText(const char* file, int taillePolice, int posX, int posY, const char* ecrit, SDL_Surface *screen);

void createEchelle(int posX, int posY, SDL_Surface *screen);

void createMenu(const char* file, int taillePolice, int largeurMenu, int hauteurMenu, int hauteurEcran, float echelle, SDL_Surface *screen);
