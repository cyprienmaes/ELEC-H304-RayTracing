#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h"

typedef struct TRANSMITTER TRANSMITTER;
typedef struct RECEIVER RECEIVER;

struct TRANSMITTER{
    int longueur;
    int largeur;
    POINT pointCentral;
    SDL_Rect position;
    SDL_Surface *newTRANSMITTER;
};

struct RECEIVER{
    int longueur;
    int largeur;
    POINT pointCentral;
    SDL_Rect position;
    SDL_Surface *newRECEIVER;
};

TRANSMITTER *newTransmitter(int xTX, int yTX, int longueur, int largeur, TRANSMITTER *transmitter, SDL_Surface *screen){
    transmitter = malloc(sizeof(TRANSMITTER));
    transmitter->position.x = xTX-largeur/2;
    transmitter->position.y = yTX-longueur/2;
    transmitter->longueur = longueur;
    transmitter->largeur = largeur;
    transmitter->pointCentral.x = transmitter->position.x+transmitter->largeur/2;
    transmitter->pointCentral.y = transmitter->position.y+transmitter->longueur/2;
    transmitter->newTRANSMITTER = SDL_CreateRGBSurface(SDL_SWSURFACE, 10, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(transmitter->newTRANSMITTER, NULL, SDL_MapRGB(screen->format, 252, 56, 237));
    SDL_BlitSurface(transmitter->newTRANSMITTER, NULL, screen, &transmitter->position);
    return transmitter;
}

RECEIVER *newReceiver(int xRX, int yRX, int longueur, int largeur, RECEIVER *receiver, SDL_Surface *screen) {
    receiver = malloc(sizeof(RECEIVER));
    receiver->largeur = largeur;
    receiver->longueur = longueur;
    receiver->position.x = xRX-largeur/2;
    receiver->position.y = yRX-largeur/2;
    receiver->pointCentral.x = receiver->position.x+receiver->largeur/2;
    receiver->pointCentral.y = receiver->position.y+receiver->longueur/2;
    receiver->newRECEIVER = SDL_CreateRGBSurface(SDL_SWSURFACE, 10, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(receiver->newRECEIVER, NULL, SDL_MapRGB(screen->format, 215, 220, 10));
    SDL_BlitSurface(receiver->newRECEIVER, NULL, screen, &receiver->position);
    return receiver;
}

