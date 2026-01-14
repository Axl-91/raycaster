#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "Guns.h"

Guns::Guns(){}

void Guns::setRenderer(SDL_Renderer* renderer){
    winRenderer = renderer;
    getTexture();
}

void Guns::getTexture(){
    SDL_Surface* surface = IMG_Load("guns.png");
    if (!surface) {
        throw std::exception(); //Crear excepcion SDL
    }
    auto color = SDL_MapRGB(surface->format, 152, 0, 136);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    textura = SDL_CreateTextureFromSurface(winRenderer, surface);
    if (!textura) {
        throw std::exception(); //Crear excepcion SDL
    }
    SDL_FreeSurface(surface);
}

bool Guns::estaEnAccion(){
    return estaDisparando;
}

void Guns::pollEvent(SDL_Event &evento){
    if (estaDisparando){
    } else if (evento.type == SDL_KEYDOWN){
		switch(evento.key.keysym.sym){
            case SDLK_1:
                srcGun.y = offset*0;
                break;
            case SDLK_2:
                srcGun.y = offset*1;
                break;
            case SDLK_3:
                srcGun.y = offset*2;
                break;
            case SDLK_4:
                srcGun.y = offset*3;
                break;
            case SDLK_SPACE:
                estaDisparando = true;
                break;
		}
	}
}

void Guns::render(int largoWin, int altoWin){
    if (estaDisparando){
        int frame = numAuxiliar/offset;
        srcGun.x = offset*frame;
        numAuxiliar++;
        if (frame > 4){
            numAuxiliar = 0;
            srcGun.x = 0;
            estaDisparando = false;
        }
    }
    SDL_Rect gun = {96, 72, GUNL, GUNA};
    SDL_RenderCopy(winRenderer, textura, &srcGun, &gun);
}

Guns::~Guns(){
    SDL_DestroyTexture(textura);
}
