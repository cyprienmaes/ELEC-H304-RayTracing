#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "point.h"
#include "wall.h"

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

TRANSMITTER newTransmitter(float echelle, int xTX, int yTX, int longueur, int largeur, double puissance, double frequence, Uint8 r, Uint8 v, Uint8 b, SDL_Surface *screen){
    TRANSMITTER transmitter;
    transmitter.position.x = round(xTX/echelle)-round(largeur/(2*echelle));
    transmitter.position.y = round(yTX/echelle)-round(longueur/(2*echelle));
    transmitter.longueur = longueur;
    transmitter.largeur = largeur;
    transmitter.puissance = pow(10, (puissance/10)-3); // conversion dBm à W
    transmitter.resistance = (720*pi)/32; // résistance d'une antenne dipôle
    transmitter.directivite = 16/(3*pi); // directivite d'une antenne dipole sur le plan affiché (theta = 90°)
    transmitter.frequence = frequence; // en Hz
    transmitter.pointCentral.x = xTX;
    transmitter.pointCentral.y = yTX;
    transmitter.newTRANSMITTER = SDL_CreateRGBSurface(SDL_SWSURFACE, longueur/echelle, largeur/echelle, 32, 0, 0, 0, 0);
    SDL_FillRect(transmitter.newTRANSMITTER, NULL, SDL_MapRGB(screen->format, 252, 56, 237));
    SDL_BlitSurface(transmitter.newTRANSMITTER, NULL, screen, &transmitter.position);
    return transmitter;
}

double calcul_Prx(RECEIVER receiver, TRANSMITTER transmitter, double sum2){
    // Calcul de la puissance moyenne (en dBm) collectée au recepteur sur une zone locale de 1 metre carré
    // - lambda : longueur d'onde
    // - lambda/pi : hauteur equivalente dans le cas de d'une antenne dipole receptrice à theta = 90°
    // - Prx : puissance moyenne recue
    // - Ra : résistance d'antenne
    // - sum2 : est la somme cumulée du quotient (coef_reflexion_transmission_tot / distance) de chaque onde parvenant à la zone de reception
    // REMARQUE, hauteur equivalente et rendement pourrait etre parametres de receiver et transmitter
    double f = transmitter.frequence;

    double D = transmitter.directivite;

    double Ra = transmitter.resistance;

    double Ptx = transmitter.puissance;

    double lambda = (3*pow(10,8))/f; // longueur d'onde = c/f

    double gain = 1*D; // Si rendement emetteur different de 1, remplacer '1' par celui-ci

    double a = (1/(8*Ra));
    double b = pow((lambda/pi),2);
    double c = (60*gain*Ptx);

    double Prx = a* b * c * sum2;

    return 20*log10(Prx/0.001); //conversion en dBm
}

float Bps(double Prx) {
    float MBps;
    MBps = round((-12.0/5.0)*(abs(round(Prx))-(191.0/2.0)));
    return MBps;
}

RECEIVER newReceiver(float echelle, char central, int xRX, int yRX, int longueur, int largeur, TRANSMITTER transmitter) {
    RECEIVER receiver;
    receiver.central = central;
    receiver.largeur = largeur;
    receiver.longueur = longueur;
    receiver.position.x = round(xRX/echelle)-round(largeur/(2*echelle));
    receiver.position.y = round(yRX/echelle)-round(longueur/(2*echelle));
    receiver.pointCentral.x = xRX;
    receiver.pointCentral.y = yRX;
    receiver.newRECEIVER = SDL_CreateRGBSurface(SDL_SWSURFACE,longueur/echelle,largeur/echelle, 32, 0, 0, 0, 0);
    return receiver;
}

void dessinReceiver(float echelle, float debit, RECEIVER receiver, SDL_Surface *screen) {
    Uint8 r; Uint8 b; Uint8 v;
    int i = 146 - debit;
    if (i<0) {
        r = 255;
        v = 0;
        b = 0;
    }
    else if (i>=0 && i<=23){
        r = 255;
        v = i*11;
        b = 0;
    }
    else if (i>23 && i<=46){
        r = 255 - (i-23)*11;
        v = 255;
        b = 0;
    }
    else if (i>46 && i<=69){
        r = 0;
        v = 255;
        b = (i-46)*11;
    }
    else if (i>69 && i<=92){
        r = 0;
        v = 255 - (i-69)*11;
        b = 255;
    }
    else if (i>92 && i<=146){
        r = 0;
        v = 0;
        b = 255-(i-92)*4;
    }
    else {
        r = 0;
        v = 0;
        b = 0;
    }
    SDL_FillRect(receiver.newRECEIVER, NULL, SDL_MapRGB(screen->format,r, v, b));
    SDL_SetAlpha(receiver.newRECEIVER, SDL_SRCALPHA, 255);
    SDL_BlitSurface(receiver.newRECEIVER, NULL, screen, &receiver.position);
}

RECEIVER *zoneDeReception(float echelle, int xRX, int yRX, TRANSMITTER transmitter, RECEIVER *zone){
    int i = 0;
    int j = 0;
    zone = malloc(11*9*sizeof(RECEIVER));
    for (j=0;j<9;j++){
        for (i=0;i<11;i++){
            if (i+(j*11)==49) zone[i+(j*11)] = newReceiver(echelle,1,xRX+(10*(i-5)),yRX+(10*(j-5)),10,10, transmitter);
            else zone[i+(j*11)] = newReceiver(echelle,0,xRX+(10*(i-5)),yRX+(10*(j-5)),10,10,transmitter);
        }
    }
    return zone;
}


RECEIVER *Mapping(float echelle, int largeurEcran, int hauteurEcran, int carre, TRANSMITTER transmitter, RECEIVER *zone){
    zone = malloc((largeurEcran/carre)*(hauteurEcran/carre)*sizeof(RECEIVER));
    int i = 0;
    int j = 0;
    for(j=0;j<hauteurEcran/carre;j++){
        for (i=0;i<largeurEcran/carre;i++){
            zone[i+(j*largeurEcran/carre)] = newReceiver(echelle, 0, carre/2+(i*carre), carre/2+(j*carre), carre, carre, transmitter);
        }
    }
    return zone;
}
