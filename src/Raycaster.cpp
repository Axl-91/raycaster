#include "Raycaster.h"
#include "Constants.h"
#include "Player.h"
#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

Raycaster::Raycaster(const Player &player, Map &map)
    : playerPos(player.getPos()), playerAngle(player.getAngle()), map(map) {

    this->horizontalRay.direction = RayDirection::HORIZONTAL;
    this->verticalRay.direction = RayDirection::VERTICAL;
}

void Raycaster::updatePlayerValues(const Player &player) {
    this->playerPos = player.getPos();
    this->playerAngle = player.getAngle();
}

void Raycaster::moveRayIntoWall(Ray &ray, const Vector &step) {
    bool hitWall = false;

    while (!hitWall) {
        ray.distance = this->playerPos.distance(ray.position);

        if (!map.isInsideMap(ray.position)) {
            break;
        }
        if (map.getBlock(ray.position) == 0) {
            ray.position.sum(step);
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

bool Raycaster::isAngleFacingUp() {
    // Angle lower than 180°
    return this->rayAngle > PI;
}

bool Raycaster::isAngleFacingLeft() {
    // Angle between 90° and 270°
    return (this->rayAngle < 3 * PI / 2) && (this->rayAngle > PI / 2);
}

void Raycaster::calculateHorizontalRay() {
    if (!isRayValid(RayDirection::HORIZONTAL)) {
        this->horizontalRay.distance = std::numeric_limits<float>::infinity();
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

    this->horizontalRay.position =
        calculateInitialRay(blockPos, offset, hTang, RayDirection::HORIZONTAL);

    Vector RayStep(xo, yo);
    moveRayIntoWall(this->horizontalRay, RayStep);
}

void Raycaster::calculateVerticalRay() {
    if (!isRayValid(RayDirection::VERTICAL)) {
        this->verticalRay.distance = std::numeric_limits<float>::infinity();
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

    this->verticalRay.position =
        calculateInitialRay(blockPos, offset, vTang, RayDirection::VERTICAL);

    Vector RayStep(xo, yo);
    moveRayIntoWall(this->verticalRay, RayStep);
}

void Raycaster::calculateFinalRay() {
    if (this->horizontalRay.distance < this->verticalRay.distance) {
        this->finalRay = this->horizontalRay;
    } else {
        this->finalRay = this->verticalRay;
    }

    // To avoid fisheye effect
    float newAngle = playerAngle - this->rayAngle;
    this->finalRay.distance *= cos(newAngle);
}

void Raycaster::calculateRay() {
    calculateHorizontalRay();
    calculateVerticalRay();
    calculateFinalRay();
}

Ray &Raycaster::getRay(float rayAngle) {
    this->rayAngle = rayAngle;
    calculateRay();
    return this->finalRay;
}
