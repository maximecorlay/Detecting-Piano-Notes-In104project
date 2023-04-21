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

double max(double * tab,int n){
    double m = 0;
    for(int i=0;i<=n-1;i++){
        if(tab[i]>m){
            m=tab[i];
        }
    }
    return m;
}

double * transformee_fourier_methode1(char * titre,int deb,int fin)
{
    SNDFILE *fichier;
    FILE* fichier_bis;
    SF_INFO info_fichier;
    int nb_echantillons ;
    int freq_echantillonnage ;
    int nb_chaines;
    double * transfo_fourier=malloc(44100*sizeof(double));
    fichier = sf_open(titre, SFM_READ, &info_fichier);
    fichier_bis = fopen(titre,"rb");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier.\n");
    }
    else{
    nb_echantillons = info_fichier.frames ; 
    freq_echantillonnage = info_fichier.samplerate ;
    nb_chaines = info_fichier.channels ;
    short echantillon_audio[(fin-deb) * nb_chaines * freq_echantillonnage];
    fseek(fichier_bis, freq_echantillonnage * nb_chaines * deb, SEEK_CUR);
    fread(echantillon_audio, sizeof(short), (fin-deb) * nb_chaines * freq_echantillonnage, fichier_bis);
    fclose(fichier_bis);
    sf_close(fichier);
    int nb_valeurs_complexes = freq_echantillonnage / 2 + 1;
    gsl_fft_complex_wavetable *wavetable = gsl_fft_complex_wavetable_alloc(freq_echantillonnage);
    gsl_fft_complex_workspace *workspace = gsl_fft_complex_workspace_alloc(freq_echantillonnage);
    double tab[(fin-deb) * nb_chaines * freq_echantillonnage];
    for (int i = 0; i < (fin-deb) * nb_chaines * freq_echantillonnage; i++) {
        tab[2*i] = (double) echantillon_audio[i]; 
        tab[2*i+1] = 0.0;
    }
    gsl_fft_complex_forward(tab, 1, freq_echantillonnage, wavetable, workspace);
    for (int i = 0; i < nb_valeurs_complexes; i++) {
        double re = REAL(tab, i);
        double im = IMAG(tab, i);
        double mag = sqrt(re*re + im*im);
        transfo_fourier[i]=mag;
    }
    gsl_fft_complex_wavetable_free(wavetable);
    gsl_fft_complex_workspace_free(workspace);
    }
    return(transfo_fourier) ;
}

int main(){
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
    double * notes_freq=malloc(compteur*44100*sizeof(double));
    double temporaire[44100];
    for(int k=0;k<=compteur-1;k++){
        cblas_ccopy(44100,transformee_fourier_methode1((char*)fichiers[k],0,5),1.0,temporaire,1.0);
        for(int l=0;l<=44100-1;l++){
            notes_freq[44100*k+l]=temporaire[l];
        }
    }
    for(int k=0;k<=compteur-1;k++){
        m=max(notes_freq+44100*k,44100);
        for(int l=0;l<=44100-1;l++){
            notes_freq[44100*k+l]=notes_freq[44100*k+l]/m;
        }
    }
    char * titre_test = "gamme.wav";
    SNDFILE *fichier_test;
    SF_INFO info_test;
    int nb_echantillons_test ;
    int freq_echantillonnage_test ;
    int nb_chaines_test;
    int duree_test;
    fichier_test = sf_open(titre_test, SFM_READ, &info_test);
    nb_echantillons_test = info_test.frames ; 
    freq_echantillonnage_test = info_test.samplerate ;
    nb_chaines_test = info_test.channels ; 
    duree_test = nb_echantillons_test / freq_echantillonnage_test ; 
    printf("nb_echantillons_test : %d\n",nb_echantillons_test);
    printf("freq_echantillonnage_test : %d\n",freq_echantillonnage_test);
    printf("duree_test : %d secondes\n",duree_test);
    sf_close(fichier_test);
    for(int temps = 0;temps<=duree_test-1;temps++){
    double * transformee=transformee_fourier_methode1(titre_test,temps,temps+1);
    int m2=max(transformee,44100);
    for(int i=0;i<=44100-1;i++){
        transformee[i]=transformee[i]/m2;
    }
    double MSE[compteur];
    for(int j=0;j<=compteur-1;j++){
        MSE[j]=0.0;
        for(int k=0;k<=44100-1;k++){
            MSE[j]=MSE[j]+(notes_freq[44100*j+k]-transformee[k])*(notes_freq[44100*j+k]-transformee[k]);
        }
    }
    int arg = argmin(MSE,compteur);
   printf("temps : %d secondes : ",temps);
    printf("%s\n",fichiers[arg]);
    }
    printf("Méthode 1 : découpage temporel du fichier test.\n");
    return 0;
}

// gcc morceau_methode1.c -lm -lgsl -lgslcblas -lsndfile