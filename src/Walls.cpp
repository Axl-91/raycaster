#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Walls.h"

Walls::Walls(){}

void Walls::setRenderer(SDL_Renderer* renderer){
    rendererWin = renderer;
    getTexture();
}

void Walls::getTexture(){
    SDL_Surface* surface = IMG_Load("walls.png");
    if (!surface) {
        throw std::exception(); //Crear excepcion SDL
    }

    textura = SDL_CreateTextureFromSurface(rendererWin, surface);
    if (!textura) {
        throw std::exception(); //Crear excepcion SDL
    }
    SDL_FreeSurface(surface);
}

void Walls::setSrc(int &posX, int &posY, int &largo, int &alto){
    src = {posX, posY, largo, alto};
}

void Walls::recortar(int &posX, int &posY, int &largo, int &alto){
    int x = srcX+posX;
    int y = srcY+posY;
    setSrc(x, y, largo, alto);
}

void Walls::setWall(int &num){
    int x = ((num%3) * 2) * 64;
    int y = (num/3) * 64;

    srcX = x;
    srcY = y;
    src.x = srcX;
    src.y = srcY;
}

void Walls::setDark(){
    srcX += offset;
    src.x += offset;
}

void Walls::render(int &posX, int &posY, int &largo, int &alto){
    SDL_Rect wall = {posX, posY, largo, alto};
    SDL_RenderCopy(rendererWin, textura, &src, &wall);
}

Walls::~Walls(){
    SDL_DestroyTexture(textura);
}
