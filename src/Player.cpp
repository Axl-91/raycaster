#include "Player.h"
#include "Constants.h"
#include "Map.h"
#include "Raycaster.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

namespace {
float normalizeAngle(float angle) {
    if (angle < 0) {
        angle += 2 * PI;
    } else if (angle > 2 * PI) {
        angle -= 2 * PI;
    }
    return angle;
}
} // namespace

Player::Player() {}

void Player::setPos(float x, float y) {
    this->posX = x;
    this->posY = y;
}

void Player::setMap(Map &map) { this->map = map; }

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

void Player::renderWalls() {
    Vector vectorPos(this->posX, this->posY);
    Raycaster raycaster(vectorPos, this->angle, this->map);

    // We need to start to create rays from the angle of the player minus 30°
    float angleRay = this->angle - OFFSET_RAYCASTER;

    for (int pos = 0; pos < SCREEN_WIDTH; ++pos) {
        angleRay = normalizeAngle(angleRay);

        raycaster.calculateRay(angleRay);
        raycaster.renderWalls(pos);

        this->distancesList[pos] = raycaster.getDistance();

        // Step is the amount neccesary to add so we can
        // fill the entire screen with the rays from -30° to +30°
        angleRay += STEP_RAYCASTER;
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

void Player::renderObjects() {
    int uno = 1;
    Vector posJugador = Vector(this->posX, this->posY);
    this->map.sortObjByDist(posJugador);
    std::vector<mapObject> mapObjects = this->map.getObjects();

    for (mapObject obj : mapObjects) {
        if (!objIsVisible(obj.position)) {
            continue;
        }
        float distanciaObj = posJugador.distance(obj.position);

        // Coordenadas en Y
        float sizeObj = (64 * 320) / distanciaObj;
        float yo = 100 - (sizeObj / 2);
        // Coordenadas en X
        float dx = this->posX - obj.position.getX();
        float dy = this->posY - obj.position.getY();

        float anguloObj = atan2(dy, dx) - this->angle;
        float xo = tan(anguloObj) * 277.1281;
        float x = 160.0f + xo - sizeObj / 2.0f;

        float anchura = sizeObj / 64;
        int yoInt = yo;
        int sizeObjInt = sizeObj;
        this->map.setObjType(obj.type);

        for (int i = 0; i < 64; ++i) {
            for (int j = 0; j < anchura; ++j) {
                int z = round(x) + ((i)*anchura) + j;
                if (z < 0 || z > 320) {
                    continue;
                }

                if (this->distancesList[z] > distanciaObj) {
                    this->map.setColObject(i);
                    this->map.renderObject(z, yoInt, uno, sizeObjInt);
                }
            }
        }
    }
}

void Player::render() {
    renderWalls();
    renderObjects();
}

Player::~Player() {}
