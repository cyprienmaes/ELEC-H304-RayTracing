#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include "line.h"
#include "wall.h"
#include "point.h"
#include "intersection.h"
#include "TXandRX.h"
#include "droite.h"
#include "transmission.h"
#include "coefficients.h"

double coeffRef(POINT avant, POINT inter, WALL wall) {
    double theta;
    double coeff;
    theta = theta_i(avant.x,avant.y,inter.x,inter.y,wall.vertical);
    coeff = norme_coeff_reflexion(theta,wall.permitivity,wall.conductivity,wall.epaisseur);
    return coeff;
}

double troisReflexion(float echelle, POINT lePoint1, POINT lePoint2, int murNonConsiderer1, int murNonConsiderer2, RECEIVER receiver, TRANSMITTER transmitter, WALL *wall, SDL_Surface *screen) {
/*
Dessine toutes les possibilites de faire 3 reflexions entre l'emetteur et le recepteur.
*/
    double coefficient = 1;
    float dist = 0;
    double sum = 0;
    Uint32 couleur = SDL_MapRGB(screen->format,0,0,255); // Lignes bleues pour trois reflexions
    POINT nouvelleImage;      // Variable qui recoit le point image
    POINT inter[3];           // Variable contenant les trois points de reflexions de l'emetteur au recepteur
    DROITE droiteInter[3];    // Variable contenant les droites calculees de points en points
    int i = 0;
    // On regarde tous les murs sauf le mur de la dernier symetrie.
    for (i = 0; i<numberWall; i++) {
        if (i == murNonConsiderer2);
        else {
            // On creer un nouveau point image
            nouvelleImage = image(lePoint2, &wall[i]);
            // On en fait une droite avec le recepteur
            droiteInter[0] = createDroite(nouvelleImage.x,nouvelleImage.y,receiver.pointCentral.x,receiver.pointCentral.y);
            // On calcul l'intersection avec le mur de la symetrie du nouveau point image qu'on arrondit pour la fenetre
            inter[0] = intersection(droiteInter[0],wall[i].droite);
            inter[0].x = round(inter[0].x);
            inter[0].y = round(inter[0].y);
            // On creer une nouvelle droite entre le point d'intersection trouver
            // et le point image precedent.
            droiteInter[1] = createDroite(inter[0].x,inter[0].y,lePoint2.x,lePoint2.y);
            // On calcul l'intersection selon le mur de symetrie precedent
            inter[1] = intersection(droiteInter[1],wall[murNonConsiderer2].droite);
            inter[1].x = round(inter[1].x);
            inter[1].y = round(inter[1].y);
            // On creer une nouvelle droite entre le point d'intersection trouver
            // et le point image precedent le precedent.
            droiteInter[2] = createDroite(inter[1].x,inter[1].y,lePoint1.x,lePoint1.y);
            // On calcul l'intersection selon le mur de symetrie precedent le precedent
            inter[2] = intersection(droiteInter[2],wall[murNonConsiderer1].droite);
            inter[2].x = round(inter[2].x);
            inter[2].y = round(inter[2].y);
            // On test toutes les intersections pour etre sur que la reflexion existe
            if (interExiste(&wall[i],inter[0],inter[1],receiver.pointCentral)==1) {
                if (interExiste(&wall[murNonConsiderer2], inter[1], inter[2], inter[0])==1) {
                    if(interExiste(&wall[murNonConsiderer1], inter[2], transmitter.pointCentral, inter[1])==1) {
                        // On calcul tous les coefficients du aux transmissions et on les multiplie ensemble
                        coefficient *= transmission(-1, murNonConsiderer1,transmitter.pointCentral,inter[2],wall,screen);
                        coefficient *= transmission(murNonConsiderer1,murNonConsiderer2,inter[2],inter[1],wall,screen);
                        coefficient *= transmission(murNonConsiderer2,i,inter[1],inter[0],wall,screen);
                        coefficient *= transmission(i,-1,inter[0],receiver.pointCentral,wall,screen);
                        // On fait de meme mais avec les reflexions
                        coefficient *= coeffRef(transmitter.pointCentral,inter[2],wall[murNonConsiderer1]);
                        coefficient *= coeffRef(inter[2],inter[1],wall[murNonConsiderer2]);
                        coefficient *= coeffRef(inter[1],inter[0],wall[i]);
                        // On calcul la distance du dernier point image au recepteur
                        dist = distance(nouvelleImage, receiver.pointCentral);
                        // On fait la somme sur tous les rayons qui arrivent au recepteur
                        sum += pow(coefficient/(dist*pow(10,-2)),2);
                        if (receiver.central == 1){
                            line(transmitter.pointCentral.x/echelle,transmitter.pointCentral.y/echelle,inter[2].x/echelle,inter[2].y/echelle,couleur,screen);
                            line(inter[2].x/echelle,inter[2].y/echelle,inter[1].x/echelle,inter[1].y/echelle,couleur,screen);
                            line(inter[1].x/echelle,inter[1].y/echelle,inter[0].x/echelle,inter[0].y/echelle,couleur,screen);
                            line(inter[0].x/echelle,inter[0].y/echelle,receiver.pointCentral.x/echelle,receiver.pointCentral.y/echelle,couleur,screen);
                        }
                        coefficient = 1;
                    }
                }
            }
        }
    }
    return sum;
}

