#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
typedef struct TRANSMITTER TRANSMITTER;
typedef struct RECEIVER RECEIVER;

struct TRANSMITTER{
    SDL_Rect position;
    SDL_Surface *newTRANSMITTER;
};

struct RECEIVER{
    SDL_Rect position;
    SDL_Surface *newRECEIVER;
};

TRANSMITTER *newTransmitter(int xTX, int yTX, TRANSMITTER *transmitter, SDL_Surface *screen){
    transmitter = malloc(sizeof(TRANSMITTER));
    transmitter->position.x = xTX-5;
    transmitter->position.y = yTX-5;
    transmitter->newTRANSMITTER = SDL_CreateRGBSurface(SDL_SWSURFACE, 10, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(transmitter->newTRANSMITTER, NULL, SDL_MapRGB(screen->format, 252, 56, 237));
    SDL_BlitSurface(transmitter->newTRANSMITTER, NULL, screen, &transmitter->position);
    return transmitter;
}

RECEIVER *newReceiver(int xRX, int yRX, RECEIVER *receiver, SDL_Surface *screen) {
    receiver = malloc(sizeof(RECEIVER));
    receiver->position.x = xRX-5;
    receiver->position.y = yRX-5;
    receiver->newRECEIVER = SDL_CreateRGBSurface(SDL_SWSURFACE, 10, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(receiver->newRECEIVER, NULL, SDL_MapRGB(screen->format, 215, 220, 10));
    SDL_BlitSurface(receiver->newRECEIVER, NULL, screen, &receiver->position);
    return receiver;
}

