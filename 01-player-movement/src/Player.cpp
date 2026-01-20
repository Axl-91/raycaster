#include "Player.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

Player::Player(float x, float y) : posX(x), posY(y) {}

void Player::moveForward() {
    this->posX += MOVE_SPEED * cos(this->angle);
    this->posY += MOVE_SPEED * sin(this->angle);
}

void Player::moveBackward() {
    this->posX -= MOVE_SPEED * cos(this->angle);
    this->posY -= MOVE_SPEED * sin(this->angle);
}

void Player::rotateLeft() {
    this->angle -= ROTATION_SPEED;
    if (this->angle < 0) {
        this->angle += 2 * PI;
    }
}

void Player::rotateRight() {
    this->angle += ROTATION_SPEED;
    if (this->angle >= 2 * PI) {
        this->angle -= 2 * PI;
    }
}

void Player::handleMovement() {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) {
        moveForward();
    }
    if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) {
        moveBackward();
    }
    if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) {
        rotateLeft();
    }
    if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) {
        rotateRight();
    }
}

void Player::render(SDL_Renderer *renderer) {
    // Translate the position unto the screen
    int x = this->posX;
    int y = this->posY;

    SDL_Rect fillRect = {x - 2, y - 2, 5, 5};

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fillRect);

    const int LINE_LENGTH = 10;
    int endX = x + static_cast<int>(cos(angle) * LINE_LENGTH);
    int endY = y + static_cast<int>(sin(angle) * LINE_LENGTH);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawLine(renderer, x, y, endX, endY);
}

Player::~Player() {}
