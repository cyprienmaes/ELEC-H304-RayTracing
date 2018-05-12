#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "wall.h"

void createRectangle(int posX, int posY, int largeur, int hauteur, char R, char G, char B, SDL_Surface *screen) {
/*
    Creation simple de rectangles.
*/
    // Position du rectangle.
    SDL_Rect position;
    // Creation de la surface
    SDL_Surface *newRect;
    position.x = posX;
    position.y = posY;
    newRect = SDL_CreateRGBSurface(SDL_SWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    SDL_FillRect(newRect, NULL, SDL_MapRGB(screen->format, R, G, B));
    SDL_BlitSurface(newRect, NULL, screen, &position);
}

void createText(const char* file, int taillePolice, int posX, int posY, const char* ecrit, SDL_Surface *screen) {
/*
    Créer du texte à un endorit voulu de la fenetre.
    - File est le fichier de police.
    - Ecrit est ce qu'il faut afficher.
*/
    // Creation de la police
    TTF_Font *font = NULL;
    font = TTF_OpenFont(file, taillePolice);
    // Creation de la surface ou sera ecrit le texte
    SDL_Surface *texte =NULL;
    // Position de la surface
    SDL_Rect positionTexte;
    SDL_Color noir = {0,0,0};
    texte = TTF_RenderUTF8_Blended(font, ecrit, noir);
    positionTexte.x = posX;
    positionTexte.y = posY;
    SDL_BlitSurface(texte,NULL,screen,&positionTexte);
    // Libération de la memoire mais toujours affiche a l'ecran.
    TTF_CloseFont(font);
    SDL_FreeSurface(texte);
}


void createMenu(const char* file, int taillePolice, int largeurMenu, int hauteurMenu, int hauteurEcran, float echelle, SDL_Surface *screen) {
/*
    Creation d'un menu dans le bas de la fenetre.
*/
    // Rectangle gris principale.
    createRectangle(0,hauteurEcran/echelle+4,largeurMenu/echelle+4, hauteurMenu, 200, 200, 200, screen);
    // Rectangle blanc pouvant afficher des donnees
    createRectangle(largeurMenu/(2*echelle)-500/echelle,hauteurEcran/echelle+4+hauteurMenu/2-10, 100, 20,255,255,255,screen);
    createRectangle(largeurMenu/(2*echelle)-50,hauteurEcran/echelle+4+hauteurMenu/2-10, 100, 20,255,255,255,screen);
    createRectangle(largeurMenu/(2*echelle)+300/echelle, hauteurEcran/echelle+4+hauteurMenu/2-10, 100, 20,255,255,255,screen);
    // Texte au-dessus du rectangle.
    createText(file, taillePolice, largeurMenu/(2*echelle)-500/echelle, hauteurEcran/echelle+4+hauteurMenu/2-30, "Paramètres : ", screen);
    createText(file, taillePolice, largeurMenu/(2*echelle)-50, hauteurEcran/echelle+4+hauteurMenu/2-30, "Position en x : ", screen);
    createText(file, taillePolice, largeurMenu/(2*echelle)+300/echelle, hauteurEcran/echelle+4+hauteurMenu/2-30, "Position en y : ", screen);
}
