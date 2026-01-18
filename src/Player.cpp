#include "Player.h"
#include "Constants.h"
#include "Map.h"
#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Player::Player(float x, float y, Map &map) : posX(x), posY(y), map(map) {}

Vector Player::getPos() const { return Vector(this->posX, this->posY); }

float Player::getAngle() const { return this->angle; }

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

bool Player::objIsVisible(Vector &posObj) {
    /*Visibilidad hacia izq y derecha en radiales
    serian 30 grados pero agrego 5 mas para que
    se vea mas el sprite del objeto */
    float gVis = 35.0 / 180.0;
    float visible = PI * gVis;

    float dx = posObj.getX() - this->posX;
    float dy = posObj.getY() - this->posY;

    float anguloObj = atan2(dy, dx);
    float difAng = this->angle - anguloObj;

    if (difAng < -PI) {
        difAng += 2 * PI;
    }
    if (difAng > PI) {
        difAng -= 2 * PI;
    }
    bool res = (difAng < visible);
    res &= (difAng > -visible);

    return res;
}

Player::~Player() {}
