#include "Player.h"
#include "Map.h"
#include "Raycaster.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

int toGrados(float radiales) {
    float anguloGrados = (radiales / PI) * 180;
    int anguloInt = round(anguloGrados);
    return anguloInt;
}

Player::Player() {}

void Player::setPos(float x, float y) {
    posX = x;
    posY = y;
}

void Player::setMap(Map &map) { mapPlayer = map; }

void Player::setRenderer(SDL_Renderer *renderer) { rendererPlayer = renderer; }

void Player::moveForward() {
    posX += this->MOVE_SPEED * cos(angle);
    posY += this->MOVE_SPEED * sin(angle);
}

void Player::moveBackward() {
    posX -= this->MOVE_SPEED * cos(angle);
    posY -= this->MOVE_SPEED * sin(angle);
}

void Player::rotateLeft() {
    angle -= this->ROTATION_SPEED;
    if (angle < 0) {
        angle += 2 * PI;
    }
}

void Player::rotateRight() {
    angle += this->ROTATION_SPEED;
    if (angle >= 2 * PI) {
        angle -= 2 * PI;
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

void Player::renderRaycaster() {
    Vector vectorPos(posX, posY);
    Raycaster raycaster(vectorPos, angle, mapPlayer);
    float anguloRay = angle - PI / 6;

    for (int pos = 0; pos < 320; ++pos) {
        if (anguloRay < 0) {
            anguloRay += 2 * PI;
        } else if (anguloRay > 2 * PI) {
            anguloRay -= 2 * PI;
        }
        raycaster.calculateRay(anguloRay);
        raycaster.renderWalls(pos);

        distBuffer[pos] = raycaster.getDistance();

        anguloRay += PI / 960;
    }
}

bool Player::objIsVisible(Vector &posObj) {
    /*Visibilidad hacia izq y derecha en radiales
    serian 30 grados pero agrego 5 mas para que
    se vea mas el sprite del objeto */
    float gVis = 35.0 / 180.0;
    float visible = PI * gVis;

    float dx = posObj.getX() - posX;
    float dy = posObj.getY() - posY;

    float anguloObj = atan2(dy, dx);
    float difAng = angle - anguloObj;

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

void Player::renderObjects() {
    int uno = 1;
    Vector posJugador = Vector(posX, posY);
    mapPlayer.sortObjByDist(posJugador);
    std::vector<mapObject> mapObjects = mapPlayer.getObjects();

    for (mapObject obj : mapObjects) {
        if (!objIsVisible(obj.position)) {
            continue;
        }
        float distanciaObj = posJugador.distance(obj.position);

        // Coordenadas en Y
        float sizeObj = (64 * 320) / distanciaObj;
        float yo = 100 - (sizeObj / 2);
        // Coordenadas en X
        float dx = posX - obj.position.getX();
        float dy = posY - obj.position.getY();

        float anguloObj = atan2(dy, dx) - angle;
        float xo = tan(anguloObj) * 277.1281;
        float x = 160.0f + xo - sizeObj / 2.0f;

        float anchura = sizeObj / 64;
        int yoInt = yo;
        int sizeObjInt = sizeObj;
        mapPlayer.setObjType(obj.type);

        for (int i = 0; i < 64; ++i) {
            for (int j = 0; j < anchura; ++j) {
                int z = round(x) + ((i)*anchura) + j;
                if (z < 0 || z > 320) {
                    continue;
                }

                if (distBuffer[z] > distanciaObj) {
                    mapPlayer.setColObject(i);
                    mapPlayer.renderObject(z, yoInt, uno, sizeObjInt);
                }
            }
        }
    }
}

void Player::render() {
    renderRaycaster();
    renderObjects();
}

Player::~Player() {}
