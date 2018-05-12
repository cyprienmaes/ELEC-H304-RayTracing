#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <complex.h>
#include "point.h"

#ifndef COEFFICIENTS_H_INCLUDED
#define COEFFICIENTS_H_INCLUDED

// Definition de quelques constantes redondantes
#define pi 3.14159

double theta_i(float x0, float y0, float x1, float y1, char vertical);
float complex z2(float eps_rel, float sigma);
float complex gamma_m(float eps_rel, float sigma);
double theta_t_snell(double theta_i, float eps1, float eps2);
double norme_coeff_reflexion(double theta_i, float eps_rel, float sigma, float epaisseur);
double norme_coeff_transmission(double theta_i, float eps_rel, float sigma, float epaisseur);

#endif // COEFFICIENTS_H_INCLUDED

