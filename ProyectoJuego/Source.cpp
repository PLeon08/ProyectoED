#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <stdio.h>;
#include <SDL_image.h>
#include "mapa.hpp"

/*Declaración*/
const Uint8* estadoteclado;
int posx, posy;
bool quit;
SDL_Event event;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* image;
SDL_Texture* texture;

SDL_Surface* fondo;
SDL_Texture* texturafondo;

SDL_Rect rectFuente;
SDL_Rect rectDestino;

mapa* mapaNivel1;

/*Fin Declaración*/


void inicializar() {
    quit = false;
    posx = 0;
    posy = 0;
    mapaNivel1 = new mapa();

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    estadoteclado = SDL_GetKeyboardState(NULL);

    window = SDL_CreateWindow("SDL2 Moving Wizard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    image = IMG_Load("Blue_Mage.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);

    fondo = IMG_Load("fondos.png");
    texturafondo = SDL_CreateTextureFromSurface(renderer, fondo);
    //SDL_FreeSurface(fondo);
    SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
}

int main(int argc, char** argv)
{

    inicializar();
    while (!quit)
    {
        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / 100) % 5;
        SDL_Rect srcrect = { sprite * 32, 0, 32, 32 };
        SDL_Rect dstrect = { posx, posy, 32, 32 };


        while (SDL_PollEvent(&event) != NULL)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        if (estadoteclado[SDL_SCANCODE_RIGHT]) {
            posx += 1;
        }
        if (estadoteclado[SDL_SCANCODE_LEFT]) {
            posx -= 1;
        }
        if (estadoteclado[SDL_SCANCODE_UP]) {
            posy -= 1;
        }
        if (estadoteclado[SDL_SCANCODE_DOWN]) {
            posy += 1;
        }

        SDL_RenderClear(renderer);
        mapaNivel1->pintarmapa(renderer,texturafondo, rectFuente,rectDestino);
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
        SDL_RenderClear(renderer);


    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
