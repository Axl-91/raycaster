#include "Guns.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <unistd.h>

Guns::Guns() {}

void Guns::setRenderer(SDL_Renderer *renderer) {
    winRenderer = renderer;
    loadTexture();
}

void Guns::loadTexture() {
    SDL_Surface *surface = IMG_Load("guns.png");
    if (!surface) {
        throw std::runtime_error("SDL surface error");
    }
    auto color = SDL_MapRGB(surface->format, 152, 0, 136);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    texture = SDL_CreateTextureFromSurface(winRenderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        throw std::runtime_error("SDL texture error");
    }
    SDL_FreeSurface(surface);
}

bool Guns::isShooting() { return this->shooting; }

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
        case SDLK_SPACE:
            this->shooting = true;
            break;
        }
    }
}

void Guns::render() {
    if (this->shooting) {
        int frame = this->auxNum / this->offset;
        this->srcGun.x = this->offset * frame;
        this->auxNum++;
        if (frame > FRAMES_MAX) {
            this->auxNum = 0;
            this->srcGun.x = 0;
            this->shooting = false;
        }
    }
    SDL_Rect gun = {96, 72, GUN_WIDTH, GUN_HEIGHT};
    SDL_RenderCopy(winRenderer, texture, &this->srcGun, &gun);
}

Guns::~Guns() { SDL_DestroyTexture(texture); }
