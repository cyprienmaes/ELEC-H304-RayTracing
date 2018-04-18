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
    methodImage(transmitter->position.x+5, transmitter->position.y+5, receiver->position.x+5, receiver->position.y+5, wall, screen, 2);
    // Update of the frame
    SDL_Flip(screen);

    StayDisplay();

    // Deleting surface inside de memory
    freeWALL(wall);

    // Stoping of SDL
    SDL_Quit();
    return EXIT_SUCCESS;
}

void doubleReflection(RECEIVER *receiver, TRANSMITTER *transmitter, WALL *wall, SDL_Surface *screen) {
    int dy, dx, i, xIm1, yIm1, xIm2, yIm2, yMur2, xMur2, yMur1, xMur1;
    int yWall1 = wall[1].position.y;
    int xWall1 = wall[1].position.x;
    int yWall2 = wall[3].position.y;
    int xWall2 = wall[3].position.x;
    int xTX = transmitter->position.x+5;
    int yTX = transmitter->position.y+5;
    int xRX = receiver->position.x+5;
    int yRX = receiver->position.y+5;
    float tgPhi, tgTheta;
    dy = yWall1 - yTX;
    xIm1 = xTX;
    yIm1 = yTX + 2*dy;
    dx = xWall2 - xIm1;
    xIm2 = xIm1 + 2*dx;
    yIm2 = yIm1;
    xMur2 = xWall2;
    tgPhi = (float) (xIm2-xRX)/(yIm2-yRX);
    yMur2 = (xMur2 - xRX + (yRX*tgPhi))/tgPhi;
    yMur1 = yWall1;
    tgTheta = (float) (yIm1-yMur2)/(xMur2-xIm1);
    xMur1 = ((tgTheta*xMur2)-yMur1+yMur2)/tgTheta;
    line(xTX, yTX, xMur1, yMur1, SDL_MapRGB(screen->format,74,152,89), screen);
    line(xMur1, yMur1, xMur2, yMur2, SDL_MapRGB(screen->format,74,152,89), screen);
    line(xMur2, yMur2, xRX, yRX, SDL_MapRGB(screen->format,74,152,89), screen);
}
