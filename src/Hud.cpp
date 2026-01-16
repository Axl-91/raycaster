#include "Hud.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

Hud::Hud() {}

void Hud::setRenderer(SDL_Renderer *renderer) {
    winRenderer = renderer;
    loadTexture();
}

void Hud::loadTexture() {
    SDL_Surface *surface = IMG_Load("hud.png");
    if (!surface) {
        throw std::runtime_error("SDL surface error on HUD");
    }

    texture = SDL_CreateTextureFromSurface(winRenderer, surface);
    if (!texture) {
        throw std::runtime_error("SDL texture error on HUD");
    }
    SDL_FreeSurface(surface);
}

void Hud::pollEvent(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_1:
            srcGun.x = offsetGun * 0;
            break;
        case SDLK_2:
            srcGun.x = offsetGun * 1;
            break;
        case SDLK_3:
            srcGun.x = offsetGun * 2;
            break;
        case SDLK_4:
            srcGun.x = offsetGun * 3;
            break;
        }
    }
}

void Hud::renderHud(int winWidth, int winHeight) {
    SDL_Rect hud = {winWidth - this->HUD_WIDTH, winHeight - this->HUD_HEIGHT,
                    this->HUD_WIDTH, this->HUD_HEIGHT};
    SDL_RenderCopy(winRenderer, texture, &srcHud, &hud);
}

void Hud::renderGun(int winWidth, int winHeight) {
    // TODO: Fix magic numbers
    SDL_Rect gun = {255, 210, this->HUD_GUN_WIDTH, this->HUD_GUN_HEIGHT};
    SDL_RenderCopy(winRenderer, texture, &srcGun, &gun);
}

Hud::~Hud() { SDL_DestroyTexture(texture); }
