#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

/*
Rappels de complation :
> GNU/Linux, MacOS : gcc base.c $(sdl2-config --cflags --libs) -o prog
*/
#define LARG 30;

/*
SDL_Rect noir2 = {(11/12)*LARG, 100, LARG, 600};
SDL_Rect noir5 = {(7/12)*LARG+2*LARG, 100, LARG, 600};
SDL_Rect noir7 = {(11/12)*LARG+3*LARG, 100, LARG, 600};
SDL_Rect noir10 = {(7/12)*LARG+5*LARG, 100, LARG, 600};
SDL_Rect noir12 = {(9/12)*LARG+6*LARG, 100, LARG, 600};
SDL_Rect noir14 = {(11/12)*LARG+7*LARG, 100, LARG, 600};
SDL_Rect noir17 = {(7/12)*LARG+9*LARG, 100, LARG, 600};
SDL_Rect noir19 = {(11/12)*LARG+10*LARG, 100, LARG, 600};
SDL_Rect noir22 = {(7/12)*LARG+12*LARG, 100, LARG, 600};
SDL_Rect noir24 = {(9/12)*LARG+13*LARG, 100, LARG, 600};
SDL_Rect noir26 = {(11/12)*LARG+14*LARG, 100, LARG, 600};
SDL_Rect noir29 = {(7/12)*LARG+16*LARG, 100, LARG, 600};
SDL_Rect noir31 = {(11/12)*LARG+17*LARG, 100, LARG, 600};
SDL_Rect noir34 = {(7/12)*LARG+19*LARG, 100, LARG, 600};
SDL_Rect noir36 = {(9/12)*LARG+20*LARG, 100, LARG, 600};
SDL_Rect noir38 = {(11/12)*LARG+21*LARG, 100, LARG, 600};
SDL_Rect noir41 = {(7/12)*LARG+23*LARG, 100, LARG, 600};
SDL_Rect noir43 = {(11/12)*LARG+24*LARG, 100, LARG, 600};
SDL_Rect noir46 = {(7/12)*LARG+26*LARG, 100, LARG, 600};
SDL_Rect noir48 = {(9/12)*LARG+27*LARG, 100, LARG, 600};
SDL_Rect noir50 = {(11/12)*LARG+28*LARG, 100, LARG, 600};
SDL_Rect noir53 = {(7/12)*LARG+30*LARG, 100, LARG, 600};
SDL_Rect noir55 = {(11/12)*LARG+31*LARG, 100, LARG, 600};
SDL_Rect noir58 = {(7/12)*LARG+33*LARG, 100, LARG, 600};
SDL_Rect noir60 = {(9/12)*LARG+34*LARG, 100, LARG, 600};
SDL_Rect noir62 = {(11/12)*LARG+35*LARG, 100, LARG, 600};
SDL_Rect noir65 = {(7/12)*LARG+37*LARG, 100, LARG, 600};
SDL_Rect noir67 = {(11/12)*LARG+38*LARG, 100, LARG, 600};
SDL_Rect noir70 = {(7/12)*LARG+40*LARG, 100, LARG, 600};
SDL_Rect noir72 = {(9/12)*LARG+41*LARG, 100, LARG, 600};
SDL_Rect noir74 = {(11/12)*LARG+42*LARG, 100, LARG, 600};
SDL_Rect noir77 = {(7/12)*LARG+44*LARG, 100, LARG, 600};
SDL_Rect noir79 = {(11/12)*LARG+45*LARG, 100, LARG, 600};
SDL_Rect noir82 = {(7/12)*LARG+47*LARG, 100, LARG, 600};
SDL_Rect noir84 = {(9/12)*LARG+48*LARG, 100, LARG, 600};
SDL_Rect noir86 = {(11/12)*LARG+49*LARG, 100, LARG, 600};
*/

