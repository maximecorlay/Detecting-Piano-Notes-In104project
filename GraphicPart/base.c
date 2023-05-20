#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

/*
Rappels de complation :
> GNU/Linux, MacOS : gcc base.c $(sdl2-config --cflags --libs) -o prog
*/
#define LARG = 30;

/*
SDL_Rectangle noir2 = {(11/12)*LARG, 100, LARG, 600};
SDL_Rectangle noir5 = {(7/12)*LARG+2*LARG, 100, LARG, 600};
SDL_Rectangle noir7 = {(11/12)*LARG+3*LARG, 100, LARG, 600};
SDL_Rectangle noir10 = {(7/12)*LARG+5*LARG, 100, LARG, 600};
SDL_Rectangle noir12 = {(9/12)*LARG+6*LARG, 100, LARG, 600};
SDL_Rectangle noir14 = {(11/12)*LARG+7*LARG, 100, LARG, 600};
SDL_Rectangle noir17 = {(7/12)*LARG+9*LARG, 100, LARG, 600};
SDL_Rectangle noir19 = {(11/12)*LARG+10*LARG, 100, LARG, 600};
SDL_Rectangle noir22 = {(7/12)*LARG+12*LARG, 100, LARG, 600};
SDL_Rectangle noir24 = {(9/12)*LARG+13*LARG, 100, LARG, 600};
SDL_Rectangle noir26 = {(11/12)*LARG+14*LARG, 100, LARG, 600};
SDL_Rectangle noir29 = {(7/12)*LARG+16*LARG, 100, LARG, 600};
SDL_Rectangle noir31 = {(11/12)*LARG+17*LARG, 100, LARG, 600};
SDL_Rectangle noir34 = {(7/12)*LARG+19*LARG, 100, LARG, 600};
SDL_Rectangle noir36 = {(9/12)*LARG+20*LARG, 100, LARG, 600};
SDL_Rectangle noir38 = {(11/12)*LARG+21*LARG, 100, LARG, 600};
SDL_Rectangle noir41 = {(7/12)*LARG+23*LARG, 100, LARG, 600};
SDL_Rectangle noir43 = {(11/12)*LARG+24*LARG, 100, LARG, 600};
SDL_Rectangle noir46 = {(7/12)*LARG+26*LARG, 100, LARG, 600};
SDL_Rectangle noir48 = {(9/12)*LARG+27*LARG, 100, LARG, 600};
SDL_Rectangle noir50 = {(11/12)*LARG+28*LARG, 100, LARG, 600};
SDL_Rectangle noir53 = {(7/12)*LARG+30*LARG, 100, LARG, 600};
SDL_Rectangle noir55 = {(11/12)*LARG+31*LARG, 100, LARG, 600};
SDL_Rectangle noir58 = {(7/12)*LARG+33*LARG, 100, LARG, 600};
SDL_Rectangle noir60 = {(9/12)*LARG+34*LARG, 100, LARG, 600};
SDL_Rectangle noir62 = {(11/12)*LARG+35*LARG, 100, LARG, 600};
SDL_Rectangle noir65 = {(7/12)*LARG+37*LARG, 100, LARG, 600};
SDL_Rectangle noir67 = {(11/12)*LARG+38*LARG, 100, LARG, 600};
SDL_Rectangle noir70 = {(7/12)*LARG+40*LARG, 100, LARG, 600};
SDL_Rectangle noir72 = {(9/12)*LARG+41*LARG, 100, LARG, 600};
SDL_Rectangle noir74 = {(11/12)*LARG+42*LARG, 100, LARG, 600};
SDL_Rectangle noir77 = {(7/12)*LARG+44*LARG, 100, LARG, 600};
SDL_Rectangle noir79 = {(11/12)*LARG+45*LARG, 100, LARG, 600};
SDL_Rectangle noir82 = {(7/12)*LARG+47*LARG, 100, LARG, 600};
SDL_Rectangle noir84 = {(9/12)*LARG+48*LARG, 100, LARG, 600};
SDL_Rectangle noir86 = {(11/12)*LARG+49*LARG, 100, LARG, 600};
*/

