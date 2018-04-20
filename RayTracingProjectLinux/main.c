#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "videoInitialisation.h"
#include "line.h"
#include "reflection.h"
#include "TXandRX.h"
#include "point.h"


int main(int argc, char *argv[]) {

    int hauteurEcran = 500;
    int largeurEcran = 800;
    int hauteurMenu = 100;
    int largeurMenu = 800;

    WALL* wall = NULL;
    TRANSMITTER *transmitter = NULL;
    RECEIVER *receiver = NULL;
    printf("Emetteur en rose\n");
    printf("Recepteur en jaune\n");
    // First rectangle which correspond to the screen
    SDL_Surface *screen = NULL;

    // Loading of the video display.
    SDL_Init(SDL_INIT_VIDEO);

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    // Video mode (resolution => 600x600 for example, color displaying, other parameters according to the memory)
    screen = SDL_SetVideoMode(largeurEcran, hauteurEcran+hauteurMenu, 32, SDL_SWSURFACE);

    if (screen == NULL) {
        fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    // Initialisation de la librairie TTF qui permet d'ecrire dans une fenetre SDL.
    TTF_Init();

    if(TTF_Init() == -1) {
        // Si jamais une erreur d'initialisation devait arriver.
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Saving of a color in the memory. Using of RGB map (256 colors).
    // Format is an under-variale of screen and give the color displaying which is the most
    // of the time 32 bits.
    Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255);
    // Filling of the rectangle
    SDL_FillRect(screen, NULL, white);
    // Title of the main frame
    SDL_WM_SetCaption("Projet de Ray-Tracing v0.1.0", NULL);

    wall = SquareMap(screen,wall,largeurEcran,hauteurEcran);
    transmitter = newTransmitter(20,320,transmitter,screen);
    receiver = newReceiver(320, 250, receiver, screen);
    // doubleReflection(receiver, transmitter, wall, screen);
    methodImage(transmitter->position.x+5, transmitter->position.y+5, receiver->position.x+5, receiver->position.y+5, wall, screen, 2);
    SDL_Flip(screen);
    createMenu("GeosansLight.ttf",16,largeurMenu, hauteurMenu, hauteurEcran, screen);
    // Deleting surface inside de memory
    freeWALL(wall);

    // Arret de la librairie TTF
    //TTF_CloseFont(police);
    TTF_Quit();
    // Stoping of SDL
    SDL_Quit();
    return EXIT_SUCCESS;
}

void createRectangle(int posX, int posY, int largeur, int hauteur, char R, char G, char B, SDL_Surface *screen) {
/*
    Creation simple de rectangles.
*/
    SDL_Rect position;
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
    TTF_Font *font = NULL;
    font = TTF_OpenFont(file, taillePolice);

    SDL_Surface *texte = NULL;
    SDL_Rect positionTexte;
    SDL_Color noir = {0,0,0};
    SDL_Color blanc = {255,255,255};
    texte = TTF_RenderUTF8_Shaded(font, ecrit, noir, blanc);
    positionTexte.x = posX;
    positionTexte.y = posY;
    SDL_BlitSurface(texte,NULL,screen,&positionTexte);
    TTF_CloseFont(font);
    SDL_FreeSurface(texte);
}

void createMenu(const char* file, int taillePolice, int largeurMenu, int hauteurMenu, int hauteurEcran, SDL_Surface *screen) {
/*
    Creation d'un menu dans le bas de la fenetre.
*/
    createRectangle(0,hauteurEcran,largeurMenu, hauteurMenu, 200, 200, 200, screen);
    createRectangle(largeurMenu/2-300, hauteurEcran+hauteurMenu/2-10, 100, 20,255,255,255,screen);
    createRectangle(largeurMenu/2-50, hauteurEcran+hauteurMenu/2-10, 100, 20,255,255,255,screen);
    createRectangle(largeurMenu/2+200, hauteurEcran+hauteurMenu/2-10, 100, 20,255,255,255,screen);
    createText(file, taillePolice, largeurMenu/2-300, hauteurEcran+hauteurMenu/2-30, "Paramètres : ", screen);
    createText(file, taillePolice, largeurMenu/2-50, hauteurEcran+hauteurMenu/2-30, "Position en x : ", screen);
    createText(file, taillePolice,largeurMenu/2+200, hauteurEcran+hauteurMenu/2-30, "Position en y : ", screen);
    posSouris(file, taillePolice, largeurMenu/2-50, hauteurEcran+hauteurMenu/2-10, largeurMenu/2+200, hauteurEcran+hauteurMenu/2-10, screen);
}

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
        //SDL_UpdateRect(screen, 0, 500, 800, 100);
        SDL_Flip(screen);
    }
}
