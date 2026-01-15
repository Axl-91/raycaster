#include "Guns.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <unistd.h>

Guns::Guns() {}

/**
 * Set renderer for the Gun Object and initialize texture
 * @param renderer SDL renderer to use for creating textures
 */
void Guns::setRenderer(SDL_Renderer *renderer) {
    winRenderer = renderer;
    loadTexture();
}

/**
 * Load gun sprite sheet texture from file
 * Loads "guns.png" and sets magenta (152, 0, 136) as transparent color
 * @throws std::runtime_error if surface or texture creation fails
 */
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

/**
 * @return true if gun is currently shooting, false otherwise
 */
bool Guns::getIsShooting() { return this->isShooting; }

/**
 * Handles keyboard input for gun selection and shooting
 * Keys 1-4 select different guns, Space initiates shooting
 */
void Guns::pollEvent(SDL_Event &event) {
    if (!this->isShooting && event.type == SDL_KEYDOWN) {
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
            this->isShooting = true;
            break;
        }
    }
}

/**
 * Render the gun sprite to the screen
 * Handles shooting animation by cycling through sprite frames
 */
void Guns::render() {
    if (this->isShooting) {
        int frame = this->auxNum / this->offset;
        this->srcGun.x = this->offset * frame;
        this->auxNum++;
        if (frame > FRAMES_MAX) {
            this->auxNum = 0;
            this->srcGun.x = 0;
            this->isShooting = false;
        }
    }
    SDL_Rect gun = {96, 72, GUN_WIDTH, GUN_HEIGHT};
    SDL_RenderCopy(winRenderer, texture, &this->srcGun, &gun);
}

Guns::~Guns() { SDL_DestroyTexture(texture); }
