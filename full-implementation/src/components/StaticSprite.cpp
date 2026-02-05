#include "StaticSprite.h"
#include <SDL2/SDL_image.h>

StaticSprite::StaticSprite() {}

void StaticSprite::loadTexture(SDL_Renderer *renderer, const char *path,
                               int spriteCols) {
    Sprite::loadTexture(renderer, path);
    this->spriteCols = spriteCols;
}

void StaticSprite::setSprite(int spriteNum) {
    int col = spriteNum % this->spriteCols;
    int row = spriteNum / this->spriteCols;

    this->x = col * this->variantCount * (BLOCK_SIZE + this->spacing);
    this->y = row * (BLOCK_SIZE + this->spacing);

    this->spriteRect.x = this->x;
    this->spriteRect.y = this->y;
}

void StaticSprite::selectSpriteCol(int xOffset) {
    this->spriteRect = {this->x + xOffset, this->y, 1, BLOCK_SIZE};
}
