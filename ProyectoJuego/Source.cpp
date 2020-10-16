#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <windows.h>

using namespace std;

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
SDL_Rect rectPanel;

SDL_bool Colision;


bool cofreAbierto = false;
bool llaveObtenida = false;

int monedas;
int puntos;
int vida = 3;
const char* Texto;
int cuenta_atras;

/*Fin Declaración*/







/*
  1= muro vertical
  2= muro horizontal
  3= muro esquina superior izq
  4= muro esquina superior der
  5= muro esquina inferior izq
  6= muro esquina inferior der
  7= muro final izquierda
  8= muro final derecha
  9= muro final abajo
  10= muro final arriba
  11= muro intersección izq, arriba, der
  12= muro intersección izq, abajo, der
  13= muro intersección izq, arriba, abajo
  14= muro intersección der, arriba, abajo
  15= muro intersección total
  16= llave
  17= cofre
  18= calavera

  */

int mapa[20][20] = {
    {0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,16},
    {0,10,0,7,2,2,2,11,2,4,0,10,0,14,2,2,8,0,1,0},
    {0,1,0,0,0,0,0,0,0,5,12,6,0,1,0,0,0,0,1,0},
    {0,5,2,2,2,2,2,4,0,0,1,0,0,1,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,5,2,2,6,0,3,6,0,7,4,0,9,0},
    {0,3,2,2,2,4,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
    {0,9,0,0,0,5,4,0,7,2,12,2,6,0,10,0,5,2,2,2},
    {0,0,0,10,0,0,1,0,0,18,1,0,0,0,1,0,0,0,0,0},
    {2,4,0,5,4,0,5,2,2,2,6,0,3,2,15,2,2,2,2,2},
    {0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
    {0,1,0,0,5,2,2,2,4,0,3,2,6,0,1,0,7,2,4,0},
    {0,5,8,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0},
    {0,0,0,0,7,2,4,0,14,2,6,0,10,0,5,12,2,2,6,0},
    {2,2,4,0,0,0,1,0,1,0,0,0,1,0,18,1,0,0,0,0},
    {17,0,9,0,19,0,1,0,1,0,7,2,11,2,2,6,0,7,4,0},
    {0,0,0,0,10,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0},
    {2,2,4,0,5,2,6,0,5,2,8,0,7,2,2,2,4,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,5,2},
    {0,7,11,2,8,0,7,2,2,12,2,2,2,2,8,0,1,0,0,0},
    {0,0,19,0,0,0,0,0,18,1,0,0,0,19,0,0,1,0,10,0}};


void pintarmapa(SDL_Rect personaje) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            rectFuente = { 64, 1152, 32, 32 };//piso
            rectDestino = { 32 * j, 32 * i, 32, 32 };
            switch (mapa[i][j])
            {
            case 0://Suelo
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 1://muro vertical
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 0, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 2://muro horizontal
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 0, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 4://muro esquina superior izq
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 96, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 3://muro esquina superior der
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 64, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 5://muro esquina inferior izq
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 64, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 6://muro esquina inferior der
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 96, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 8://muro final izquierda
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 128, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 7://muro final derecha
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 128, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 9://muro final abajo
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 32, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 10://muro final arriba
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 32, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 11://muro intersección izq, arriba, der
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 160, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 12://muro intersección izq, abajo, der
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 192, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 13://muro intersección izq, arriba, abajo
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 192, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 14://muro intersección der, arriba, abajo
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 160, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 15://muro intersección total
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 224, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 16://llave
                Colision = SDL_HasIntersection(&personaje, &rectDestino);
                if (Colision) {
                    llaveObtenida = true;
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 224, 4192, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectPanel = { 732,32,32,32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectPanel);
                }
                else {
                    if (llaveObtenida == false) {
                        SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                        rectFuente = { 224, 4192, 32, 32 };
                        SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    }
                    else
                    {
                        SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                        rectFuente = { 224, 4192, 32, 32 };
                        rectPanel = { 732,32,32,32 };
                        SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectPanel);
                    }
                }
                break;
            case 17://cofre                                                                       
                Colision = SDL_HasIntersection(&personaje, &rectDestino);
                if (Colision && llaveObtenida == true) {
                    cofreAbierto = true;
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 192, 3456, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                }
                else {
                    if (cofreAbierto == false) {
                        SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                        rectFuente = { 192, 3424, 32, 32 };
                        SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    }
                    else
                    {
                        SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                        rectFuente = { 192, 3456, 32, 32 };
                        SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    }
                }
                break;
            case 18://calavera
                Colision = SDL_HasIntersection(&personaje, &rectDestino);
                if (Colision) {
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 192, 4192, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                   // mapa[i][j] = 0;
                   // Sonido = 2;
                    vida--;
                }
                else {

                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 192, 4192, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                }
                break;
            case 19://recompensa Monedas
                Colision = SDL_HasIntersection(&personaje, &rectDestino);
                if (Colision) {
                    mapa[i][j] = 0;
                    //Sonido = 3;
                    monedas +=5;
                }
                else {

                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 64, 3963, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                }
                break;

            default:
                break;
            }
        }
    }
}



void MostrarTexto(const char* Texto, SDL_Rect PosicionTexto, int tamano) {
    TTF_Init();
    TTF_Font* Fuente = TTF_OpenFont("Fuente.ttf", tamano);
    SDL_Color ColorTexto = { 50,50,200,255 };
    SDL_Surface* Surface = TTF_RenderText_Solid(Fuente, Texto, ColorTexto);
    SDL_Texture* Textura = SDL_CreateTextureFromSurface(renderer, Surface);
    SDL_FreeSurface(Surface);
    SDL_RenderCopy(renderer, Textura, NULL, &PosicionTexto);
}





