#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <sstream>
#include <windows.h>
#include <SDL_mixer.h>
#include <time.h>

using namespace std;

/*Declaración*/
const Uint8* estadoteclado;
int posx, posy, posxE, posyE;
bool quit;
SDL_Event event;
SDL_Window* window;
SDL_Window* ventanaDerrota;
SDL_Renderer* renderer;
SDL_Surface* image;
SDL_Texture* texturapersonaje;

SDL_Surface* fondo;
SDL_Texture* texturafondo;

SDL_Surface* enemigo;
SDL_Texture* texturaenemigo;

SDL_Surface* fondosPanel;
SDL_Texture* texturafondosPanel;

SDL_Rect rectFuente;
SDL_Rect rectDestino;
SDL_Rect rectPanel;

SDL_bool Colision;

Mix_Chunk* efectocofre;
Mix_Chunk* chocaEnemigo;
Mix_Chunk* chocaPared;
Mix_Chunk* morir;
Mix_Chunk* aparicion;
Mix_Chunk* key;
Mix_Chunk* muertedefinitiva;

Mix_Music* soundmonedas;
Mix_Music* calabera;

bool cofreAbierto = false;
bool llaveObtenida = false;

int monedas;

int vidas;
int c;
int i;

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
    {17,0,9,0,0,0,1,0,1,0,7,2,11,2,2,6,0,7,4,0},
    {0,0,0,0,10,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0},
    {2,2,4,0,5,2,6,0,5,2,8,0,7,2,2,2,4,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,5,2},
    {0,7,11,2,8,0,7,2,2,12,2,2,2,2,8,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,18,1,0,0,0,0,0,0,1,0,10,0}};

int recompensas[20];

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
                    if (llaveObtenida != true) {
                        Mix_PlayChannel(-1, key, 0);
                    }
                    llaveObtenida = true;
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 224, 4192, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectPanel = { 700,480,32,32 };
                    rectFuente = { 0, 32, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondosPanel, &rectFuente, &rectPanel);
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
                        rectPanel = { 700,480,32,32 };
                        rectFuente = { 0, 32, 32, 32 };
                        SDL_RenderCopy(renderer, texturafondosPanel, &rectFuente, &rectPanel);
                    }

                }
                break;
            case 17://cofre                                                                       
                Colision = SDL_HasIntersection(&personaje, &rectDestino);
                if (Colision && llaveObtenida == true && cofreAbierto==false) {
                    Mix_PlayChannel(-1, efectocofre, 0);
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
                    Mix_PlayMusic(calabera, 0);
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    rectFuente = { 192, 4192, 32, 32 };
                    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                    
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
                    Mix_PlayMusic(soundmonedas, 0);
                    monedas += 32;
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

void panel() {
    rectFuente = { 64, 3963, 32, 32 };//moneda
    rectPanel = { 690,302,32,32 };
    SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectPanel);
    rectFuente = { monedas , 640, 32, 32 };//contador moneda
    rectPanel = { 722,300,32,32 };
    SDL_RenderCopy(renderer, texturafondosPanel, &rectFuente, &rectPanel);

}

