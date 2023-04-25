#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_fft_complex.h>
#include <cblas.h>
#include <stdint.h>
#include <sndfile.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

int puissance(int a,int b){
    int res = a;
    for(int i=1;i<=b;i++){
        res = res * a ;
    }
    return res ;
}

int absolue(int a,int b){
    int m=0;
    if(a<b){
        return (b-a) ;
    }
    return (a-b);
}

double absolue_double(double a,double b){
    double m=0;
    if(a<b){
        return (b-a) ;
    }
    return (a-b);
}

int argmin(double * tab,int count){
    int m=0;
    for(int i=1;i<=count-1;i++){
        if(tab[i]<tab[m]){
            m=i;
        }
    }
    return m;
}

int maxi(int a,int b){
    if(a<b){
        return b;
    }
    return a;
}

int argmax_harmonique(double * tab,int count){
    int m=1;
    for(int i=1;i<=maxi(count/8-1,1500);i++){
        if(tab[i]+tab[2*i]+tab[3*i]+tab[4*i]+tab[5*i]+tab[6*i]+tab[7*i]+tab[8*i]>tab[m]+tab[2*m]+tab[3*m]+tab[4*m]+tab[5*m]+tab[6*m]+tab[7*m]+tab[8*m]){
            m=i;
        }
    }
    return m;
}

int argmax(int * tab,int count){
    int m=0;
    for(int i=0;i<=count-1;i++){
        if(tab[i]>tab[m]){
            m=i;
        }
    }
    return m;
}

// cette fonction renvoie le n° de la touche de piano enfoncée en fonction de la fréquence 
// correspondance avec notes classiques : https://fr.wikipedia.org/wiki/Fr%C3%A9quences_des_touches_du_piano
int note(double frequence){
    double table[88] = {27.5,29.1353,30.8677,32.7032,34.6479,36.7081,38.8909,41.2035,43.6536,46.2493,48.9995,51.9131,55,58.2705,61.7354,65.4064,69.2957,73.4162,77.7817,82.4069,87.3071,92.4986,97.9989,103.826,110,116.541,123.471,130.813,138.591,146.832,155.563,164.814,174.614,184.997,195.998,207.652,220,233.082,246.942,261.626,277.183,293.665,311.127,329.628,349.228,369.994,391.995,415.305,440,466.164,493.883,523.251,554.365,587.33,622.254,659.255,698.456,739.989,783.991,830.609,880,932.328,987.767,1046.5,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760,1864.66,1975.53,2093,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520,3729.31,3951.07,4186.01};
    double ecarts[88];
    for(int i=0;i<=87;i++){
        ecarts[i]=absolue_double(frequence,table[i]);
    }
    return(argmin(ecarts,88)+1);
}

