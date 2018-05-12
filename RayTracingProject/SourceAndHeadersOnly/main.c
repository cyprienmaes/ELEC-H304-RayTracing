#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "coefficients.h"
#include "wall.h"
#include "line.h"
#include "reflection.h"
#include "TXandRX.h"
#include "point.h"
#include "menu.h"
#include "evenement.h"
#include "intersection.h"
#include "droite.h"
#include "transmission.h"

int main(int argc, char *argv[]) {
    float echelle = 1.7;
    int hauteurEcran = 700; // en cm
    int largeurEcran = 1400; // en cm
    int hauteurMenu = 100;
    int largeurMenu = 1400;

    double sum = 0;

    WALL* wall = NULL;
    TRANSMITTER *transmitter = NULL;
    double puissance = 20; // puissance � l'emetteur (en dBm)
    double frequence = 2.45*pow(10,9); //2.45 GHz

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
    screen = SDL_SetVideoMode((largeurEcran/echelle)+4, (hauteurEcran/echelle)+4+hauteurMenu, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

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
    SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,0,0,0));
    // Title of the main frame
    SDL_WM_SetCaption("Projet de Ray-Tracing v1.3.0", NULL);
    // Creation de la map
    wall = MapExempleRapport2(largeurEcran, hauteurEcran, echelle, screen, wall);
    // Creation de l'emetteur et du recepteur.
    transmitter = newTransmitter(echelle, 100, 200, 20, 20, puissance, frequence, transmitter, screen);
    receiver = newReceiver(echelle, 1, 1100, 400, 20,20, receiver, screen);

    sum = onde(echelle,receiver,transmitter,wall,screen);
    printf("La somme au carre est donc : %.15f\n", sum);
    double sum2 = 0.0029;

    double Prx = calcul_Prx(receiver, transmitter, sum2);
    printf("La puissance en dBm est donc : %f \n",Prx);

    SDL_Flip(screen);
    // Creation d'un menu ou s'affiche certaines donnees
    createMenu("GeosansLight.ttf",16,largeurMenu,hauteurMenu,hauteurEcran,echelle,screen);
    SDL_Flip(screen);
    // Gestion d'evenement avec la souris.
    posSouris(echelle, largeurEcran, hauteurEcran, "GeosansLight.ttf",16,largeurMenu/(2*echelle)-50, hauteurEcran/echelle+4+hauteurMenu/2-10, largeurMenu/(2*echelle)+300/echelle, hauteurEcran/echelle+4+hauteurMenu/2-10,screen);
    // Deleting surface inside de memory
    freeWALL(wall);
    SDL_Flip(screen);
    // Arret de la librairie TTF
    TTF_Quit();
    // Stoping of SDL
    SDL_Quit();
    return EXIT_SUCCESS;
}
