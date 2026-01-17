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
    float rx, ry, xo, yo;
    Vector raySuma;
    bool noHayColision = true;
    int grados = toGradosRay(rayAngle);
    float tangH = -1 / tan(rayAngle);

    if (grados > 180) {
        int bloqPasados = playerPos.getY() / BLOCK_SIZE;
        ry = bloqPasados * BLOCK_SIZE - 0.0001;
        rx = (playerPos.getY() - ry) * tangH + playerPos.getX();
        horizontalRay = Vector(rx, ry);

        yo = -BLOCK_SIZE;
        xo = -yo * tangH;
        raySuma = Vector(xo, yo);
    }
    if (grados < 180) {
        int bloqPasados = playerPos.getY() / BLOCK_SIZE;
        ry = bloqPasados * BLOCK_SIZE + BLOCK_SIZE;
        rx = (playerPos.getY() - ry) * tangH + playerPos.getX();
        horizontalRay = Vector(rx, ry);

        yo = BLOCK_SIZE;
        xo = -yo * tangH;
        raySuma = Vector(xo, yo);
    }
    if (grados == 0 || grados == 360 || grados == 180) {
        noHayColision = false;
    }

    while (noHayColision) {
        hRayDist = playerPos.distance(horizontalRay);

        if (!map.isInsideMap(horizontalRay)) {
            break;
        }
        if (map.getBlock(horizontalRay) == 0) {
            horizontalRay.sum(raySuma);
        } else {
            noHayColision = false;
        }
    }
}

void Raycaster::calculateVerticalRay() {
    float rx, ry, xo, yo;
    Vector raySuma;
    bool noHayColision = true;
    int grados = toGradosRay(rayAngle);
    float tangV = -tan(rayAngle);

    if (grados < 270 && grados > 90) {
        int bloqPasados = playerPos.getX() / BLOCK_SIZE;
        rx = bloqPasados * BLOCK_SIZE - 0.0001;
        ry = (playerPos.getX() - rx) * tangV + playerPos.getY();
        verticalRay = Vector(rx, ry);

        xo = -BLOCK_SIZE;
        yo = -xo * tangV;
        raySuma = Vector(xo, yo);
    }
    if (grados > 270 || grados < 90) {
        int bloqPasados = playerPos.getX() / BLOCK_SIZE;
        rx = bloqPasados * BLOCK_SIZE + BLOCK_SIZE;
        ry = (playerPos.getX() - rx) * tangV + playerPos.getY();
        verticalRay = Vector(rx, ry);

        xo = BLOCK_SIZE;
        yo = -xo * tangV;
        raySuma = Vector(xo, yo);
    }
    if (grados == 270 || grados == 90) {
        noHayColision = false;
    }

    while (noHayColision) {
        vRayDist = playerPos.distance(verticalRay);

        if (!map.isInsideMap(verticalRay)) {
            break;
        }
        if (map.getBlock(verticalRay) == 0) {
            verticalRay.sum(raySuma);
        } else {
            noHayColision = false;
        }
    }
}

void Raycaster::calculateFinalRay() {
    if (hRayDist < vRayDist) {
        finalRayDist = hRayDist;
        this->finalRay = horizontalRay;
        if (!map.isInsideMap(finalRay)) {
            SDL_Log("Raycaster (%f, %f)", finalRay.getX(), finalRay.getY());
        }
        map.setWallType(finalRay, false);
        float rayX = finalRay.getX();
        map.setColWall(rayX);
    } else {
        finalRayDist = vRayDist;
        this->finalRay = verticalRay;
        if (!map.isInsideMap(finalRay)) {
            SDL_Log("Raycaster (%f, %f)", finalRay.getX(), finalRay.getY());
        }
        map.setWallType(finalRay, true);
        float rayY = finalRay.getY();
        map.setColWall(rayY);
    }

    /* Para evitar efecto fisheye */
    float angNuevo = playerAngle - rayAngle;
    if (angNuevo < 0) {
        angNuevo += 2 * PI;
    }
    if (angNuevo > 2 * PI) {
        angNuevo -= 2 * PI;
    }
    finalRayDist = finalRayDist * cos(angNuevo);
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
