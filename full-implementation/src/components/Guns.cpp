#include "Guns.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <stdexcept>
#include <unistd.h>

Guns::Guns() {}

void Guns::loadTextures(SDL_Renderer *renderer) {
    SDL_Surface *surface = IMG_Load("assets/guns.png");
    if (!surface) {
        throw std::runtime_error(std::string("Failed to load guns.png: ") +
                                 IMG_GetError());
    }

    auto color = SDL_MapRGB(surface->format, 152, 0, 136);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!this->texture) {
        SDL_FreeSurface(surface);
        throw std::runtime_error(std::string("Failed to create gun texture: ") +
                                 SDL_GetError());
    }
    SDL_FreeSurface(surface);
}

void Guns::pollEvent(SDL_Event &event) {
    if (!this->shooting && event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_1:
            this->srcGun.y = this->offset * 0;
            break;
        case SDLK_2:
            this->srcGun.y = this->offset * 1;
            break;
        case SDLK_3:
            this->srcGun.y = this->offset * 2;
            break;
        case SDLK_4:
            this->srcGun.y = this->offset * 3;
            break;
        }
    }
}

void Guns::handleShooting() {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_SPACE] && !shooting) {
        shooting = true;
    }
}

void Guns::update() {
    if (this->shooting) {
        int frame = this->auxNum / this->offset;
        this->srcGun.x = this->offset * frame;
        this->auxNum += ANIMATION_SPEED;
        if (frame > FRAMES_MAX) {
            this->auxNum = 0;
            this->srcGun.x = 0;
            this->shooting = false;
        }
    }
}

void Guns::render(SDL_Renderer *renderer) {
    update();

    SDL_Rect gun = {GUN_POS_X, GUN_POS_Y, GUN_WIDTH, GUN_HEIGHT};
    SDL_RenderCopy(renderer, this->texture, &this->srcGun, &gun);
}

Guns::~Guns() { SDL_DestroyTexture(this->texture); }
