#include "HudSprite.h"
#include "../utils/Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

HudSprite::HudSprite() {}

void HudSprite::pollEvent(SDL_Event &event) {
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

void HudSprite::render(SDL_Renderer *renderer) const {
    SDL_Rect hud = {SCREEN_WIDTH - HUD_WIDTH, SCREEN_HEIGHT - HUD_HEIGHT,
                    HUD_WIDTH, HUD_HEIGHT};
    SDL_RenderCopy(renderer, this->texture, &this->srcHud, &hud);

    // Rendering gun section of the HUD
    SDL_Rect gunHud = {HUD_GUN_X, HUD_GUN_Y, HUD_GUN_WIDTH, HUD_GUN_HEIGHT};
    SDL_RenderCopy(renderer, this->texture, &this->srcGun, &gunHud);
}
