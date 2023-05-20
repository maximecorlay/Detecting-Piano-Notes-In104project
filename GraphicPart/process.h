#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_fft_complex.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

// renvoie l'indice de l'élément du tableau dont la somme des 4 premières harmoniques est la plus grande
int argmax_double(double * tab,int largeur);

// renvoie l'indice du plus petit élément du tableau
int argmin(double * tab,int largeur);

// renvoie le n° de la note (sur le clavier) étant la plus proche de la fréquence donnée
int note(int frequence);


// main
int* partition();