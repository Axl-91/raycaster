#include "Renderer.h"
#include "Raycaster.h"
#include "Vector.h"

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

Renderer::Renderer(Player &player, Map &map, Raycaster &raycaster)
    : player(player), map(map), raycaster(raycaster) {}

void Renderer::setRenderer(SDL_Renderer *renderer) {
    this->sdlRenderer = renderer;
}

void Renderer::clearScreen() {
    SDL_SetRenderDrawColor(this->sdlRenderer, 0, 0, 0, 0);
    SDL_RenderClear(this->sdlRenderer);
}

void Renderer::renderRays() {
    // We need to start to create rays from the angle of the player minus 30°
    float angleRay = this->player.getAngle() - OFFSET_RAYCASTER;

    Vector playerPos = this->player.getPos();

    float mapPixelWidth = map.getAmountCols() * BLOCK_SIZE;
    float mapPixelHeight = map.getAmountRows() * BLOCK_SIZE;

    int x = (playerPos.getX() / mapPixelWidth) * SCREEN_WIDTH;
    int y = (playerPos.getY() / mapPixelHeight) * SCREEN_HEIGHT;

    for (int pos = 0; pos < SCREEN_WIDTH; ++pos) {
        angleRay = normalizeAngle(angleRay);

        Ray ray = this->raycaster.getRay(angleRay);

        int xRay = (ray.position.getX() / mapPixelWidth) * SCREEN_WIDTH;
        int yRay = (ray.position.getY() / mapPixelHeight) * SCREEN_HEIGHT;

        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0xFF, 0x00, 0xFF);

        SDL_RenderDrawLine(sdlRenderer, x, y, xRay, yRay);

        angleRay += STEP_RAYCASTER;
    }
}

void Renderer::render() {
    clearScreen();

    this->map.render(this->sdlRenderer);
    renderRays();
    this->player.render(this->sdlRenderer);

    SDL_RenderPresent(this->sdlRenderer);
}