int main(int argc, char** argv)
{
    /*
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
    }
    */

    
    SDL_Rectangle* piano = malloc(88*sizeof(SDL_Rectangle));

    piano[1] = {0, 100, LARG, 600};
    piano[2] = {(1/2)*LARG, 100, LARG, 400};
    piano[3] = {LARG, 100, LARG, 600};
    piano[4] = {2*LARG, 100, LARG, 600};
    piano[5] = {(1/2)*LARG+2*LARG, 100, LARG, 400};
    piano[6] = {3*LARG, 100, LARG, 600};
    piano[7] = {(1/2)*LARG+3*LARG, 100, LARG, 400};
    piano[8] = {4*LARG, 100, LARG, 600};
    piano[9] = {5*LARG, 100, LARG, 600};
    piano[10] = {(1/2)*LARG+5*LARG, 100, LARG, 400};
    piano[11] = {6*LARG, 100, LARG, 600};
    piano[12] = {(1/2)*LARG+6*LARG, 100, LARG, 400};
    piano[13] = {7*LARG, 100, LARG, 600};
    piano[14] = {(1/2)*LARG+7*LARG, 100, LARG, 400};
    piano[15] = {8*LARG, 100, LARG, 600};
    piano[16] = {9*LARG, 100, LARG, 600};
    piano[17] = {(1/2)*LARG+9*LARG, 100, LARG, 400};
    piano[18] = {10*LARG, 100, LARG, 600};
    piano[19] = {(1/2)*LARG+10*LARG, 100, LARG, 400};
    piano[20] = {11*LARG, 100, LARG, 600};
    piano[21] = {12*LARG, 100, LARG, 600};
    piano[22] = {(1/2)*LARG+12*LARG, 100, LARG, 400};
    piano[23] = {13*LARG, 100, LARG, 600};
    piano[24] = {(1/2)*LARG+13*LARG, 100, LARG, 400};
    piano[25] = {14*LARG, 100, LARG, 600};
    piano[26] = {(1/2)*LARG+14*LARG, 100, LARG, 400};
    piano[27] = {15*LARG, 100, LARG, 600};
    piano[28] = {16*LARG, 100, LARG, 600};
    piano[29] = {(1/2)*LARG+16*LARG, 100, LARG, 400};
    piano[30] = {17*LARG, 100, LARG, 600};
    piano[31] = {(1/2)*LARG+17*LARG, 100, LARG, 400};
    piano[32] = {18*LARG, 100, LARG, 600};
    piano[33] = {19*LARG, 100, LARG, 600};
    piano[34] = {(1/2)*LARG+19*LARG, 100, LARG, 400};
    piano[35] = {20*LARG, 100, LARG, 600};
    piano[36] = {(1/2)*LARG+20*LARG, 100, LARG, 400};
    piano[37] = {21*LARG, 100, LARG, 600};
    piano[38] = {(1/2)*LARG+21*LARG, 100, LARG, 400};
    piano[39] = {22*LARG, 100, LARG, 600};
    piano[40] = {23*LARG, 100, LARG, 600};
    piano[41] = {(1/2)*LARG+23*LARG, 100, LARG, 400};
    piano[42] = {24*LARG, 100, LARG, 600};
    piano[43] = {(1/2)*LARG+24*LARG, 100, LARG, 400};
    piano[44] = {25*LARG, 100, LARG, 600};
    piano[45] = {26*LARG, 100, LARG, 600};
    piano[46] = {(1/2)*LARG+26*LARG, 100, LARG, 400};
    piano[47] = {27*LARG, 100, LARG, 600};
    piano[48] = {(1/2)*LARG+27*LARG, 100, LARG, 400};
    piano[49] = {28*LARG, 100, LARG, 600};
    piano[50] = {(1/2)*LARG+28*LARG, 100, LARG, 400};
    piano[51] = {29*LARG, 100, LARG, 600};
    piano[52] = {30*LARG, 100, LARG, 600};
    piano[53] = {(1/2)*LARG+30*LARG, 100, LARG, 400};
    piano[54] = {31*LARG, 100, LARG, 600};
    piano[55] = {(1/2)*LARG+31*LARG, 100, LARG, 400};
    piano[56] = {32*LARG, 100, LARG, 600};
    piano[57] = {33*LARG, 100, LARG, 600};
    piano[58] = {(1/2)*LARG+33*LARG, 100, LARG, 400};
    piano[59] = {34*LARG, 100, LARG, 600};
    piano[60] = {(1/2)*LARG+34*LARG, 100, LARG, 400};
    piano[61] = {35*LARG, 100, LARG, 600};
    piano[62] = {(1/2)*LARG+35*LARG, 100, LARG, 400};
    piano[63] = {36*LARG, 100, LARG, 600};
    piano[64] = {37*LARG, 100, LARG, 600};
    piano[65] = {(1/2)*LARG+37*LARG, 100, LARG, 400};
    piano[66] = {38*LARG, 100, LARG, 600};
    piano[67] = {(1/2)*LARG+38*LARG, 100, LARG, 400}
    piano[68] = {39*LARG, 100, LARG, 600};
    piano[69] = {40*LARG, 100, LARG, 600};
    piano[70] = {(1/2)*LARG+40*LARG, 100, LARG, 400};
    piano[71] = {41*LARG, 100, LARG, 600};
    piano[72] = {(1/2)*LARG+41*LARG, 100, LARG, 400};
    piano[73] = {42*LARG, 100, LARG, 600};
    piano[74] = {(1/2)*LARG+42*LARG, 100, LARG, 400};
    piano[75] = {43*LARG, 100, LARG, 600};
    piano[76] = {44*LARG, 100, LARG, 600};
    piano[77] = {(1/2)*LARG+44*LARG, 100, LARG, 400};
    piano[78] = {45*LARG, 100, LARG, 600};
    piano[79] = {(1/2)*LARG+45*LARG, 100, LARG, 400};
    piano[80] = {46*LARG, 100, LARG, 600};
    piano[81] = {47*LARG, 100, LARG, 600};
    piano[82] = {(1/2)*LARG+47*LARG, 100, LARG, 400};
    piano[83] = {48*LARG, 100, LARG, 600};
    piano[84] = {(1/2)*LARG+48*LARG, 100, LARG, 400};
    piano[85] = {49*LARG, 100, LARG, 600};
    piano[86] = {(1/2)*LARG+49*LARG, 100, LARG, 400};
    piano[87] = {50*LARG, 100, LARG, 600};
    piano[88] = {51*LARG, 100, LARG, 600};

    

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

    SDL_RenderFillRect(renderer, &piano[2]);
    SDL_RenderFillRect(renderer, &piano[5]);
    SDL_RenderFillRect(renderer, &piano[7]);
    SDL_RenderFillRect(renderer, &piano[10]);
    SDL_RenderFillRect(renderer, &ppiano[12]);
    SDL_RenderFillRect(renderer, &piano[14]);
    SDL_RenderFillRect(renderer, &piano[17]);
    SDL_RenderFillRect(renderer, &piano[19]);
    SDL_RenderFillRect(renderer, &piano[22]);
    SDL_RenderFillRect(renderer, &piano[24]);
    SDL_RenderFillRect(renderer, &piano[26]);
    SDL_RenderFillRect(renderer, &piano[29]);
    SDL_RenderFillRect(renderer, &piano[31]);
    SDL_RenderFillRect(renderer, &piano[34]);
    SDL_RenderFillRect(renderer, &piano[36]);
    SDL_RenderFillRect(renderer, &piano[38]);
    SDL_RenderFillRect(renderer, &piano[41]);
    SDL_RenderFillRect(renderer, &piano[43]);
    SDL_RenderFillRect(renderer, &piano[46]);
    SDL_RenderFillRect(renderer, &piano[48]);
    SDL_RenderFillRect(renderer, &piano[50]);
    SDL_RenderFillRect(renderer, &piano[53]);
    SDL_RenderFillRect(renderer, &piano[55]);
    SDL_RenderFillRect(renderer, &piano[58]);
    SDL_RenderFillRect(renderer, &piano[60]);
    SDL_RenderFillRect(renderer, &piano[62]);
    SDL_RenderFillRect(renderer, &piano[65]);
    SDL_RenderFillRect(renderer, &piano[67]);
    SDL_RenderFillRect(renderer, &piano[70]);
    SDL_RenderFillRect(renderer, &piano[72]);
    SDL_RenderFillRect(renderer, &piano[74]);
    SDL_RenderFillRect(renderer, &piano[77]);
    SDL_RenderFillRect(renderer, &piano[79]);
    SDL_RenderFillRect(renderer, &piano[82]);
    SDL_RenderFillRect(renderer, &piano[84]);
    SDL_RenderFillRect(renderer, &piano[86]);

    // Affichage de la fenêtre

    SDL_RenderPresent(renderer);

    SDL_Delay(10000);

    SDL_DestroyWindow(window);



    SDL_Quit();

    return EXIT_SUCCESS; //return 0;
}

