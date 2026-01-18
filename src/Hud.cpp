#include "Hud.h"
#include "Constants.h"
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

void Hud::renderHud(SDL_Renderer *renderer) {
    SDL_Rect hud = {SCREEN_WIDTH - this->HUD_WIDTH,
                    SCREEN_HEIGHT - this->HUD_HEIGHT, this->HUD_WIDTH,
                    this->HUD_HEIGHT};
    SDL_RenderCopy(renderer, this->texture, &srcHud, &hud);

    // Rendering gun section of the HUD
    SDL_Rect gunHud = {255, 210, this->HUD_GUN_WIDTH,
                       this->HUD_GUN_HEIGHT}; // TODO: Fix magic numbers
    SDL_RenderCopy(renderer, this->texture, &srcGun, &gunHud);
}

Hud::~Hud() { SDL_DestroyTexture(this->texture); }
