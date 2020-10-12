#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <stdio.h>;
#include <SDL_image.h>
#include <string>


int main(int argc, char** argv)
{
    int intento=10;
    int bblin;
    int i = 10;
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("SDL2 Moving Wizard",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    //Initialize variables
    SDL_Surface* arquera = IMG_Load("Arquera.png");
    SDL_Texture* textureArquera = SDL_CreateTextureFromSurface(renderer, arquera);
    SDL_Surface* mago = IMG_Load("Blue_Mage.png");
    SDL_Texture* textureMago = SDL_CreateTextureFromSurface(renderer, mago);


    SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
    SDL_RenderClear(renderer);
    int posxM = 32;
    int posyM = 64;
    int posxA = 64;
    int posyA = 64;
    int posxM = 32;
    int posyM = 64;
    int posxA = 64;
    int posxM = 32;
    int posyM = 64;
    int posxA = 64;
    int posyA = 64;
    int posyA = 64;
    int posSAnadora = 4;

    while (!quit)
    {
        /*Tiempo, GetTicks devuelve los milisegundos (1000=1seg) desde que comenzó el programa*/
        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / 100) % 5;
        SDL_Rect origenA = { sprite * 32, 0, 32, 32 };  
        /*X y Y indican las cordenadas donde comenzará la imagen recortada del spritesheet, 
        W y H indican las cordenadas donde terminará la imagen recortada del spritesheet.
        Funciona así, los ticks las milesimas que han pasado desde que empezó el programa, al hacer la división y el mod se obtiene un número del 1-4,
        así el sprite al muliplicarse por 32 estará recorriendo sprite por sprite, porque se movera de 1 en 1 los 32 pixeles en X y siempre comenzará 0 en Y, Y no se mueve
        porque es un vector, si fuera matriz se necesitaria una anidación*/
        SDL_Rect destinoA = { posxA, posyA, 32, 32 };

        SDL_Rect origenM = { sprite * 32, 0, 32, 32 };
        SDL_Rect destinoM = { posxM, posyM, 32, 32 };
        //SDL_Rect origenB = { sprite * 32, 0, 32, 64 };
        //SDL_Rect origenB = { 10, 10, 32, 64 };

        while (SDL_PollEvent(&event) != NULL)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    posxM += 32;
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    posxM -= 32;
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    posyM -= 32;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    posyM += 32;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    posxA += 3;
                }
                if (event.key.keysym.sym == SDLK_a) {
                    posxA -= 3;
                }
                if (event.key.keysym.sym == SDLK_w) {
                    posyA -= 3;
                }
                if (event.key.keysym.sym == SDLK_s) {
                    posyA += 3;
                }
                    
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textureArquera, &origenA, &destinoA);
        SDL_RenderCopy(renderer, textureMago, &origenM, &destinoM);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
        SDL_RenderClear(renderer);
    }

    SDL_DestroyTexture(textureArquera);
    SDL_FreeSurface(arquera);
    SDL_FreeSurface(mago);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}