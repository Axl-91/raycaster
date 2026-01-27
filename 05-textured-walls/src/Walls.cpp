#include "Walls.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <stdexcept>

Walls::Walls() {}

void Walls::loadTexture(SDL_Renderer *renderer) {
    SDL_Surface *surface = IMG_Load("assets/walls.png");
    if (!surface) {
        throw std::runtime_error("SDL surface error on Walls");
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!this->texture) {
        throw std::runtime_error("SDL texture error on Walls");
    }
    SDL_FreeSurface(surface);
}

void Walls::setWall(int numWall, bool isDark) {
    int col = numWall % SPRITE_COLS;
    int row = numWall / SPRITE_COLS;

    this->wallX = col * OFFSET_WALL * BLOCK_SIZE;
    this->wallY = row * BLOCK_SIZE;

    this->wallRect.x = this->wallX;
    this->wallRect.y = this->wallY;

    if (isDark) {
        this->wallRect.x += BLOCK_SIZE;
        this->wallX = this->wallRect.x;
    }
}

void Walls::selectSpriteCol(int xOffset) {
    this->wallRect = {this->wallX + xOffset, this->wallY, 1, BLOCK_SIZE};
}

void Walls::render(SDL_Renderer *renderer, int x, int y, int width,
                   int height) const {
    SDL_Rect wall = {x, y, width, height};
    SDL_RenderCopy(renderer, this->texture, &this->wallRect, &wall);
}

Walls::~Walls() { SDL_DestroyTexture(texture); }