double deuxReflexion(float echelle, POINT lePoint, int murNonConsiderer, RECEIVER receiver, TRANSMITTER transmitter, WALL *wall, SDL_Surface *screen) {
/*
Dessine toutes les possibilites de faire 2 reflexions entre l'emetteur et le recepteur.
Fonctionne sur le meme principe que troisReflexion.
*/
    double coefficient = 1;
    float dist = 0;
    double sum = 0;
    Uint32 couleur = SDL_MapRGB(screen->format,0,255,0); // Lignes vertes pour deux reflexions
    POINT nouvelleImage;
    POINT inter[2];
    DROITE droiteInter[2];
    int i = 0;
    for (i=0;i<numberWall;i++){
        if (i==murNonConsiderer);
        else {
            nouvelleImage = image(lePoint,&wall[i]);
            droiteInter[0] = createDroite(nouvelleImage.x,nouvelleImage.y,receiver.pointCentral.x,receiver.pointCentral.y);
            inter[0] = intersection(droiteInter[0],wall[i].droite);
            inter[0].x = round(inter[0].x);
            inter[0].y = round(inter[0].y);
            droiteInter[1] = createDroite(inter[0].x,inter[0].y,lePoint.x,lePoint.y);
            inter[1] = intersection(droiteInter[1],wall[murNonConsiderer].droite);
            inter[1].x = round(inter[1].x);
            inter[1].y = round(inter[1].y);
            if(interExiste(&wall[murNonConsiderer],inter[1],transmitter.pointCentral,inter[0]) == 1) {
                if(interExiste(&wall[i],inter[0],inter[1],receiver.pointCentral) == 1){
                    coefficient *= transmission(-1, murNonConsiderer, transmitter.pointCentral,inter[1],wall,screen);
                    coefficient *= transmission(murNonConsiderer,i,inter[1],inter[0],wall,screen);
                    coefficient *= transmission(i,-1,inter[0],receiver.pointCentral,wall,screen);
                    coefficient *= coeffRef(transmitter.pointCentral,inter[1],wall[murNonConsiderer]);
                    coefficient *= coeffRef(inter[1],inter[0],wall[i]);
                    dist = distance(nouvelleImage,receiver.pointCentral);
                    sum += pow(coefficient/(dist*pow(10,-2)),2);
                    if (receiver.central) {
                        line(transmitter.pointCentral.x/echelle,transmitter.pointCentral.y/echelle,inter[1].x/echelle,inter[1].y/echelle,couleur,screen);
                        line(inter[1].x/echelle,inter[1].y/echelle,inter[0].x/echelle,inter[0].y/echelle,couleur,screen);
                        line(inter[0].x/echelle,inter[0].y/echelle,receiver.pointCentral.x/echelle,receiver.pointCentral.y/echelle,couleur,screen);
                    }
                    coefficient = 1;
                }
            }
            // On envoie le point de symetrie de la premiere image et la nouvelleImage calculee
            // dans troisReflexion
            sum += troisReflexion(echelle,lePoint,nouvelleImage,murNonConsiderer,i,receiver,transmitter,wall,screen);
        }
    }
    return sum;
}

