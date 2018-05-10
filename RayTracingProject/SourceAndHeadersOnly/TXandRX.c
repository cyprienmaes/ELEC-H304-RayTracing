#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h"

#define pi 3.14159

typedef struct TRANSMITTER TRANSMITTER;
typedef struct RECEIVER RECEIVER;

struct TRANSMITTER{
    int longueur;
    int largeur;
    float puissance; // Puissance à l'emetteur (en W)
    float resistance;  // Resistance d'antenne
    float directivite; // directivité
    float frequence;
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

TRANSMITTER *newTransmitter(int xTX, int yTX, int longueur, int largeur, float puissance, float frequence, TRANSMITTER *transmitter, SDL_Surface *screen){
    transmitter = malloc(sizeof(TRANSMITTER));
    transmitter->position.x = xTX-largeur/2;
    transmitter->position.y = yTX-longueur/2;
    transmitter->longueur = longueur;
    transmitter->largeur = largeur;
    transmitter->puissance = pow(10, (puissance/10)-3); // conversion dBm à W
    transmitter->resistance = (720*pi)/32; // résistance d'une antenne dipôle
    transmitter->directivite = 16/(3*pi); // directivite d'une antenne dipole sur le plan affiché (theta = 90°)
    transmitter->frequence = frequence; // en Hz
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

float calcul_Prx(RECEIVER *receiver, TRANSMITTER *transmitter, float sum2){
    // Calcul de la puissance moyenne (en dBm) collectée au recepteur sur une zone locale de 1 metre carré
    // - lambda : longueur d'onde
    // - lambda/pi : hauteur equivalente dans le cas de d'une antenne dipole receptrice à theta = 90°
    // - Prx : puissance moyenne recue
    // - Ra : résistance d'antenne
    // - sum2 : est la somme cumulée du quotient (coef_reflexion_transmission_tot / distance) de chaque onde parvenant à la zone de reception
    // REMARQUE, hauteur equivalente et rendement pourrait etre parametres de receiver et transmitter
    float f = transmitter->frequence;
    float D = transmitter->directivite;
    float Ra = transmitter->resistance;
    float Ptx = transmitter->puissance;

    float lambda = (3*pow(10,8))/f; // longueur d'onde = c/f
    float gain = 1*D; // Si rendement emetteur different de 1, remplacer '1' par celui-ci
    float Prx = (1/8*Ra) * pow((lambda/pi),2) * (60*gain*Ptx) * sum2;

    return 10*log10(Prx/0.001); //conversion en dBm
}