bool existeColisionArriba(int posxPersonaje, int posyPersonaje) {
    int posyMuro;
    int posxMuro;
    bool colision;
    for (int fila = 0; fila < 20; fila++)
    {
        for (int columna = 0; columna < 20; columna++) {
            if (mapa[fila][columna] == 1 || mapa[fila][columna] == 2 || mapa[fila][columna] == 3 || mapa[fila][columna] == 4 || mapa[fila][columna] == 5 || mapa[fila][columna] == 6 || mapa[fila][columna] == 7 || mapa[fila][columna] == 8
                || mapa[fila][columna] == 9 || mapa[fila][columna] == 10 || mapa[fila][columna] == 11 || mapa[fila][columna] == 12 || mapa[fila][columna] == 13 || mapa[fila][columna] == 14 || mapa[fila][columna] == 15) {
                posxMuro = columna * 32;
                posyMuro = (fila * 32) + 32;
                if (posxMuro == posxPersonaje && posyMuro == posyPersonaje) {
                    Mix_PlayChannel(-1, chocaPared, 0);
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
                || mapa[fila][columna] == 9 || mapa[fila][columna] == 10 || mapa[fila][columna] == 11 || mapa[fila][columna] == 12 || mapa[fila][columna] == 13 || mapa[fila][columna] == 14 || mapa[fila][columna] == 15) {
                posxMuro = columna * 32;
                posyMuro = (fila * 32) - 32;
                if (posxMuro == posxPersonaje && posyMuro == posyPersonaje) {
                    Mix_PlayChannel(-1, chocaPared, 0);
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
                || mapa[fila][columna] == 9 || mapa[fila][columna] == 10 || mapa[fila][columna] == 11 || mapa[fila][columna] == 12 || mapa[fila][columna] == 13 || mapa[fila][columna] == 14 || mapa[fila][columna] == 15) {
                posxMuro = (columna * 32) + 32;
                posyMuro = fila * 32;
                if (posxMuro == posxPersonaje && posyMuro == posyPersonaje) {
                    Mix_PlayChannel(-1, chocaPared, 0);
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
                || mapa[fila][columna] == 9 || mapa[fila][columna] == 10 || mapa[fila][columna] == 11 || mapa[fila][columna] == 12 || mapa[fila][columna] == 13 || mapa[fila][columna] == 14 || mapa[fila][columna] == 15) {
                posxMuro = (columna * 32) - 32;
                posyMuro = fila * 32;
                if (posxMuro == posxPersonaje && posyMuro == posyPersonaje) {
                    Mix_PlayChannel(-1, chocaPared, 0);
                    return true;
                }
            }
        }
    }
    return false;
}

void monedaRandom(int recompensaactual) {

    int posrandom = int(rand() % 400);
    int cont = 0;
    bool salir = false;
    for (int fila = 0; fila < 20; fila++) {
        for (int columna = 0; columna < 20; columna++) {
            if (cont == posrandom && mapa[fila][columna] == 0) {
                mapa[fila][columna] = 19;
                recompensas[recompensaactual] == posrandom;
                salir = true;
                break;
            }
            else {
                if (cont >= posrandom && mapa[fila][columna] == 0) {
                    mapa[fila][columna] = 19;
                    recompensas[recompensaactual] == cont;
                    salir = true;
                    break;
                }
            }
            cont++;
        }
        if (salir) {
            break;
        }
    }
}

void inicializar() {
    quit = false;
    posx = 608;
    posy = 608;
    posxE = 96;
    posyE = 416;
    vidas = 3;
    

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    /*Comando para reproducir la musica, solo necesita una muscia de fondo*/
    //Mix_PlayingMusic(musica, -1);
    estadoteclado = SDL_GetKeyboardState(NULL);

    window = SDL_CreateWindow("SDL2 Moving Wizard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    image = IMG_Load("arquera.png");
    texturapersonaje = SDL_CreateTextureFromSurface(renderer, image);

    enemigo = IMG_Load("slime.png");
    texturaenemigo = SDL_CreateTextureFromSurface(renderer, enemigo);

    fondosPanel = IMG_Load("fondosPanel.png");
    texturafondosPanel = SDL_CreateTextureFromSurface(renderer, fondosPanel);
    
    fondo = IMG_Load("fondos.png");
    texturafondo = SDL_CreateTextureFromSurface(renderer, fondo);
    SDL_FreeSurface(fondo);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Mix_Init(MIX_INIT_MP3);
    //if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { //Se inicializa la funcion para el audio
        //fprintf(stderr, "Error no se puede iniciar el sistema", SDL_GetError());
    //}
    //Mix_FreeChunk(Sonido);
    key = Mix_LoadWAV("Key.wav");  //Se atribulle el .wav (El wav se atribulle con Mix_LoadWAV)
    efectocofre = Mix_LoadWAV("Cofre.wav");
    chocaPared = Mix_LoadWAV("ChocaPared.wav");
    chocaEnemigo = Mix_LoadWAV("ChocaEnemigo.wav");
    aparicion = Mix_LoadWAV("Aparicion.wav");
    morir = Mix_LoadWAV("Morir.wav");
    muertedefinitiva = Mix_LoadWAV("MuerteDefinitiva.wav");
    soundmonedas = Mix_LoadMUS("Monedas.mp3");
    calabera = Mix_LoadMUS("Calabera.mp3");//Se atribulle el .mp3 (El mp3 se atribulle con Mix_LoadMUS) 

    srand(time(NULL));
    int recompensaActual = 0;
    for (int x = 0; x < 20; x++) {
        monedaRandom(recompensaActual);
        recompensaActual++;
    }

    Mix_PlayChannel(-1, aparicion, 0);
}

void leerEvento() {
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
}

void pantallaDerrota() {

    rectFuente = {32,0,640,640};
    rectDestino = {80, 0, 640, 640};

    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        while (SDL_PollEvent(&event) != NULL)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(-1);
                break;
            }
        }
        SDL_RenderCopy(renderer, texturafondosPanel, &rectFuente, &rectDestino);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        
    }
    SDL_DestroyWindow(ventanaDerrota);

    SDL_Delay(3000);
    
}

void escribirVidas() {
    rectFuente = { 0, 0 , 32, 32 };//Imagen del corazon

    if (vidas >= 3) {
        rectPanel = { 748,90,32,32 };
        SDL_RenderCopy(renderer, texturafondosPanel, &rectFuente, &rectPanel);
    }
    if (vidas >= 2) {
        rectPanel = { 700,90,32,32 };
        SDL_RenderCopy(renderer, texturafondosPanel, &rectFuente, &rectPanel);
        }
    if (vidas >= 1) {
        rectPanel = { 652,90,32,32 };
        SDL_RenderCopy(renderer, texturafondosPanel, &rectFuente, &rectPanel);
    }
    else {
        pantallaDerrota();
    }    
    
}

void existecolisionenemigo() {
    if (posx==posxE && posy == posyE) {
        
        vidas -= 1;
        posx = 608;
        posy = 608;
        Mix_PlayChannel(-1, chocaEnemigo, 0);
        if (c == 2) {
            Mix_PlayChannel(1, muertedefinitiva, 0);
        }
        c += 1;
        
    }
}

void tiempoYSprites() {
    Uint32 ticks = SDL_GetTicks();
    Uint32 sprite = (ticks / 100) % 5;
    SDL_Rect srcrect = { sprite * 32, 0, 32, 32 };
    SDL_Rect dstrect = { posx, posy, 32, 32 };
    SDL_Rect rectenemigo = { posxE, posyE, 32, 32 };

    SDL_RenderClear(renderer);
    pintarmapa(dstrect);
    panel();
    escribirVidas();
    existecolisionenemigo();
    SDL_RenderCopy(renderer, texturapersonaje, &srcrect, &dstrect);
    SDL_RenderCopy(renderer, texturaenemigo, &srcrect, &rectenemigo);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void finalizar() {
    SDL_DestroyTexture(texturapersonaje);
    SDL_FreeSurface(image);
    Mix_FreeChunk(efectocofre);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char** argv)
{

    inicializar();
    while (!quit)
    {
        tiempoYSprites();
        leerEvento();
    }
    finalizar();
    
    return 0;
}