#include "Renderer.h"
#include "Constants.h"
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

    Vector playerPos = this->map.mapToScreen(this->player.getPos());

    for (int pos = 0; pos < AMOUNT_RAYS; ++pos) {
        angleRay = normalizeAngle(angleRay);

        Ray ray = this->raycaster.getRay(angleRay);

        Vector rayPos = this->map.mapToScreen(ray.position);

        // We're going to render the rays with the green color
        SDL_SetRenderDrawColor(sdlRenderer, 0x08, 0xFF, 0x08, 0x01);
        SDL_RenderDrawLine(sdlRenderer, playerPos.getX(), playerPos.getY(),
                           rayPos.getX(), rayPos.getY());

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
