#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "videoInitialisation.h"
#include "line.h"
#include "reflection.h"
#include "TXandRX.h"
#include "intersection.h"

//////////////////////////////////////////

int main(int argc, char *argv[]) {
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
    screen = SDL_SetVideoMode(600, 600, 32, SDL_SWSURFACE);

    if (screen == NULL) {
        fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Saving of a color in the memory. Using of RGB map (256 colors).
    // Format is an under-variale of screen and give the color displaying which is the most
    // of the time 32 bits.
    Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255);
    // Filling of the rectangle
    SDL_FillRect(screen, NULL, white);
    // Title of the main frame
    SDL_WM_SetCaption("Projet de Ray-Tracing v0.0.3", NULL);

    wall = SquareMap(screen, wall);

    transmitter = newTransmitter(20,500,transmitter,screen);
    receiver = newReceiver(500, 250, receiver, screen);
    // doubleReflection(receiver, transmitter, wall, screen);
    //methodImage(transmitter->position.x+5, transmitter->position.y+5, receiver->position.x+5, receiver->position.y+5, wall, screen, 2);


    // EXEMPLE D'UTILISATION DE INTERSECTION
    DROITE droite1; DROITE droite2;
    POINT croisement;

    droite1.x0 = 0; droite1.y0 = 2,35;
    droite1.x1 = 4; droite1.y1 = 12.47;
    line(droite1.x0, droite1.y0, droite1.x1, droite1.y1, SDL_MapRGB(screen->format,0,100,255), screen);

    droite2.x0 = 0; droite2.y0 = -3.41;
    droite2.x1 = 10; droite2.y1 = 48.89;
    line(droite2.x0, droite2.y0, droite2.x1, droite2.y1, SDL_MapRGB(screen->format,100,0,255), screen);

    croisement = intersection(droite1, droite2);
    transmitter = newTransmitter(croisement.x, croisement.y, transmitter, screen); // Juste pour avoir un visuel sur l'intersection



    // Update of the frame
    SDL_Flip(screen);

    StayDisplay();

    // Deleting surface inside de memory
    freeWALL(wall);

    // Stoping of SDL
    SDL_Quit();
    return EXIT_SUCCESS;
}
