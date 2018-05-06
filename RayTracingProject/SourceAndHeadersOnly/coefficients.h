#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <complex.h>

#ifndef COEFFICIENTS_H_INCLUDED
#define COEFFICIENTS_H_INCLUDED

// Definition de quelques constantes redondantes
#define pi 3.14159

const float mu_0 = 4*pi*pow(10,-7);
const float eps_0 = 8.854*pow(10, -12);
const float omega = (2.45*pow(10,9))*2*pi; //pulsation en rad/s, définie par la fréquence de travail
const float beta = (2.45*pow(10,9))*2*pi / (3*pow(10,8));

float complex z2(float eps_rel, float sigma);
float norme_coeff_reflexion(float theta_i, float eps_rel, float sigma, float epaisseur);
float norme_coeff_transmission(float theta_i, float eps_rel, float sigma, float epaisseur);
float complex gamma_m(float eps_rel, float sigma);

#endif // COEFFICIENTS_H_INCLUDED

