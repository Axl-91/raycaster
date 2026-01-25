#include "Raycaster.h"
#include "Constants.h"
#include "Player.h"
#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

Raycaster::Raycaster(const Player &player, const Map &map)
    : player(player), map(map) {

    this->horizontalRay.direction = RayDirection::HORIZONTAL;
    this->verticalRay.direction = RayDirection::VERTICAL;
}

void Raycaster::moveRayIntoWall(Ray &ray, const Vector &step) {
    bool hitWall = false;

    while (!hitWall) {
        ray.distance = this->player.getPos().distance(ray.position);

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

Vector Raycaster::calculateInitPos(float offset, float tangent,
                                   RayDirection direction) {
    float rx, ry;
    Vector playerPos = this->player.getPos();

    float playerX = playerPos.getX();
    float playerY = playerPos.getY();

    if (direction == RayDirection::HORIZONTAL) {
        int blockPos = playerPos.getY() / BLOCK_SIZE;

        ry = blockPos * BLOCK_SIZE + offset;
        rx = (playerY - ry) * tangent + playerX;
    } else {
        int blockPos = playerPos.getX() / BLOCK_SIZE;

        rx = blockPos * BLOCK_SIZE + offset;
        ry = (playerX - rx) * tangent + playerY;
    }
    return Vector(rx, ry);
}

bool Raycaster::isRayValid(RayDirection direction) {
    float angle = direction == RayDirection::HORIZONTAL ? sin(this->rayAngle)
                                                        : cos(this->rayAngle);

    return (fabs(angle) > EPSILON);
}

bool Raycaster::isAngleFacingUp() {
    // Angle higher than 180°
    return this->rayAngle > PI;
}

bool Raycaster::isAngleFacingLeft() {
    // Angle between 90° and 270°
    return (this->rayAngle < 3 * PI / 2) && (this->rayAngle > PI / 2);
}

void Raycaster::calculateRay(Ray &ray, RayConfig &rayConfig) {
    if (!isRayValid(ray.direction)) {
        ray.distance = std::numeric_limits<float>::infinity();
        return;
    }
    float xo, yo, offset;

    if (ray.direction == RayDirection::HORIZONTAL) {
        offset = rayConfig.isNegativeDir ? -EPSILON : BLOCK_SIZE;
        yo = rayConfig.isNegativeDir ? -BLOCK_SIZE : BLOCK_SIZE;
        xo = -yo * rayConfig.tangent;
    } else {
        offset = rayConfig.isNegativeDir ? -EPSILON : BLOCK_SIZE;
        xo = rayConfig.isNegativeDir ? -BLOCK_SIZE : BLOCK_SIZE;
        yo = -xo * rayConfig.tangent;
    }
    ray.position = calculateInitPos(offset, rayConfig.tangent, ray.direction);

    Vector RayStep(xo, yo);
    moveRayIntoWall(ray, RayStep);
}

void Raycaster::calculateHorizontalRay() {
    RayConfig rayConfig{isAngleFacingUp(), -1 / tan(this->rayAngle)};
    calculateRay(this->horizontalRay, rayConfig);
}

void Raycaster::calculateVerticalRay() {
    RayConfig rayConfig{isAngleFacingLeft(), -tan(this->rayAngle)};
    calculateRay(this->verticalRay, rayConfig);
}

const Ray &Raycaster::getClosestRay() {
    calculateHorizontalRay();
    calculateVerticalRay();

    Ray &closestRay = this->horizontalRay.distance < this->verticalRay.distance
                          ? this->horizontalRay
                          : this->verticalRay;

    // To avoid fisheye effect
    float newAngle = this->player.getAngle() - this->rayAngle;
    closestRay.distance *= cos(newAngle);

    return closestRay;
}

const Ray &Raycaster::getRay(float rayAngle) {
    this->rayAngle = rayAngle;
    return getClosestRay();
}
