#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>


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


int puntos;
int vida = 3;
const char* Texto;


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
    {0,1,1,1,1,0,0,0,2,0,0,0,0,0,0,1,1,0,2,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,2,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {1,1,0,0,1,1,1,1,1,1,1,9,1,1,1,1,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,10},
    {0,2,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,7,3,3,3,3,3,8,0,0,0,0,0,0,0},
    {0,0,0,0,2,0,4,0,0,1,1,0,4,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,4,0,0,1,1,0,4,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,4,0,0,1,1,0,4,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,11,0,4,0,0},
    {3,3,3,3,3,3,5,0,0,5,1,0,6,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0} };

int pintarmapa(SDL_Rect personaje) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            rectFuente = { 64, 1152, 32, 32 };//piso
            rectDestino = { 32 * j, 32 * i, 32, 32 };
            rectPanel = { 32 * j, 32 * i, 32, 32 };
            switch (mapa[i][j])
            {
            case 0://PISO
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 1://Pared
                rectFuente = { 0, 1184, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 2://HUEC0
                Colision = SDL_HasIntersection(&personaje, &rectDestino);
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 64, 256, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                if (Colision) {
                    vida--;
                    
                }
                else {
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 64, 256, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    
                }
                break;
            case 3: //muro horizontal
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 0, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 4: //muro vertical
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 0, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 5://esquina inferior derecha
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 96, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 6://esquina inferior izquiera
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 64, 864, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 7://esquina superior derecha
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 64, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 8://esquina superior izquierda
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 96, 832, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 9: //llave
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
            case 10://tesoro
                Colision = SDL_HasIntersection(&personaje, &rectDestino);
                if (Colision && llaveObtenida==true) {
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
            case 11://oso
                Colision = SDL_HasIntersection(&personaje, &rectDestino);
                if (Colision) {
                    mapa[i][j] = 0;
                    puntos++;
                }
                else {
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 96, 4096, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);

                }
                break;
            default:
                break;
                return vida;
            }
        }
    }
}


void MostrarTexto(const char* Texto, SDL_Rect PosicionTexto) {
    TTF_Init();
    TTF_Font* Fuente = TTF_OpenFont("Fuente.ttf", 15);
    SDL_Color ColorTexto = { 50,50,200,255 };
    SDL_Surface* Surface = TTF_RenderText_Solid(Fuente, Texto, ColorTexto);
    SDL_Texture* Textura = SDL_CreateTextureFromSurface(renderer, Surface);
    SDL_FreeSurface(Surface);
    SDL_RenderCopy(renderer, Textura, NULL, &PosicionTexto);
}

bool existeColisionArriba(int posxPersonaje, int posyPersonaje) {
    int posyMuro;
    int posxMuro;
    bool colision;
    for (int fila = 0; fila < 20; fila++)
    {
        for (int columna = 0; columna < 20; columna++) {
            if (mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8) {
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
            if (mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8) {
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
            if (mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8) {
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
            if (mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8) {
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

    window = SDL_CreateWindow("SDL2 Moving Wizard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 768, 640, 0);
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

        stringstream TextoTex;////////////////////////////////////
        TextoTex << "Puntos: " << puntos;////////////////////////////////////
      
        
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
                    if (posy > 608 || existeColisionAbajo(posx, posy)) {
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
                    if (posx > 608 || existeColisionDerecha(posx, posy)) {
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
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        MostrarTexto(TextoTex.str().c_str(), { 620, 20, 150, 50 });
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