POINT *premiereImage(TRANSMITTER transmitter,WALL *wall, POINT *listeDePoints){
/*
    Retourne un tableau dynamique de points. Ces points sont l'images de l'emetteur par rapport
    a chaque mur de la map consideree.
*/
    int i = 0;
    // On alloue un espace egale au nombre de mur.
    listeDePoints = malloc(numberWall*sizeof(POINT));
    // On cree un point correspondant a la position centrale de l'emetteur.
    POINT recu;
    for (i=0;i<numberWall;i++){
        recu = image(transmitter.pointCentral,&wall[i]);
        listeDePoints[i].x = recu.x;
        listeDePoints[i].y = recu.y;
    }
    return listeDePoints;
}

double reflexion(float echelle, RECEIVER receiver, TRANSMITTER transmitter, WALL *wall, SDL_Surface *screen){
/*
    Dessine toutes les possibilites de faire 1 reflexion entre l'emetteur et le recepteur.
    Fonctionne sur le meme principe que deuxReflexion.
*/
    double coefficient = 1;
    float dist = 0;
    double sum = 0;
    Uint32 couleur = SDL_MapRGB(screen->format,255,0,0); // Lignes rouges pour deux reflexions
    int i = 0;
    // On creer les points associes a la premiere image de l'emmeteur
    POINT *premierPointImage = NULL;
    premierPointImage = premiereImage(transmitter,wall,premierPointImage);
    POINT interMurDroite;
    DROITE droiteDePoints;
    droiteDePoints.x0 = receiver.pointCentral.x;
    droiteDePoints.y0 = receiver.pointCentral.y;
    for(i=0;i<numberWall;i++){
        droiteDePoints.x1 = premierPointImage[i].x;
        droiteDePoints.y1 = premierPointImage[i].y;
        interMurDroite = intersection(droiteDePoints,wall[i].droite);
        interMurDroite.x = round(interMurDroite.x);
        interMurDroite.y = round(interMurDroite.y);
        if (interExiste(&wall[i],interMurDroite, transmitter.pointCentral, receiver.pointCentral)==1) {;
            coefficient *= transmission(-1,i,transmitter.pointCentral,interMurDroite,wall,screen);
            coefficient *= transmission(i,-1,interMurDroite,receiver.pointCentral,wall,screen);
            coefficient *= coeffRef(transmitter.pointCentral,interMurDroite,wall[i]);
            dist = distance(premierPointImage[i],receiver.pointCentral);
            sum += pow(coefficient/(dist*pow(10,-2)),2);
            if (receiver.central == 1){
                line(transmitter.pointCentral.x/echelle,transmitter.pointCentral.y/echelle,interMurDroite.x/echelle,interMurDroite.y/echelle,couleur,screen);
                line(interMurDroite.x/echelle,interMurDroite.y/echelle,receiver.pointCentral.x/echelle,receiver.pointCentral.y/echelle,couleur,screen);
            }
            coefficient = 1;
        }
        sum += deuxReflexion(echelle, premierPointImage[i],i,receiver,transmitter,wall,screen);
    }
    return sum;
}

double onde(float echelle, RECEIVER receiver, TRANSMITTER transmitter, WALL *wall, SDL_Surface *screen){
/*
Onde directe arrivant de l'emetteur au recepteur.
*/
    double coefficient = 1;
    float dist = 0;
    double sum = 0;
    Uint32 couleur = SDL_MapRGB(screen->format,255,255,255); // Ligne blanche pour l'onde directe.
    coefficient = transmission(-1,-1,transmitter.pointCentral,receiver.pointCentral,wall,screen);
    dist = distance(transmitter.pointCentral,receiver.pointCentral);
    if (receiver.central == 1){
        // Seul le recepteur central peut avoir les lignes qui le suivent
        line(transmitter.pointCentral.x/echelle,transmitter.pointCentral.y/echelle,receiver.pointCentral.x/echelle,receiver.pointCentral.y/echelle,couleur,screen);
    }
    sum = pow(coefficient/(dist*pow(10,-2)),2);
    sum += reflexion(echelle,receiver,transmitter,wall,screen);
    return sum;
}
