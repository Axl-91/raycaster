#include "Player.h"
#include "Constants.h"
#include "Map.h"
#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Player::Player(float x, float y, Map &map) : posX(x), posY(y), map(map) {}

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

bool Player::objIsVisible(const Vector &posObj) const {
    // Horizontal visibility check (left / right of the player view).
    // The theoretical half-FOV is 30°, but we extend it to 35° so that
    // object sprites are not clipped at the screen edges.
    constexpr float DEG_TO_RAD = PI / 180.0f;
    constexpr float HALF_FOV = 35.0f * DEG_TO_RAD;

    float dx = posObj.getX() - this->posX;
    float dy = posObj.getY() - this->posY;

    float objectAngle = atan2(dy, dx);
    float delta = objectAngle - this->angle;

    // Normalization of deltaAngle to check if it's between -30° and 30°
    // from the players vision
    if (delta < -PI)
        delta += 2.0f * PI;
    if (delta > PI)
        delta -= 2.0f * PI;

    return delta > -HALF_FOV && delta < HALF_FOV;
}

Player::~Player() {}
