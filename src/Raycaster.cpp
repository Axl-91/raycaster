#include "Raycaster.h"
#include "Constants.h"
#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int toGradosRay(float radiales) {
    float angulo = (radiales / PI) * 180;
    int anguloInt = round(angulo);
    return anguloInt;
}

Raycaster::Raycaster(Vector &playerPos, float playerAngle, Map &map)
    : playerPos(playerPos), playerAngle(playerAngle), map(map) {}

void Raycaster::calculateRay(float rayAngle) {
    this->rayAngle = rayAngle;
    calculateHorizontalRay();
    calculateVerticalRay();
    calculateFinalRay();
}

void Raycaster::calculateHorizontalRay() {
    if (fabs(sin(rayAngle)) < EPSILON) {
        this->hRayDist = std::numeric_limits<float>::infinity();
        return;
    }

    Vector raySum;
    bool hitWall = false;
    float hTang = -1 / tan(rayAngle);

    if (rayAngle > PI) {
        int blockPos = playerPos.getY() / BLOCK_SIZE;

        // Initial ray position
        float ry = blockPos * BLOCK_SIZE - EPSILON;
        float rx = ((playerPos.getY() - ry) * hTang) + playerPos.getX();

        this->horizontalRay = Vector(rx, ry);

        float yo = -BLOCK_SIZE;
        float xo = -yo * hTang;

        raySum = Vector(xo, yo);
    } else {
        int blockPos = playerPos.getY() / BLOCK_SIZE;

        // Initial ray position
        float ry = blockPos * BLOCK_SIZE + BLOCK_SIZE;
        float rx = (playerPos.getY() - ry) * hTang + playerPos.getX();

        this->horizontalRay = Vector(rx, ry);

        float yo = BLOCK_SIZE;
        float xo = -yo * hTang;

        raySum = Vector(xo, yo);
    }

    while (!hitWall) {
        this->hRayDist = playerPos.distance(this->horizontalRay);

        if (!map.isInsideMap(this->horizontalRay)) {
            break;
        }
        if (map.getBlock(this->horizontalRay) == 0) {
            this->horizontalRay.sum(raySum);
            continue;
        }
        hitWall = true;
    }
}

void Raycaster::calculateVerticalRay() {
    if (fabs(cos(rayAngle)) < EPSILON) {
        this->vRayDist = std::numeric_limits<float>::infinity();
        return;
    }

    Vector raySum;
    bool hitWall = false;
    float vTang = -tan(rayAngle);

    if (rayAngle < 3 * PI / 2 && rayAngle > PI / 2) {
        int blockPos = playerPos.getX() / BLOCK_SIZE;

        float rx = blockPos * BLOCK_SIZE - EPSILON;
        float ry = (playerPos.getX() - rx) * vTang + playerPos.getY();

        this->verticalRay = Vector(rx, ry);

        float xo = -BLOCK_SIZE;
        float yo = -xo * vTang;
        raySum = Vector(xo, yo);
    }
    if (rayAngle > 3 * PI / 2 || rayAngle < PI / 2) {
        int blockPos = playerPos.getX() / BLOCK_SIZE;

        float rx = blockPos * BLOCK_SIZE + BLOCK_SIZE;
        float ry = (playerPos.getX() - rx) * vTang + playerPos.getY();

        this->verticalRay = Vector(rx, ry);

        float xo = BLOCK_SIZE;
        float yo = -xo * vTang;

        raySum = Vector(xo, yo);
    }

    while (!hitWall) {
        this->vRayDist = playerPos.distance(this->verticalRay);

        if (!map.isInsideMap(this->verticalRay)) {
            break;
        }
        if (map.getBlock(this->verticalRay) == 0) {
            this->verticalRay.sum(raySum);
            continue;
        }
        hitWall = true;
    }
}

void Raycaster::calculateFinalRay() {
    if (hRayDist < vRayDist) {
        this->finalRayDist = this->hRayDist;
        this->finalRay = this->horizontalRay;

        map.setWallType(finalRay, false);
        float rayX = finalRay.getX();
        map.setColWall(rayX);
    } else {
        this->finalRayDist = this->vRayDist;
        this->finalRay = this->verticalRay;

        map.setWallType(finalRay, true);
        float rayY = finalRay.getY();
        map.setColWall(rayY);
    }

    // To avoid fisheye effect
    float newAngle = playerAngle - rayAngle;
    finalRayDist = finalRayDist * cos(newAngle);
}

float Raycaster::getDistance() { return finalRayDist; }

void Raycaster::renderWalls(int pos) {
    int largoCol = 1;
    float largoPared = (BLOCK_SIZE * SCREEN_WIDTH) / finalRayDist;

    // Desde donde voy a empezar a dibujar la pared
    float offset = (SCREEN_HEIGHT / 2.0f) - (largoPared / 2.0f);

    int largoParedInt = largoPared;
    int offsetInt = offset;

    map.renderWall(pos, offsetInt, largoCol, largoParedInt);
}
