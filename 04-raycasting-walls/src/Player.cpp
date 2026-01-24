#include "Player.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

Player::Player(float x, float y, Map &map) : posX(x), posY(y), map(map) {}

bool Player::canMove(float x, float y) {
    return this->map.getBlock(Vector(x + PLAYER_RADIUS, y)) == 0 &&
           this->map.getBlock(Vector(x - PLAYER_RADIUS, y)) == 0 &&
           this->map.getBlock(Vector(x, y + PLAYER_RADIUS)) == 0 &&
           this->map.getBlock(Vector(x, y - PLAYER_RADIUS)) == 0;
}

void Player::moveForward() {
    float newX = this->posX + MOVE_SPEED * cos(this->angle);
    float newY = this->posY + MOVE_SPEED * sin(this->angle);

    if (canMove(newX, this->posY))
        this->posX = newX;

    if (canMove(this->posX, newY))
        this->posY = newY;
}

void Player::moveBackward() {
    float newX = this->posX - MOVE_SPEED * cos(this->angle);
    float newY = this->posY - MOVE_SPEED * sin(this->angle);

    if (canMove(newX, this->posY))
        this->posX = newX;

    if (canMove(this->posX, newY))
        this->posY = newY;
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
    constexpr SDL_Color PLAYER = {0xFF, 0x00, 0x00, 0xFF};
    constexpr SDL_Color ANGLE = {0xFF, 0xFF, 0x00, 0xFF};

    float blockX = this->posX / (this->map.getAmountCols() * BLOCK_SIZE);
    float blockY = this->posY / (this->map.getAmountRows() * BLOCK_SIZE);

    // Translate the position unto the screen
    int x = blockX * SCREEN_WIDTH;
    int y = blockY * SCREEN_HEIGHT;

    SDL_Rect fillRect = {x - 2, y - 2, 5, 5};

    SDL_SetRenderDrawColor(renderer, PLAYER.r, PLAYER.b, PLAYER.b, PLAYER.a);
    SDL_RenderFillRect(renderer, &fillRect);

    const int LINE_LENGTH = 10;
    int endX = x + static_cast<int>(cos(angle) * LINE_LENGTH);
    int endY = y + static_cast<int>(sin(angle) * LINE_LENGTH);

    SDL_SetRenderDrawColor(renderer, ANGLE.r, ANGLE.g, ANGLE.b, ANGLE.a);
    SDL_RenderDrawLine(renderer, x, y, endX, endY);
}

Player::~Player() {}