/*

void cronometro() {
    cuenta_atras = 60;
    stringstream TextoTex;
    TextoTex << "tiempo: " << cuenta_atras;
    while (cuenta_atras>0) {
        MostrarTexto(TextoTex.str().c_str(), { 620, 40, 150, 50 }, 10);
        cuenta_atras--;
        if (cuenta_atras == 0) {
            MostrarTexto("Ha muerto", { 300, 300, 150, 50 }, 25);
            quit = true;
        }
    }
}
*/


void panel() {
    stringstream TextoTex;
    rectFuente = { 64, 3963, 32, 32 };//moneda
    rectPanel = { 700,160,32,32 };
    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectPanel);
    TextoTex << ": " << monedas;
    MostrarTexto(TextoTex.str().c_str(), { 732, 160, 32, 32 }, 10);
    ////////////////////////////////////
    rectFuente = { 160, 3904, 32, 32 };//CAMBIAR POR CORAZON...ESTO ES UN EJEMPLO
    rectPanel = { 652,64,32,32 };
    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectPanel);
    rectPanel = { 700,64,32,32 };
    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectPanel);
    rectPanel = { 748,64,32,32 };
    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectPanel);
}



bool existeColisionArriba(int posxPersonaje, int posyPersonaje) {
    int posyMuro;
    int posxMuro;
    bool colision;
    for (int fila = 0; fila < 20; fila++)
    {
        for (int columna = 0; columna < 20; columna++) {
            if (mapa[fila][columna] == 1 || mapa[fila][columna] == 2 || mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8
                || mapa[fila][columna] == 9 || mapa[fila][columna] == 10 || mapa[fila][columna] == 11 || mapa[fila][columna] == 12 || mapa[fila][columna] == 13 || mapa[fila][columna] == 15 || mapa[fila][columna] == 15) {
                posxMuro = columna * 32;
                posyMuro = (fila * 32) + 32;
                if (posxMuro == posxPersonaje && posyMuro == posyPersonaje) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool existeColisionAbajo(int posxPersonaje, int posyPersonaje) {
    int posyMuro;
    int posxMuro;
    bool colision;
    for (int fila = 0; fila < 20; fila++)
    {
        for (int columna = 0; columna < 20; columna++) {
            if (mapa[fila][columna] == 1 || mapa[fila][columna] == 2 || mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8
                || mapa[fila][columna] == 9 || mapa[fila][columna] == 10 || mapa[fila][columna] == 11 || mapa[fila][columna] == 12 || mapa[fila][columna] == 13 || mapa[fila][columna] == 15 || mapa[fila][columna] == 15) {
                posxMuro = columna * 32;
                posyMuro = (fila * 32) - 32;
                if (posxMuro == posxPersonaje && posyMuro == posyPersonaje) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool existeColisionIzquierda(int posxPersonaje, int posyPersonaje) {
    int posyMuro;
    int posxMuro;
    bool colision;
    for (int fila = 0; fila < 20; fila++)
    {
        for (int columna = 0; columna < 20; columna++) {
            if (mapa[fila][columna] == 1 || mapa[fila][columna] == 2 || mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8
                || mapa[fila][columna] == 9 || mapa[fila][columna] == 10 || mapa[fila][columna] == 11 || mapa[fila][columna] == 12 || mapa[fila][columna] == 13 || mapa[fila][columna] == 15 || mapa[fila][columna] == 15) {
                posxMuro = (columna * 32) + 32;
                posyMuro = fila * 32;
                if (posxMuro == posxPersonaje && posyMuro == posyPersonaje) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool existeColisionDerecha(int posxPersonaje, int posyPersonaje) {
    int posyMuro;
    int posxMuro;
    bool colision;
    for (int fila = 0; fila < 20; fila++)
    {
        for (int columna = 0; columna < 20; columna++) {
            if (mapa[fila][columna] == 1 || mapa[fila][columna] == 2 || mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8
                || mapa[fila][columna] == 9 || mapa[fila][columna] == 10 || mapa[fila][columna] == 11 || mapa[fila][columna] == 12 || mapa[fila][columna] == 13 || mapa[fila][columna] == 15 || mapa[fila][columna] == 15) {
                posxMuro = (columna * 32) - 32;
                posyMuro = fila * 32;
                if (posxMuro == posxPersonaje && posyMuro == posyPersonaje) {
                    return true;
                }
            }
        }
    }
    return false;
}

void inicializar() {
    quit = false;
    posx = 0;
    posy = 0;


    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    estadoteclado = SDL_GetKeyboardState(NULL);

    window = SDL_CreateWindow("SDL2 Moving Wizard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    image = IMG_Load("arquera.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);

    fondo = IMG_Load("fondos.png");
    texturafondo = SDL_CreateTextureFromSurface(renderer, fondo);
    SDL_FreeSurface(fondo);
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
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_UP) {
                    if (posy <= 0 || existeColisionArriba(posx, posy)) {
                        break;
                    }
                    else {
                        posy -= 32;
                    }
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    if (posy > 576 || existeColisionAbajo(posx, posy)) {
                        break;
                    }
                    else {
                        posy += 32;
                    }
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    if (posx <= 0 || existeColisionIzquierda(posx, posy)) {
                        break;
                    }
                    else {
                        posx -= 32;
                    }
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    if (posx > 576 || existeColisionDerecha(posx, posy)) {
                        break;
                    }
                    else {
                        posx += 32;
                    }
                }
                break;
            }
        }

        SDL_RenderClear(renderer);
        pintarmapa(dstrect);
        panel();
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