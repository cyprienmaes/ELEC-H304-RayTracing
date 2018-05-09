#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <complex.h>
#include "point.h"

// Definition de quelques constantes redondantes
#define pi 3.14159

const float mu_0 = 4*pi*pow(10,-7);
const float eps_0 = 8.854*pow(10, -12);
const float omega = (2.45*pow(10,9))*2*pi; //pulsation en rad/s, définie par la fréquence de travail
const float beta = (2.45*pow(10,9))*2*pi / (3*pow(10,8));

float theta_i(float x0, float y0, float x1, float y1, char vertical){
// Calcul de l'angle d'incidence depuis le "point 0 emetteur" jusqu'au point 1 d'intersection avec le mur
    if( vertical ){
        return fabs( atan( (y1-y0)/(x1-x0) ) );
    }

    else {
        return fabs( atan( (x1-x0)/(y1-y0) ) );
    }
}

float complex z2(float eps_rel, float conduct){

    float  eps = eps_0*eps_rel;
    float  k = conduct/omega;

    return csqrt( mu_0 / (eps-(k*I)) );
}

float complex gamma_m(float eps_rel, float sigma){
    //Calcul de la constante de propagation (complexe) du mur
    // gamma_m = alpha + j*beta
    float a = omega*sqrt(mu_0*eps_0*eps_rel/2);
    float b = sqrt(1 + pow( sigma/(omega*eps_0*eps_rel), 2));

    float alpha = a * sqrt(b - 1);
    float beta  = a * sqrt(b + 1);

    return alpha + I * beta;
}

float theta_t_snell(float theta_i, float eps1, float eps2){
    // Calcul de l'angle de transmission par Snell, besoin pour calcul du coefficient de reflexion perpendiculaire

    return asin( sqrt(eps1/eps2)*sin(theta_i) );
}

float norme_coeff_reflexion(float theta_i, float eps_rel, float sigma, float epaisseur){

    float theta_t = theta_t_snell(theta_i, eps_0, eps_rel*eps_0); //calcul angle de transmission
    float s = epaisseur/cos(theta_t); // distance de propagation dans le mur (pour un "aller de rayon")

    float z1 = 377; //impedance caracteristique du vide
    float complex z3 = z2(eps_rel, sigma); //impedance caract du mur (COMPLEXE)


    float complex gamma = gamma_m(eps_rel, sigma); //calcul de la constante de propagation (COMPLEX)

    float complex coef_perp = (z3*cos(theta_i) - z1*cos(theta_t)) / (z3*cos(theta_i) + z1*cos(theta_t)); //coefficient de reflexion pour
                                                                                                     //polarisation perpendiculaire

    float complex partie_exp = cexp(-2*gamma*s) * cexp(I*beta*2*s*sin(theta_t)*sin(theta_i));  //Partie exponentielle de la formule du
                                                                                               //coef de reflexion du mur
    return cabs( coef_perp + (1-pow(coef_perp,2))*(coef_perp*partie_exp/(1-pow(coef_perp,2)*partie_exp))  );
}

float norme_coeff_transmission(float theta_i, float eps_rel, float sigma, float epaisseur){

    float theta_t = theta_t_snell(theta_i, eps_0, eps_rel*eps_0); //calcul angle de transmission
    float s = epaisseur/cos(theta_t); // distance de propagation dans le mur (pour un "aller de rayon")

    float z1 = 377; //impedance caracteristique du vide
    float complex z3 = z2(eps_rel, sigma); //impedance caract du mur (COMPLEXE)

    float complex gamma = gamma_m(eps_rel, sigma); //calcul de la constante de propagation (COMPLEX)

    float complex coef_perp = (z3*cos(theta_i) - z1*cos(theta_t)) / (z3*cos(theta_i) + z1*cos(theta_t)); //coefficient de reflexion pour
                                                                                                     //polarisation perpendiculaire

    float complex partie_exp = cexp(-2*gamma*s) * cexp(I*beta*2*s*sin(theta_t)*sin(theta_i));  //Partie exponentielle de la formule du
                                                                                            // du coef de reflexion du mur

    return cabs( ((1-pow(coef_perp,2))*cexp(-s*gamma)) / ((1-pow(coef_perp,2)*partie_exp)));
}
