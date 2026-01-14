#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "Objects.h"

Objects::Objects(){}

void Objects::setRenderer(SDL_Renderer* renderer){
    rendererWin = renderer;
    getTexture();
}

void Objects::setObject(int num){
    int limite = 5;
    int x = (num % limite) * offset;
    int y = (num / limite) * offset;
    srcX = x;
    srcY = y;
    src.x = srcX;
    src.y = srcY;
}

void Objects::getTexture(){
    SDL_Surface* surface = IMG_Load("objects.png");
    if (!surface) {
        throw std::exception(); //Crear excepcion SDL
    }
    //Hago trasparente el color violeta del sprite
    auto color = SDL_MapRGB(surface->format, 152, 0, 136);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    textura = SDL_CreateTextureFromSurface(rendererWin, surface);
    if (!textura) {
        throw std::exception(); //Crear excepcion SDL
    }
    SDL_FreeSurface(surface);
}

void Objects::setSrc(int x, int y, int largo, int alto){
    src = {x, y, largo, alto};
}

void Objects::recortar(int x, int y, int largo, int alto){
    setSrc(srcX+x, srcY+y, largo, alto);
}

void Objects::render(int x, int y, int largo, int alto){
    SDL_Rect object = {x, y, largo, alto};
    SDL_RenderCopy(rendererWin, textura, &src, &object);
}

Objects::~Objects(){
    SDL_DestroyTexture(textura);
}
