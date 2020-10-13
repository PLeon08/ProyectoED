#pragma once
#include <SDL.h>
#include "Source.cpp"

class mapa
{
private:
    int mapa1[20][20];

public:
    mapa();
    ~mapa();
    void pintarmapa(SDL_Renderer*, SDL_Texture*, SDL_Rect*&, SDL_Rect*&);
};
