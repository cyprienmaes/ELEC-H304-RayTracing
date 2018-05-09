#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h"

#ifndef TXANDRX_H_INCLUDED
#define TXANDRX_H_INCLUDED


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

TRANSMITTER *newTransmitter(int xTX, int yTX, int longueur, int largeur, TRANSMITTER *transmitter, SDL_Surface *screen);

RECEIVER *newReceiver(int xRX, int yRX, int longueur, int largeur, RECEIVER *receiver, SDL_Surface *screen);


#endif // TXANDRX_H_INCLUDED


