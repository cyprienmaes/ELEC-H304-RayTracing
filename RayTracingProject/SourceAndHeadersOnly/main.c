#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "line.h"
#include "reflection.h"
#include "TXandRX.h"
#include "point.h"
#include "menu.h"
#include "evenement.h"
#include "intersection.h"

int main(int argc, char *argv[]) {

    int hauteurEcran = 800; // en cm
    int largeurEcran = 1120; // en cm
    int hauteurMenu = 100;
    int largeurMenu = 1120;

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
    screen = SDL_SetVideoMode(largeurEcran/scaling, (hauteurEcran/scaling)+hauteurMenu, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

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

    // Filling of the rectangle
    SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,255,255,255));
    // Title of the main frame
    SDL_WM_SetCaption("Projet de Ray-Tracing v0.1.0", NULL);
    // Creation de la map
    wall = MapUn(screen,wall,largeurEcran,hauteurEcran);
    // Creation de l'emetteur et du recepteur.
    transmitter = newTransmitter(20,320,transmitter,screen);
    receiver = newReceiver(320, 250, receiver, screen);
    // Methode image obolete mais juste pour voir
    // methodImage(transmitter->position.x+5, transmitter->position.y+5, receiver->position.x+5, receiver->position.y+5, wall, screen, 2);

    emission(transmitter->position.x+5, transmitter->position.y+5, wall, screen);




    // Creation d'un menu ou s'affiche certaines donnees
    createMenu("GeosansLight.ttf",16,largeurMenu,hauteurMenu,hauteurEcran,screen);
    SDL_Flip(screen);
    // Gestion d'evenement avec la souris.
    posSouris("GeosansLight.ttf",16,largeurMenu/(2*scaling)-50, (hauteurEcran/scaling)+(hauteurMenu/2)-10, largeurMenu/(2*scaling)+300/scaling, (hauteurEcran/scaling)+(hauteurMenu/2)-10,screen);
    // Deleting surface inside de memory
    freeWALL(wall);
    SDL_Flip(screen);
    // Arret de la librairie TTF
    TTF_Quit();
    // Stoping of SDL
    SDL_Quit();
    return EXIT_SUCCESS;
}
