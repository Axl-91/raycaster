#include "Objects.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <unistd.h>

Objects::Objects() {}

void Objects::setRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
    loadTexture();
}

void Objects::setObject(int objNum) {
    int col = objNum % SPRITE_COLS;
    int row = objNum / SPRITE_COLS;

    this->objX = col * (BLOCK_SIZE + SPRITE_BORDER);
    this->objY = row * (BLOCK_SIZE + SPRITE_BORDER);

    this->objRect.x = objX;
    this->objRect.y = objY;
}

void Objects::loadTexture() {
    SDL_Surface *surface = IMG_Load("assets/objects.png");
    if (!surface) {
        throw std::runtime_error("SDL surface error on Object");
    }

    // I make the color purple from the sprite transparent
    auto color = SDL_MapRGB(surface->format, 152, 0, 136);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!this->texture) {
        throw std::runtime_error("SDL texture error on Object");
    }
    SDL_FreeSurface(surface);
}

void Objects::selectSpriteCol(int xOffset) {
    this->objRect = {this->objX + xOffset, this->objY, 1, BLOCK_SIZE};
}

void Objects::render(int x, int y, int width, int height) {
    SDL_Rect object = {x, y, width, height};
    SDL_RenderCopy(this->renderer, this->texture, &this->objRect, &object);
}

Objects::~Objects() { SDL_DestroyTexture(this->texture); }
