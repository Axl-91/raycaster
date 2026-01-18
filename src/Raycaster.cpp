#include "Raycaster.h"
#include "Constants.h"
#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Raycaster::Raycaster(Vector &playerPos, float playerAngle, Map &map)
    : playerPos(playerPos), playerAngle(playerAngle), map(map) {}

void Raycaster::calculateRay(float rayAngle) {
    this->rayAngle = rayAngle;
    calculateHorizontalRay();
    calculateVerticalRay();
    calculateFinalRay();
}

bool Raycaster::isAngleFacingUp() { return this->rayAngle > PI; }

void Raycaster::calculateHorizontalRay() {
    if (fabs(sin(this->rayAngle)) < EPSILON) {
        this->hRayDist = std::numeric_limits<float>::infinity();
        return;
    }

    Vector raySum;
    bool hitWall = false;
    float hTang = -1 / tan(this->rayAngle);

    if (isAngleFacingUp()) {
        int blockPos = this->playerPos.getY() / BLOCK_SIZE;

        // Initial ray position
        float ry = blockPos * BLOCK_SIZE - EPSILON;
        float rx =
            ((this->playerPos.getY() - ry) * hTang) + this->playerPos.getX();

        this->horizontalRay = Vector(rx, ry);

        float yo = -BLOCK_SIZE;
        float xo = -yo * hTang;

        raySum = Vector(xo, yo);
    } else {
        int blockPos = this->playerPos.getY() / BLOCK_SIZE;

        // Initial ray position
        float ry = blockPos * BLOCK_SIZE + BLOCK_SIZE;
        float rx =
            (this->playerPos.getY() - ry) * hTang + this->playerPos.getX();

        this->horizontalRay = Vector(rx, ry);

        float yo = BLOCK_SIZE;
        float xo = -yo * hTang;

        raySum = Vector(xo, yo);
    }

    while (!hitWall) {
        this->hRayDist = this->playerPos.distance(this->horizontalRay);

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

bool Raycaster::isAngleFacingLeft() {
    return (this->rayAngle < 3 * PI / 2) && (this->rayAngle > PI / 2);
}

void Raycaster::calculateVerticalRay() {
    if (fabs(cos(this->rayAngle)) < EPSILON) {
        this->vRayDist = std::numeric_limits<float>::infinity();
        return;
    }

    Vector raySum;
    bool hitWall = false;
    float vTang = -tan(rayAngle);

    if (isAngleFacingLeft()) {
        int blockPos = this->playerPos.getX() / BLOCK_SIZE;

        float rx = blockPos * BLOCK_SIZE - EPSILON;
        float ry =
            (this->playerPos.getX() - rx) * vTang + this->playerPos.getY();

        this->verticalRay = Vector(rx, ry);

        float xo = -BLOCK_SIZE;
        float yo = -xo * vTang;
        raySum = Vector(xo, yo);
    } else {
        int blockPos = this->playerPos.getX() / BLOCK_SIZE;

        float rx = blockPos * BLOCK_SIZE + BLOCK_SIZE;
        float ry =
            (this->playerPos.getX() - rx) * vTang + this->playerPos.getY();

        this->verticalRay = Vector(rx, ry);

        float xo = BLOCK_SIZE;
        float yo = -xo * vTang;

        raySum = Vector(xo, yo);
    }

    while (!hitWall) {
        this->vRayDist = this->playerPos.distance(this->verticalRay);

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
    float newAngle = playerAngle - this->rayAngle;
    finalRayDist = finalRayDist * cos(newAngle);
}

float Raycaster::getDistance() { return finalRayDist; }

void Raycaster::renderWalls(int posX) {
    int wallHeight =
        static_cast<int>((BLOCK_SIZE * SCREEN_WIDTH) / finalRayDist);

    float screenCenterY = SCREEN_HEIGHT / 2.0f;
    float wallCenter = wallHeight / 2.0f;
    int wallInitPosY = static_cast<int>(screenCenterY - wallCenter);

    map.renderWall(posX, wallInitPosY, COL_WIDTH, wallHeight);
}
