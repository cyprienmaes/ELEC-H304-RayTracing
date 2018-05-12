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

TRANSMITTER *newTransmitter(float echelle, int xTX, int yTX, int longueur, int largeur, double puissance, double frequence, TRANSMITTER *transmitter, SDL_Surface *screen){
    transmitter = malloc(sizeof(TRANSMITTER));
    transmitter->position.x = round(xTX/echelle)-round(largeur/(2*echelle));
    transmitter->position.y = round(yTX/echelle)-round(longueur/(2*echelle));
    transmitter->longueur = longueur;
    transmitter->largeur = largeur;

    transmitter->puissance = pow(10, (puissance/10)-3); // conversion dBm à W
    transmitter->resistance = (720*pi)/32; // résistance d'une antenne dipôle
    transmitter->directivite = 16/(3*pi); // directivite d'une antenne dipole sur le plan affiché (theta = 90°)
    transmitter->frequence = frequence; // en Hz

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

double calcul_Prx(RECEIVER *receiver, TRANSMITTER *transmitter, double sum2){
    // Calcul de la puissance moyenne (en dBm) collectée au recepteur sur une zone locale de 1 metre carré
    // - lambda : longueur d'onde
    // - lambda/pi : hauteur equivalente dans le cas de d'une antenne dipole receptrice à theta = 90°
    // - Prx : puissance moyenne recue
    // - Ra : résistance d'antenne
    // - sum2 : est la somme cumulée du quotient (coef_reflexion_transmission_tot / distance) de chaque onde parvenant à la zone de reception
    // REMARQUE, hauteur equivalente et rendement pourrait etre parametres de receiver et transmitter
    double f = transmitter->frequence;
    printf("FREQUENCE = %f \n", f);

    double D = transmitter->directivite;
    printf("DIRECTIVITE = %f \n", D);

    double Ra = transmitter->resistance;
    printf("RESISTANCE = %f \n", Ra);

    double Ptx = transmitter->puissance;
    printf("P TRANSMISSION = %f \n", Ptx);
//////////////////////////////////

    double lambda = (3*pow(10,8))/f; // longueur d'onde = c/f
    printf("LAMBDA = %f \n", lambda);

    double gain = 1*D; // Si rendement emetteur different de 1, remplacer '1' par celui-ci
    printf("GAIN = %f \n", gain);

    double a = (1/(8*Ra));          printf("A = %f \n", a);
    double b = pow((lambda/pi),2);  printf("B = %f \n", b);
    double c = (60*gain*Ptx);       printf("C = %f \n", c);

    double Prx = a* b * c * sum2;
    printf("Puissance en Watt = %E \n", Prx);

    return 10*log10(Prx/0.001); //conversion en dBm
}

