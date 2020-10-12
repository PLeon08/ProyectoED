#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <stdio.h>;
#include <SDL_image.h>


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

SDL_Rect srcrectF;
SDL_Rect dstrectF;
SDL_Rect srcrectvaya;
SDL_Rect dscrectvaya;
/*Fin Declaración*/

/*0=suelo
  1=suelox2 
  2=hueco
  3=muro horizontal
  4=muro vertical
  5=esquina inferior derecha
  6=esquina inferior izquierda
  7=esquina superior derecha
  8=esquina superior izquierda
  9=llave
  10=tesoro
  */
int mapa[20][20] = {
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {1,1,0,0,1,1,1,1,1,1,1,9,1,1,1,1,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,10},
    {0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,7,3,3,3,3,3,8,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,4,0,0,1,1,0,4,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,4,0,0,1,1,0,4,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,4,0,0,1,1,0,4,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,11,0,4,0,0},
    {3,3,3,3,3,3,5,0,1,5,1,0,6,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0} };

void pintarmapa() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (mapa[i][j] == 0) {
                SDL_Rect srcrectF = { 64, 1152, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
            }
            if (mapa[i][j] == 1) {
                SDL_Rect srcrect = { 64, 1184, 32, 32 };
                SDL_Rect dstrect = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrect, &dstrect);
            }
            if (mapa[i][j] == 3) {
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 0, 864, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }
            if (mapa[i][j] == 4) { //muro vertical
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 0, 832, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }

            if (mapa[i][j] == 5) { //esquina inferior derecha
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 96, 864, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }
            if (mapa[i][j] == 6) { //esquina inferior izquiera
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 64, 864, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }
            if (mapa[i][j] == 7) { //esquina superior derecha
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 64, 832, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }
            if (mapa[i][j] == 8) { //esquina superior izquierda
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 96, 832, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }
            if (mapa[i][j] == 9) { //llave
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 224, 4192, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }
            if (mapa[i][j] == 10) { //tesoro
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 192, 3424, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }
            if (mapa[i][j] == 11) { //oso
                SDL_Rect srcrectF = { 65, 1153, 32, 32 };
                SDL_Rect dstrectF = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectF, &dstrectF);
                SDL_Rect srcrectvaya = { 96, 4096, 32, 32 };
                SDL_Rect dstrectvaya = { 32 * j, 32 * i, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &srcrectvaya, &dstrectvaya);
            }
        }
    }
}

void inicializar() {
    quit = false;
    posx = 0;
    posy = 0;


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
        pintarmapa();
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