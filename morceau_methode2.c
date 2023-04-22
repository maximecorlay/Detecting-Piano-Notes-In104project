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


int argmin(double * tab,int count){
    int m=0;
    for(int i=1;i<=count-1;i++){
        if(tab[i]<tab[m]){
            m=i;
        }
    }
    return m;
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
        //printf("%f %f\n", frequence, transfo_fourier[j]);
    }

    // Libérer la mémoire
    gsl_fft_complex_wavetable_free(wavetable);
    gsl_fft_complex_workspace_free(workspace);

    return(transfo_fourier);
}

int main(){
    //(!) Paramètres à choisir
    int largeur_echantillons_audio = 20000 ; 
    // si trop grand les notes se superposent, si trop court l'incertitude spectrale devient trop grande

    //(!) Paramètres qu'on ne choisit pas
    int freq_echantillonnage = 44100 ; 
    int nb_echantillons_elementaires_audio = 1190700 ;
    int nb_echantillons_audio = nb_echantillons_elementaires_audio / largeur_echantillons_audio ;
    double largeur_temporelle_audio = largeur_echantillons_audio * freq_echantillonnage ; 

    DIR *dossier;
    struct dirent *ent;
    char* chemin_acces = "./banque_sons/"; 
    char fichiers[100][30];
    int compteur = 0;
    char str[100];
    double m ; 
    if ((dossier = opendir(chemin_acces)) != NULL) {
        while ((ent=readdir(dossier)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            strcpy(fichiers[compteur++],ent->d_name);
            if (compteur == 100)
                break;
        }
        closedir(dossier);
    } else {
        printf("Impossible d'ouvrir le dossier.\n");
    }
    for(int i=0;i<=compteur-1;i++){
        strcpy(str,"./banque_sons/");
        strcat(str,fichiers[i]);
        strcpy(fichiers[i],str);
    }
    printf("Fichiers dans %s :\n", chemin_acces);
    for (int i = 0; i < compteur; i++) {
        printf("%s\n", fichiers[i]);
    }
    double * notes_freq=malloc(compteur*largeur_echantillons_audio*sizeof(double));
    for(int k=0;k<=compteur-1;k++){
        double * temporaire = fft3((char*)fichiers[k],largeur_echantillons_audio,1);
        for(int l=0;l<=largeur_echantillons_audio-1;l++){
            notes_freq[largeur_echantillons_audio*k+l]=temporaire[l];
        }
        free(temporaire);
    }

    // ci-dessus durée d'une échantillon temporel (celle-ci doit être suffisamment courte sinon les notes se superposent)
    for(int numero_echantillon_audio=1;numero_echantillon_audio<nb_echantillons_audio;numero_echantillon_audio++){
        double * transformee = fft3("gamme.wav",largeur_echantillons_audio,numero_echantillon_audio);
        double MSE[compteur];
        for(int j=0;j<=compteur-1;j++){
        MSE[j]=0.0;
        for(int k=0;k<=largeur_echantillons_audio-1;k++){
            MSE[j]=MSE[j]+(notes_freq[largeur_echantillons_audio*j+k]-transformee[k])*(notes_freq[largeur_echantillons_audio*j+k]-transformee[k]);
        }
        }
         int arg = argmin(MSE,compteur);
         printf("n° : %d  : ",numero_echantillon_audio);
         printf("%s\n",fichiers[arg]);
         free(transformee);
    }
    return 0;
}


// gcc morceau_methode2.c -lm -lgsl -lgslcblas -lsndfile