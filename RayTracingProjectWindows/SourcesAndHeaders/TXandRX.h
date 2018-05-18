#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h"
#include "wall.h"

#define pi 3.14159

#ifndef TXANDRX_H_INCLUDED
#define TXANDRX_H_INCLUDED


typedef struct TRANSMITTER TRANSMITTER;
typedef struct RECEIVER RECEIVER;

struct TRANSMITTER{
    int longueur;
    int largeur;
    double puissance; // Puissance à l'emetteur (en W)
    double resistance;  // Resistance d'antenne
    double directivite; // directivité
    double frequence;
    POINT pointCentral;
    SDL_Rect position;
    SDL_Surface *newTRANSMITTER;
};

struct RECEIVER{
    char central;
    int longueur;
    int largeur;
    POINT pointCentral;
    SDL_Rect position;
    SDL_Surface *newRECEIVER;
};

TRANSMITTER newTransmitter(float echelle, int xTX, int yTX, int longueur, int largeur, double puissance, double frequence, Uint8 r, Uint8 v, Uint8 b, SDL_Surface *screen);

double calcul_Prx(RECEIVER receiver, TRANSMITTER transmitter, double sum2);

float Bps(double Prx);

RECEIVER newReceiver(float echelle, char central, int xRX, int yRX, int longueur, int largeur, TRANSMITTER transmitter);

void dessinReceiver(float echelle, float debit, RECEIVER receiver, SDL_Surface *screen);

RECEIVER *zoneDeReception(float echelle, int xRX, int yRX, TRANSMITTER transmitter, RECEIVER *zone);

RECEIVER *Mapping(float echelle, int largeurEcran, int hauteurEcran, int carre, TRANSMITTER transmitter, RECEIVER *zone);

#endif // TXANDRX_H_INCLUDED