int main(int argc, char** argv)
{

    // Lancement de la librairie SDL
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
    }

    // Création du piano
    
    SDL_Rect* piano = malloc(89*sizeof(SDL_Rect));

    for (int i = 1; i < 89; ++i)
    {
        piano[i].y = 100;
        piano[i].w = LARG;
    }

    piano[1].x = 0;
    piano[2].x = (1/2)*LARG;
    piano[3].x = LARG;
    piano[4].x = 2*LARG;
    piano[5].x = (1/2)*LARG+2*LARG;
    piano[6].x = 3*LARG;
    piano[7].x = (1/2)*LARG+3*LARG;
    piano[8].x = 4*LARG;
    piano[9].x = 5*LARG;
    piano[10].x = (1/2)*LARG+5*LARG;
    piano[11].x = 6*LARG;
    piano[12].x = (1/2)*LARG+6*LARG;
    piano[13].x = 7*LARG;
    piano[14].x = (1/2)*LARG+7*LARG;
    piano[15].x = 8*LARG;
    piano[16].x = 9*LARG;
    piano[17].x = (1/2)*LARG+9*LARG;
    piano[18].x = 10*LARG;
    piano[19].x = (1/2)*LARG+10*LARG;
    piano[20].x = 11*LARG;
    piano[21].x = 12*LARG;
    piano[22].x = (1/2)*LARG+12*LARG;
    piano[23].x = 13*LARG;
    piano[24].x = (1/2)*LARG+13*LARG;
    piano[25].x = 14*LARG;
    piano[26].x = (1/2)*LARG+14*LARG;
    piano[27].x = 15*LARG;
    piano[28].x = 16*LARG;
    piano[29].x = (1/2)*LARG+16*LARG;
    piano[30].x = 17*LARG;
    piano[31].x = (1/2)*LARG+17*LARG;
    piano[32].x = 18*LARG;
    piano[33].x = 19*LARG;
    piano[34].x = (1/2)*LARG+19*LARG;
    piano[35].x = 20*LARG;
    piano[36].x = (1/2)*LARG+20*LARG;
    piano[37].x = 21*LARG;
    piano[38].x = (1/2)*LARG+21*LARG;
    piano[39].x = 22*LARG;
    piano[40].x = 23*LARG;
    piano[41].x = (1/2)*LARG+23*LARG;
    piano[42].x = 24*LARG;
    piano[43].x = (1/2)*LARG+24*LARG;
    piano[44].x = 25*LARG;
    piano[45].x = 26*LARG;
    piano[46].x = (1/2)*LARG+26*LARG;
    piano[47].x = 27*LARG;
    piano[48].x = (1/2)*LARG+27*LARG;
    piano[49].x = 28*LARG;
    piano[50].x = (1/2)*LARG+28*LARG;
    piano[51].x = 29*LARG;
    piano[52].x = 30*LARG;
    piano[53].x = (1/2)*LARG+30*LARG;
    piano[54].x = 31*LARG;
    piano[55].x = (1/2)*LARG+31*LARG;
    piano[56].x = 32*LARG;
    piano[57].x = 33*LARG;
    piano[58].x = (1/2)*LARG+33*LARG;
    piano[59].x = 34*LARG;
    piano[60].x = (1/2)*LARG+34*LARG;
    piano[61].x = 35*LARG;
    piano[62].x = (1/2)*LARG+35*LARG;
    piano[63].x = 36*LARG;
    piano[64].x = 37*LARG;
    piano[65].x = (1/2)*LARG+37*LARG;
    piano[66].x = 38*LARG;
    piano[67].x = (1/2)*LARG+38*LARG;
    piano[68].x = 39*LARG;
    piano[69].x = 40*LARG;
    piano[70].x = (1/2)*LARG+40*LARG;
    piano[71].x = 41*LARG;
    piano[72].x = (1/2)*LARG+41*LARG;
    piano[73].x = 42*LARG;
    piano[74].x = (1/2)*LARG+42*LARG;
    piano[75].x = 43*LARG;
    piano[76].x = 44*LARG;
    piano[77].x = (1/2)*LARG+44*LARG;
    piano[78].x = 45*LARG;
    piano[79].x = (1/2)*LARG+45*LARG;
    piano[80].x = 46*LARG;
    piano[81].x = 47*LARG;
    piano[82].x = (1/2)*LARG+47*LARG;
    piano[83].x = 48*LARG;
    piano[84].x = (1/2)*LARG+48*LARG;
    piano[85].x = 49*LARG;
    piano[86].x = (1/2)*LARG+49*LARG;
    piano[87].x = 50*LARG;
    piano[88].x = 51*LARG;

    piano[1].h = 600;
    piano[2].h = 400;
    piano[3].h = 600;
    piano[4].h = 600;
    piano[5].h = 400;
    piano[6].h = 600;
    piano[7].h = 400;
    piano[8].h = 600;
    piano[9].h = 600;
    piano[10].h = 400;
    piano[11].h = 600;
    piano[12].h = 400;
    piano[13].h = 600;
    piano[14].h = 400;
    piano[15].h = 600;
    piano[16].h = 600;
    piano[17].h = 400;
    piano[18].h = 600;
    piano[19].h = 400;
    piano[20].h = 600;
    piano[21].h = 600;
    piano[22].h = 400;
    piano[23].h = 600;
    piano[24].h = 400;
    piano[25].h = 600;
    piano[26].h = 400;
    piano[27].h = 600;
    piano[28].h = 600;
    piano[29].h = 400;
    piano[30].h = 600;
    piano[31].h = 400;
    piano[32].h = 600;
    piano[33].h = 600;
    piano[34].h = 400;
    piano[35].h = 600;
    piano[36].h = 400;
    piano[37].h = 600;
    piano[38].h = 400;
    piano[39].h = 600;
    piano[40].h = 600;
    piano[41].h = 400;
    piano[42].h = 600;
    piano[43].h = 400;
    piano[44].h = 600;
    piano[45].h = 600;
    piano[46].h = 400;
    piano[47].h = 600;
    piano[48].h = 400;
    piano[49].h = 600;
    piano[50].h = 400;
    piano[51].h = 600;
    piano[52].h = 600;
    piano[53].h = 400;
    piano[54].h = 600;
    piano[55].h = 400;
    piano[56].h = 600;
    piano[57].h = 600;
    piano[58].h = 400;
    piano[59].h = 600;
    piano[60].h = 400;
    piano[61].h = 600;
    piano[62].h = 400;
    piano[63].h = 600;
    piano[64].h = 600;
    piano[65].h = 400;
    piano[66].h = 600;
    piano[67].h = 400;
    piano[68].h = 600;
    piano[69].h = 600;
    piano[70].h = 400;
    piano[71].h = 600;
    piano[72].h = 400;
    piano[73].h = 600;
    piano[74].h = 400;
    piano[75].h = 600;
    piano[76].h = 600;
    piano[77].h = 400;
    piano[78].h = 600;
    piano[79].h = 400;
    piano[80].h = 600;
    piano[81].h = 600;
    piano[82].h = 400;
    piano[83].h = 600;
    piano[84].h = 400;
    piano[85].h = 600;
    piano[86].h = 400;
    piano[87].h = 600;
    piano[88].h = 600;


    /*

    Récapitulatif sur les données du piano
    
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
*/
    

    // Création de la fenêtre et du rendu (on vérifie si chaque initialisation a bien fonctionné)

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

    // Création du clavier

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

     
    // Coloriage des touches noires 

    SDL_RenderFillRect(renderer, &piano[2]);
    SDL_RenderFillRect(renderer, &piano[5]);
    SDL_RenderFillRect(renderer, &piano[7]);
    SDL_RenderFillRect(renderer, &piano[10]);
    SDL_RenderFillRect(renderer, &piano[12]);
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

    // Destruction de la fenêtre et libération de la mémoire

    free(piano);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS; //return 0;
}

