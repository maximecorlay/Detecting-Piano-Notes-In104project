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

int absolue(int a,int b){
    int m=0;
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

int argmax_harmonique(double * tab,int count){
    int m=0;
    for(int i=1;i<=count/9-1;i++){
        if(tab[i]+tab[2*i]+tab[3*i]+tab[4*i]+tab[5*i]+tab[6*i]+tab[7*i]+tab[8*i]+tab[9*i]>tab[m]+tab[2*m]+tab[3*m]+tab[4*m]+tab[5*m]+tab[6*m]+tab[7*m]+tab[8*m]+tab[9*m]){
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
    int largeur_echantillons_audio = 40000 ; 
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
    double * freq_max=malloc(2*compteur*sizeof(int));
    for(int k=0;k<=compteur-1;k++){
        double * temporaire = fft3((char*)fichiers[k],largeur_echantillons_audio,1);
        freq_max[k]=argmax_harmonique(temporaire,largeur_echantillons_audio);
        free(temporaire);
    }



    // ci-dessus durée d'une échantillon temporel (celle-ci doit être suffisamment courte sinon les notes se superposent)
    for(int numero_echantillon_audio=1;numero_echantillon_audio<nb_echantillons_audio;numero_echantillon_audio++){
        double * transformee = fft3("gamme.wav",largeur_echantillons_audio,numero_echantillon_audio);
        int freq_max_test = argmax_harmonique(transformee,largeur_echantillons_audio);
        printf("echantillon n° %d / %d (temps :%f s):",numero_echantillon_audio,nb_echantillons_audio,(double)numero_echantillon_audio/(double) freq_echantillonnage*(double)largeur_echantillons_audio);
        for(int i=0;i<=compteur-1;i++){
            if(absolue(freq_max[i],freq_max_test)<2){
                printf("%s ",fichiers[i]);
            }
        }
        printf("\n");
        free(transformee);
    }
    free(freq_max);
    return 0;
}


// gcc morceau_methode4.c -lm -lgsl -lgslcblas -lsndfile