double * fft3(char * titre,int largeur_echantillons_audio,int numero_echantillon_audio)
{
    FILE * fichier_audio = fopen(titre, "rb");
    char entete[44]; // entete de fichier .wav
    fread(entete, 1, 44, fichier_audio);
    short audio_format = *((short *)(entete + 20));
    short echantillon_audio[largeur_echantillons_audio];
    fseek(fichier_audio, 2*(numero_echantillon_audio-1)*largeur_echantillons_audio, SEEK_CUR);
    int n = fread(echantillon_audio, sizeof(short), largeur_echantillons_audio, fichier_audio);
    fclose(fichier_audio);

    // Calculer la transformée de Fourier
    gsl_fft_complex_wavetable *wavetable = gsl_fft_complex_wavetable_alloc(largeur_echantillons_audio);
    gsl_fft_complex_workspace *workspace = gsl_fft_complex_workspace_alloc(largeur_echantillons_audio);


    // Copier les échantillons dans la fenêtre de calcul (int -> double)
    double echantillon_audio_double[2*largeur_echantillons_audio];
    for (int i = 0; i < largeur_echantillons_audio ; i++) {
        echantillon_audio_double[2*i] = (double) echantillon_audio[i]; 
        echantillon_audio_double[2*i+1] = 0.0;
    }

    // Appliquer la fenêtre de Hamming
    for (int j = 0; j < largeur_echantillons_audio ; j++) {
        echantillon_audio_double[2*j] *= 0.54 - 0.46 * cos(2.0 * 3.14159265 * (double)j / (double)(largeur_echantillons_audio - 1));
    }
    
   double * transfo_fourier=malloc(largeur_echantillons_audio*sizeof(double));

    gsl_fft_complex_forward(echantillon_audio_double, 1, largeur_echantillons_audio, wavetable, workspace);
    for (int i = 0; i < largeur_echantillons_audio ; i++) {
        double re = REAL(echantillon_audio_double, i);
        double im = IMAG(echantillon_audio_double, i);
        double mag = sqrt(re*re + im*im);
        transfo_fourier[i]=mag;
    }

    // Afficher les fréquences et amplitudes correspondantes
    for (int j = 0; j < largeur_echantillons_audio / 2; j++) {
        double frequence = (double)j * (double) 44100 / (double)largeur_echantillons_audio;
        if(frequence>2000||frequence<50){
            transfo_fourier[j]=0;
        }
        //printf("%f %f\n", frequence, transfo_fourier[j]);
    }

    // Libérer la mémoire
    gsl_fft_complex_wavetable_free(wavetable);
    gsl_fft_complex_workspace_free(workspace);

    return(transfo_fourier);
}

int main(){
    //(!) Paramètres à choisir
    int largeur_echantillons_audio = 44100 ; 
    // si trop grand les notes se superposent, si trop court l'incertitude spectrale devient trop grande
    char * titre_test = "gamme.wav"; // fichier wav retenu

    //(!) Paramètres qu'on ne choisit pas
    SNDFILE * fichier_test;
    SF_INFO info_test;
    int nb_echantillons_test ;
    int freq_echantillonnage_test ;
    int nb_chaines_test;
    double duree_test;
    fichier_test = sf_open(titre_test, SFM_READ, &info_test); 
    int freq_echantillonnage = 44100 ; 
    int nb_echantillons_elementaires_audio = info_test.frames  ;
    int nb_echantillons_audio = 4*nb_echantillons_elementaires_audio / largeur_echantillons_audio ;
    double largeur_temporelle_audio = largeur_echantillons_audio * freq_echantillonnage ; 
    duree_test=(double) nb_echantillons_elementaires_audio/(double) freq_echantillonnage;
    sf_close(fichier_test);

    // ci-dessus durée d'une échantillon temporel (celle-ci doit être suffisamment courte sinon les notes se superposent)
    printf("nb_echantillons_audio : %d\n",nb_echantillons_audio);
    for(int numero_echantillon_audio=1;numero_echantillon_audio<nb_echantillons_audio;numero_echantillon_audio++){
        double * transformee = fft3(titre_test,largeur_echantillons_audio,numero_echantillon_audio);
        int freq_max_test = argmax_harmonique(transformee,largeur_echantillons_audio);
        //printf("fréquence maximale : %f\n",(double)freq_max_test * (double) 44100 / (double)largeur_echantillons_audio);
        int octave[8];
        for(int i=0;i<=7;i++){
            if(freq_max_test*puissance(2,i)>largeur_echantillons_audio-1){
                octave[i]=0;
            }
            else{            
                octave[i]=transformee[freq_max_test*puissance(2,i)];
            }
        } 
        int freq_max_test_finale = freq_max_test*puissance(2,argmax(octave,8));
        //printf("Fréquence maxime sélectionnée : %f\n",freq_max_test_finale* (double) 44100 / (double)largeur_echantillons_audio);
        printf("Echantillon n°%d / %d (%fs/%fs)--> Note retenue (n° de touche du piano) : %d\n",numero_echantillon_audio,nb_echantillons_audio,((double) numero_echantillon_audio / (double) nb_echantillons_audio) * duree_test,duree_test,note(freq_max_test_finale));
        free(transformee);
    }
    return 0;
}


// gcc morceau_methode5.c -lm -lgsl -lgslcblas -lsndfile