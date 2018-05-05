#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <complex.h>

float complex z2(float eps_rel, float sigma, float f){
    // Calcul de Z2 pour les coefficients de reflexion/transmission

    float pi = 3.1416;
    float  mu_0 = 4*pi*pow(10,-7);
    float  eps_0 = 8.854*pow(10, -12);

    float  omega = 2*pi*f;
    float  eps = eps_0*eps_rel;
    float  k = sigma/omega;

    return csqrt( mu_0 / (eps-(k*I)) );
}

float norme_coeff_reflexion(float theta_i, float eps_rel, float sigma, float f){

    float pi = 3.1416;
    float theta_t = snell();
    float z1 = sqrt( 4*pi*pow(10,-7) / 8.854*pow(10, -12));
    float complex z2 = z2(eps_rel, sigma, f);
    float coef_perp = (z2*cos(theta_i) - z1*cos(theta_t)) / (z2*cos(theta_i) + z1*cos(theta_t));

    return cabs( coef_perp + (1-pow(coef_perp,2))*()  )
}
