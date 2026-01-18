#include "Raycaster.h"
#include "Constants.h"
#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

Raycaster::Raycaster(Vector &playerPos, float playerAngle, Map &map)
    : playerPos(playerPos), playerAngle(playerAngle), map(map) {}

void Raycaster::calculateRay(float rayAngle) {
    this->rayAngle = rayAngle;

    calculateHorizontalRay();
    calculateVerticalRay();
    calculateFinalRay();
}

void Raycaster::moveRayIntoWall(Vector &ray, const Vector &step,
                                float &distance) {
    bool hitWall = false;

    while (!hitWall) {
        distance = this->playerPos.distance(ray);

        if (!map.isInsideMap(ray)) {
            break;
        }
        if (map.getBlock(ray) == 0) {
            ray.sum(step);
            continue;
        }
        hitWall = true;
    }
}

Vector Raycaster::calculateInitialRay(float blockPos, float offset, float tang,
                                      RayDirection direction) {
    float rx, ry;
    float playerX = this->playerPos.getX();
    float playerY = this->playerPos.getY();

    if (direction == RayDirection::HORIZONTAL) {
        ry = blockPos * BLOCK_SIZE + offset;
        rx = (playerY - ry) * tang + playerX;
    } else {
        rx = blockPos * BLOCK_SIZE + offset;
        ry = (playerX - rx) * tang + playerY;
    }
    return Vector(rx, ry);
}

bool Raycaster::isRayValid(RayDirection direction) {
    float angle = direction == RayDirection::HORIZONTAL ? sin(this->rayAngle)
                                                        : cos(this->rayAngle);

    return (fabs(angle) > EPSILON);
}

bool Raycaster::isAngleFacingUp() { return this->rayAngle > PI; }

bool Raycaster::isAngleFacingLeft() {
    return (this->rayAngle < 3 * PI / 2) && (this->rayAngle > PI / 2);
}

void Raycaster::calculateHorizontalRay() {
    if (!isRayValid(RayDirection::HORIZONTAL)) {
        this->hRayDist = std::numeric_limits<float>::infinity();
        return;
    }

    float xo, yo, offset;
    float hTang = -1 / tan(this->rayAngle);
    int blockPos = this->playerPos.getY() / BLOCK_SIZE;

    if (isAngleFacingUp()) {
        offset = -EPSILON;
        yo = -BLOCK_SIZE;
        xo = -yo * hTang;
    } else {
        offset = BLOCK_SIZE;
        yo = BLOCK_SIZE;
        xo = -yo * hTang;
    }

    this->horizontalRay =
        calculateInitialRay(blockPos, offset, hTang, RayDirection::HORIZONTAL);

    Vector RayStep(xo, yo);
    moveRayIntoWall(this->horizontalRay, RayStep, this->hRayDist);
}

void Raycaster::calculateVerticalRay() {
    if (!isRayValid(RayDirection::VERTICAL)) {
        this->vRayDist = std::numeric_limits<float>::infinity();
        return;
    }

    float xo, yo, offset;
    float vTang = -tan(rayAngle);
    int blockPos = this->playerPos.getX() / BLOCK_SIZE;

    if (isAngleFacingLeft()) {
        offset = -EPSILON;
        xo = -BLOCK_SIZE;
        yo = -xo * vTang;
    } else {
        offset = BLOCK_SIZE;
        xo = BLOCK_SIZE;
        yo = -xo * vTang;
    }

    this->verticalRay =
        calculateInitialRay(blockPos, offset, vTang, RayDirection::VERTICAL);

    Vector RayStep(xo, yo);
    moveRayIntoWall(this->verticalRay, RayStep, this->vRayDist);
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
