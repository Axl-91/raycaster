#include "Objects.h"
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
    // amount of objects on a row
    int limit = 5;

    int x = (objNum % limit) * this->OFFSET;
    int y = (objNum / limit) * this->OFFSET;

    this->objX = x;
    this->objY = y;
    this->objRect.x = objX;
    this->objRect.y = objY;
}

void Objects::loadTexture() {
    SDL_Surface *surface = IMG_Load("objects.png");
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
    this->objRect = {objX + xOffset, objY, 1, this->SPRITE_SIZE};
}

void Objects::render(int x, int y, int width, int height) {
    SDL_Rect object = {x, y, width, height};
    SDL_RenderCopy(this->renderer, this->texture, &this->objRect, &object);
}

Objects::~Objects() { SDL_DestroyTexture(this->texture); }
