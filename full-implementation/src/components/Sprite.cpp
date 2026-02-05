#include "Sprite.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

Sprite::Sprite() {}

void Sprite::loadTexture(SDL_Renderer *renderer, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        throw std::runtime_error("SDL surface error");
    }

    // Sets the color key for the surface to purple for transparency.
    const Uint32 PURPLE_COLOR = SDL_MapRGB(surface->format, 0x98, 0x00, 0x88);
    SDL_SetColorKey(surface, SDL_TRUE, PURPLE_COLOR);

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!this->texture) {
        throw std::runtime_error("SDL texture error");
    }
    SDL_FreeSurface(surface);
}

void Sprite::nextSprite() {
    this->spriteRect.x += BLOCK_SIZE;
    this->x = this->spriteRect.x;
}

void Sprite::render(SDL_Renderer *renderer, int x, int y, int width,
                    int height) const {
    SDL_Rect sprite = {x, y, width, height};
    SDL_RenderCopy(renderer, this->texture, &this->spriteRect, &sprite);
}

Sprite::~Sprite() { SDL_DestroyTexture(texture); }
