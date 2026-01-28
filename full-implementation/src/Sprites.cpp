#include "Sprites.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

Sprites::Sprites() {}

void Sprites::loadTexture(SDL_Renderer *renderer, const char *path,
                          int spriteCols, bool transparent) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        throw std::runtime_error("SDL surface error on Object");
    }

    if (transparent) {
        auto color = SDL_MapRGB(surface->format, 0x98, 0x00, 0x88);
        SDL_SetColorKey(surface, SDL_TRUE, color);
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!this->texture) {
        throw std::runtime_error("SDL texture error on Object");
    }

    this->spriteCols = spriteCols;

    SDL_FreeSurface(surface);
}

void Sprites::setSprite(int spriteNum) {
    int col = spriteNum % this->spriteCols;
    int row = spriteNum / this->spriteCols;

    this->x = col * this->offset * (BLOCK_SIZE + this->separator);
    this->y = row * (BLOCK_SIZE + this->separator);

    this->spriteRect.x = this->x;
    this->spriteRect.y = this->y;
}

void Sprites::nextSprite() {
    this->spriteRect.x += BLOCK_SIZE;
    this->x = this->spriteRect.x;
}

void Sprites::selectSpriteCol(int xOffset) {
    this->spriteRect = {this->x + xOffset, this->y, 1, BLOCK_SIZE};
}

void Sprites::render(SDL_Renderer *renderer, int x, int y, int width,
                     int height) const {
    SDL_Rect sprite = {x, y, width, height};
    SDL_RenderCopy(renderer, this->texture, &this->spriteRect, &sprite);
}

Sprites::~Sprites() { SDL_DestroyTexture(texture); }
