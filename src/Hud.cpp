#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Hud.h"

Hud::Hud(){}

void Hud::setRenderer(SDL_Renderer* renderer){
    winRenderer = renderer;
    getTexture();
}

void Hud::getTexture(){
    SDL_Surface* surface = IMG_Load("hud.png");
    if (!surface) {
        throw std::exception(); //Crear excepcion SDL
    }

    textura = SDL_CreateTextureFromSurface(winRenderer, surface);
    if (!textura) {
        throw std::exception(); //Crear excepcion SDL
    }
    SDL_FreeSurface(surface);
}

void Hud::pollEvent(SDL_Event &evento){
    if (evento.type == SDL_KEYDOWN){
		switch(evento.key.keysym.sym){
            case SDLK_1:
                srcGun.x = offsetGun*0;
                break;
            case SDLK_2:
                srcGun.x = offsetGun*1;
                break;
            case SDLK_3:
                srcGun.x = offsetGun*2;
                break;
            case SDLK_4:
                srcGun.x = offsetGun*3;
                break;
		}
    }
}

void Hud::renderHud(int largoWin, int altoWin){
    SDL_Rect hud = {largoWin-HUDL, altoWin-HUDA, HUDL, HUDA};
    SDL_RenderCopy(winRenderer, textura, &srcHud, &hud);
}

void Hud::renderGun(int largoWin, int altoWin){
    SDL_Rect gun = {255, 210, HGUNL, HGUNA};
    SDL_RenderCopy(winRenderer, textura, &srcGun, &gun);
}

Hud::~Hud(){
    SDL_DestroyTexture(textura);
}
