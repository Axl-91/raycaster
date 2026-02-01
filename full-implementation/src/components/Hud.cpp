#include "Hud.h"
#include "../utils/Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <stdexcept>

Hud::Hud() {}

void Hud::loadTexture(SDL_Renderer *renderer) {
    SDL_Surface *surface = IMG_Load("assets/hud.png");
    if (!surface) {
        throw std::runtime_error("SDL surface error on HUD");
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!this->texture) {
        throw std::runtime_error("SDL texture error on HUD");
    }
    SDL_FreeSurface(surface);
}

void Hud::pollEvent(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_1:
            this->srcGun.x = this->offsetGun * 0;
            break;
        case SDLK_2:
            this->srcGun.x = this->offsetGun * 1;
            break;
        case SDLK_3:
            this->srcGun.x = this->offsetGun * 2;
            break;
        case SDLK_4:
            this->srcGun.x = this->offsetGun * 3;
            break;
        }
    }
}

void Hud::renderHud(SDL_Renderer *renderer) const {
    SDL_Rect hud = {SCREEN_WIDTH - HUD_WIDTH, SCREEN_HEIGHT - HUD_HEIGHT,
                    HUD_WIDTH, HUD_HEIGHT};
    SDL_RenderCopy(renderer, this->texture, &this->srcHud, &hud);

    // Rendering gun section of the HUD
    // TODO: Fix magic numbers
    SDL_Rect gunHud = {255, 210, HUD_GUN_WIDTH, HUD_GUN_HEIGHT};
    SDL_RenderCopy(renderer, this->texture, &this->srcGun, &gunHud);
}

Hud::~Hud() { SDL_DestroyTexture(this->texture); }
