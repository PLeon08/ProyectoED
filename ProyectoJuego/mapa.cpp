#include "mapa.hpp"



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


int mapaNivel1[20][20] = {
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {1,1,0,0,1,1,1,1,1,1,1,9,1,1,1,1,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,10},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,7,3,3,3,3,3,8,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,4,0,0,0,1,0,4,0,2,0,4,0,0,0},
    {1,1,1,1,1,0,4,0,0,0,1,0,4,0,0,0,4,0,0,0},
    {0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,4,0,0,0},
    {0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,11,4,0,0,0},
    {3,3,3,3,3,3,5,0,0,0,0,0,6,3,3,3,5,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

void mapa::pintarmapa(SDL_Renderer*renderer, SDL_Texture* texturafondo, SDL_Rect* &rectFuente, SDL_Rect* &rectDestino) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            SDL_Rect rectFuente = { 32, 0, 32, 32 };//piso
            SDL_Rect rectDestino = { 32 * j, 32 * i, 32, 32 };
            switch (mapaNivel1[i][j])
            {
            case 0://PISO
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 1://PISO2
                rectFuente = { 160, 0, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 2://HUEC0
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 64, 256, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
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
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 224, 4192, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 10://tesoro
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 192, 3424, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;
            case 11://oso
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                rectFuente = { 128, 896, 32, 32 };
                SDL_RenderCopy(renderer, texturafondo, &rectFuente, &rectDestino);
                break;

            default:
                break;
            }
        }
    }
}