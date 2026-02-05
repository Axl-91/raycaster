#include "GunSprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <unistd.h>

GunSprite::GunSprite() {}

void GunSprite::pollEvent(SDL_Event &event) {
    if (!this->shooting && event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_1:
            this->spriteRect.y = this->offset * 0;
            break;
        case SDLK_2:
            this->spriteRect.y = this->offset * 1;
            break;
        case SDLK_3:
            this->spriteRect.y = this->offset * 2;
            break;
        case SDLK_4:
            this->spriteRect.y = this->offset * 3;
            break;
        }
    }
}

void GunSprite::handleShooting() {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_SPACE] && !shooting) {
        shooting = true;
    }
}

void GunSprite::update() {
    if (this->shooting) {
        int frame = this->auxNum / this->offset;
        this->spriteRect.x = this->offset * frame;
        this->auxNum += ANIMATION_SPEED;
        if (frame > FRAMES_MAX) {
            this->auxNum = 0;
            this->spriteRect.x = 0;
            this->shooting = false;
        }
    }
}

void GunSprite::render(SDL_Renderer *renderer) {
    update();

    Sprite::render(renderer, GUN_POS_X, GUN_POS_Y, GUN_WIDTH, GUN_HEIGHT);
}
