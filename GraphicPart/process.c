#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_fft_complex.h>

#include "process.h"

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

// renvoie l'indice de l'élément du tableau dont la somme des 4 premières harmoniques est la plus grande
int argmax_double(double * tab,int largeur){
    int argm=1;
    for(int cpt1=1;cpt1<=largeur/10-1;cpt1++){
        if(tab[cpt1]+tab[2*cpt1]+tab[3*cpt1]+tab[4*cpt1]>tab[argm]+tab[2*argm]+tab[3*argm]+tab[4*argm]){
            argm=cpt1;
        }
    }
    return argm;
}

// renvoie l'indice du plus petit élément du tableau
int argmin(double * tab,int largeur){
    int m=0;
    for(int cpt2=1;cpt2<=largeur-1;cpt2++){
        if(tab[cpt2]<tab[m]){
            m=cpt2;
        }
    }
    return m;
}

// renvoie le n° de la note (sur le clavier) étant la plus proche de la fréquence donnée
int note(int frequence){
    double table[88] = {27.5,29.1353,30.8677,32.7032,34.6479,36.7081,38.8909,41.2035,43.6536,46.2493,48.9995,51.9131,55,58.2705,61.7354,65.4064,69.2957,73.4162,77.7817,82.4069,87.3071,92.4986,97.9989,103.826,110,116.541,123.471,130.813,138.591,146.832,155.563,164.814,174.614,184.997,195.998,207.652,220,233.082,246.942,261.626,277.183,293.665,311.127,329.628,349.228,369.994,391.995,415.305,440,466.164,493.883,523.251,554.365,587.33,622.254,659.255,698.456,739.989,783.991,830.609,880,932.328,987.767,1046.5,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760,1864.66,1975.53,2093,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520,3729.31,3951.07,4186.01};
    double ecarts[88];
    for(int cpt3=0;cpt3<88;cpt3++){
        ecarts[cpt3]=((double) frequence-table[cpt3])*((double)frequence-table[cpt3]);
    }
    return(argmin(ecarts,88)+1);
}

// main

void partition(int* notes) {
    //(!) PARAMETRES A PRECISER A LA MACHINE
    int tau1 = 1024 ; 
    int tau2 = 4096 ;  
    int duree_audio = 27 ; 
    int freq_echantillonnage = 44100 ;
    FILE * fichier_audio = fopen("gamme.wav", "rb");
    // Nb : ce code fonctionne seulement avec .wav canal mono , 16 bits / échantillon
    // Vérifier ces informations sur VLC avant toute utilisation
    // En cas de besoin, convertir en ligne avec "convertio"

    
    int freq_maximale = 0 ;
    int note_jouee = 0 ; 
    ushort * enregistrement_audio_ushort = malloc(duree_audio*freq_echantillonnage*sizeof(ushort));
    double * enregistrement_audio_double = malloc(duree_audio*freq_echantillonnage*sizeof(double));
    fread(enregistrement_audio_ushort, sizeof(ushort), duree_audio*freq_echantillonnage, fichier_audio);
    for(int cpt1 = 0 ; cpt1<duree_audio*freq_echantillonnage ; cpt1++){
        enregistrement_audio_double [cpt1] = (double) enregistrement_audio_ushort [cpt1];
    }
    fclose(fichier_audio);
    // Calculer la transformée de Fourier
    double * echantillon_complexe_lu = malloc(2*tau2*sizeof(double));
    double * transfo_fourier = malloc(tau2*sizeof(double));
    gsl_fft_complex_wavetable * wavetable = gsl_fft_complex_wavetable_alloc(tau2);
    gsl_fft_complex_workspace * workspace = gsl_fft_complex_workspace_alloc(tau2);
    int nb_iterations = (duree_audio*freq_echantillonnage-tau2)/tau1;


    for(int cpt2 = 0;cpt2< tau1;cpt2++) {
    
        for (int cpt3 = 0; cpt3 < tau2 ; cpt3++) {
            REAL(echantillon_complexe_lu,cpt3) = enregistrement_audio_double[tau1*cpt2+cpt3];
            IMAG(echantillon_complexe_lu,cpt3) = 0.0;
        }

        /*// Appliquer la fenêtre de Hamming
        for (int j = 0; j < tau2 ; j++) {
            echantillon_complexe_lu[2*j] *= 0.54 - 0.46 * cos(2.0 * 3.14159265 * (double)j / (double)(tau2 - 1));
        }*/

        gsl_fft_complex_forward(echantillon_complexe_lu, 1, tau2, wavetable, workspace);
        for (int cpt4 = 0; cpt4 < tau2 ; cpt4++) {
            double re = REAL(echantillon_complexe_lu, cpt4);
            double im = IMAG(echantillon_complexe_lu, cpt4);
            double mag = sqrt(re*re + im*im);
            transfo_fourier[cpt4]=mag;
        }

        freq_maximale = argmax_double(transfo_fourier,tau2);
        note_jouee = note(freq_maximale*freq_echantillonnage/tau2);
        
        notes[cpt2] = note_jouee;
    }

    free(enregistrement_audio_ushort);
    free(enregistrement_audio_double);
    free(echantillon_complexe_lu);
    free(transfo_fourier);
    gsl_fft_complex_wavetable_free(wavetable);
    gsl_fft_complex_workspace_free(workspace);

}

// gcc morceau_methode5.c -lm -lgsl 