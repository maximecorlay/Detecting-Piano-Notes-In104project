#include <SDL2/SDL.h>
#include "process.h"

// Dimensions de la fenêtre

#define FENETRE_LARGEUR 1000
#define FENETRE_HAUTEUR 800

// Dimensions d'une touche de piano
#define TOUCHE_LARGEUR (FENETRE_LARGEUR / 88)
#define TOUCHE_HAUTEUR 100

// Tableau des couleurs des touches blanches

SDL_Color whiteKeyColors[] = {
    {255, 255, 255, 255}, // Do
    {255, 255, 255, 255}, // Ré
    {255, 255, 255, 255}, // Mi
    {255, 255, 255, 255}, // Fa
    {255, 255, 255, 255}, // Sol
    {255, 255, 255, 255}, // La
    {255, 255, 255, 255}, // Si
};


// Tableau des couleurs des touches noires

SDL_Color blackKeyColors[] = {
    {0, 0, 0, 255},       // Do#
    {0, 0, 0, 255},       // Ré#
    {0, 0, 0, 255},       // Fa#
    {0, 0, 0, 255},       // Sol#
    {0, 0, 0, 255}        // La#
};



int main(int argc, char *argv[]) {
    int notes[88];
    int y[88];

    for (int i = 0; i < 88; ++i)
    {
        notes[i] = i;
        y[i] = -(i+1)*TOUCHE_HAUTEUR;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;


    // Initialisation de SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }


    // Création de la fenêtre

    window = SDL_CreateWindow("Clavier de piano", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, FENETRE_LARGEUR, FENETRE_HAUTEUR, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }


    // Création du renderer

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    
    /////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////


    int running2 = 1;

    while (running2) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running2 = 0;
            }

            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running2 = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        

        // Dessine les touches du clavier de piano

        for (int i = 0; i < 88; i++) {
          // Détermine la position et la couleur de la touche
            int x = i * TOUCHE_LARGEUR;
            SDL_Color color;
            int isBlackKey = 0;  // Variable pour déterminer si la touche est noire


            // Vérifie si la touche est noire
            switch (i % 12) {
                case 1: // Do#
                case 3: // Ré#
                case 6: // Fa#
                case 8: // Sol#
                case 10: // La#
                    isBlackKey = 1;
                    break;
                default:
                    break;
            }


            // Définit la couleur de la touche

            if (isBlackKey) {
                color = blackKeyColors[i % 5];
            } else {
                color = whiteKeyColors[i % 7];
            }


            // Dessine la touche

            SDL_Rect rect2 = {x, 700, TOUCHE_LARGEUR, TOUCHE_HAUTEUR};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect2);
        }

        for (int i = 1; i < 87; i++) {

            //Traçage des lignes de séparation entre les toucheS
            int x = i * TOUCHE_LARGEUR;
            SDL_Rect rect_ligne = {x-0.5,700,1,TOUCHE_HAUTEUR};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect_ligne);
        }

        SDL_Rect rect2 = {0, 0, 1800, 700};
        SDL_SetRenderDrawColor(renderer,200,200,200,0);
        SDL_RenderFillRect(renderer,&rect2);

        for(int k=0;k<88;k++){
            y[k]+=1;
            // Dessine le rectangle
            SDL_Rect rect = { notes[k]*TOUCHE_LARGEUR, y[k], TOUCHE_LARGEUR, TOUCHE_HAUTEUR };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderFillRect(renderer, &rect);
        }


        // Vérifie si le rectangle est entièrement sorti de la fenêtre

        if (y[87] > FENETRE_HAUTEUR) {
            running2 = 0;
        }


        // Affiche le rendu
        SDL_RenderPresent(renderer);
    }


    // Libération des ressources

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}