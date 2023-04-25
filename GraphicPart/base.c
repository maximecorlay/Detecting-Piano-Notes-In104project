#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

/*
Rappels de complation :
> GNU/Linux, MacOS : gcc base.c $(sdl2-config --cflags --libs) -o prog
*/


int main(int argc, char** argv)
{
    /*
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
    }
    */

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    window = SDL_CreateWindow("Interface Piano", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 800, 0);
    
    if (window == NULL)
    {
        SDL_Log("ERREUR : Creation fenetre échouée > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

     if (renderer == NULL)
    {
        SDL_Log("ERREUR : Creation rendu échouée > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_Rect rectangle = {0, 100, 1600, 600};
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(renderer, 0, 100, 1600, 100);
    SDL_RenderDrawLine(renderer, 0, 700, 1600, 700);

    for (int i = 0; i < 53; ++i)
    {
        SDL_RenderDrawLine(renderer, i*30, 100, i*30, 700);
    }

    

    /*
    b = -30;


    for (int i = 0; i < 12; ++i)
    {
        b += 50;

        if (i%2 == 0)
        {
            
            SDL_RenderFillRect(renderer, rectangle)
        }
    }
    */

    // Affichage de la fenêtre

    SDL_RenderPresent(renderer);

    SDL_Delay(10000);

    SDL_DestroyWindow(window);



    SDL_Quit();

    return EXIT_SUCCESS; //return 0;
}

