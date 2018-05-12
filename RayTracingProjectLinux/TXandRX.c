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
    char central;
    int longueur;
    int largeur;
    POINT pointCentral;
    SDL_Rect position;
    SDL_Surface *newRECEIVER;
};

TRANSMITTER *newTransmitter(float echelle, int xTX, int yTX, int longueur, int largeur, TRANSMITTER *transmitter, SDL_Surface *screen){
    transmitter = malloc(sizeof(TRANSMITTER));
    transmitter->position.x = round(xTX/echelle)-round(largeur/(2*echelle));
    transmitter->position.y = round(yTX/echelle)-round(longueur/(2*echelle));
    transmitter->longueur = longueur;
    transmitter->largeur = largeur;
    transmitter->pointCentral.x = xTX;
    transmitter->pointCentral.y = yTX;
    transmitter->newTRANSMITTER = SDL_CreateRGBSurface(SDL_SWSURFACE, longueur/echelle, largeur/echelle, 32, 0, 0, 0, 0);
    SDL_FillRect(transmitter->newTRANSMITTER, NULL, SDL_MapRGB(screen->format, 252, 56, 237));
    SDL_BlitSurface(transmitter->newTRANSMITTER, NULL, screen, &transmitter->position);
    return transmitter;
}

RECEIVER *newReceiver(float echelle, char central, int xRX, int yRX, int longueur, int largeur, RECEIVER *receiver, SDL_Surface *screen) {
    receiver = malloc(sizeof(RECEIVER));
    receiver->central = central;
    receiver->largeur = largeur;
    receiver->longueur = longueur;
    receiver->position.x = round(xRX/echelle)-round(largeur/(2*echelle));
    receiver->position.y = round(yRX/echelle)-round(longueur/(2*echelle));
    receiver->pointCentral.x = xRX;
    receiver->pointCentral.y = yRX;
    receiver->newRECEIVER = SDL_CreateRGBSurface(SDL_SWSURFACE, longueur/echelle,largeur/echelle, 32, 0, 0, 0, 0);
    SDL_FillRect(receiver->newRECEIVER, NULL, SDL_MapRGB(screen->format, 215, 220, 10));
    SDL_SetAlpha(receiver->newRECEIVER, SDL_SRCALPHA, 255);
    SDL_BlitSurface(receiver->newRECEIVER, NULL, screen, &receiver->position);
    return receiver;
}

RECEIVER UnReceiver(float echelle, char central, int xRX, int yRX, int longueur, int largeur, SDL_Surface *screen) {
    RECEIVER receiver;
    receiver.central = central;
    receiver.largeur = largeur;
    receiver.longueur = longueur;
    receiver.position.x = round(xRX/echelle)-round(largeur/(2*echelle));
    receiver.position.y = round(yRX/echelle)-round(longueur/(2*echelle));
    receiver.pointCentral.x = xRX;
    receiver.pointCentral.y = yRX;
    receiver.newRECEIVER = SDL_CreateRGBSurface(SDL_SWSURFACE, longueur/echelle,largeur/echelle, 32, 0, 0, 0, 0);
    SDL_FillRect(receiver.newRECEIVER, NULL, SDL_MapRGB(screen->format, 215, 220, 10));
    SDL_SetAlpha(receiver.newRECEIVER, SDL_SRCALPHA, 255);
    SDL_BlitSurface(receiver.newRECEIVER, NULL, screen, &receiver.position);
    return receiver;
}

RECEIVER *zoneReception(float echelle, int xRX,int yRX,RECEIVER *receiver,SDL_Surface *screen) {
    // Indice pour une matrice
    int i = -5;
    int j = -5;
    // Creation d'une matrice de reciver
    receiver = malloc(11*11*sizeof(RECEIVER));
    for (j=-5;j<6;j++){
        for (i = -5;i<6;i++){
            if (i==0 && j ==0) receiver[(i+5)*(j+6)] = UnReceiver(echelle,1,xRX+(i*10),yRX+(j*10),10,10,screen);
            else receiver[(i+5)*(j+6)] = UnReceiver(echelle,0,xRX+(i*10),yRX+(j*10),10,10,screen);
        }
    }
    return receiver;
}

