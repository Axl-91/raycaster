#include "Renderer.h"
#include "Constants.h"
#include "Raycaster.h"

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

void Renderer::renderBackground() const {
    // Fill all screen with the FLOOR_COLOR
    SDL_SetRenderDrawColor(this->sdlRenderer, FLOOR_COLOR.r, FLOOR_COLOR.g,
                           FLOOR_COLOR.b, FLOOR_COLOR.a);
    SDL_RenderClear(this->sdlRenderer);

    SDL_Rect ceilingRect = {0, 0, SCREEN_WIDTH, (SCREEN_HEIGHT) / 2};

    // Render CEILING_COLOR on the top half of the screen
    SDL_SetRenderDrawColor(this->sdlRenderer, CEILING_COLOR.r, CEILING_COLOR.g,
                           CEILING_COLOR.b, CEILING_COLOR.a);
    SDL_RenderFillRect(this->sdlRenderer, &ceilingRect);
}

void Renderer::renderWallCol(int screenPos, Ray &ray) const {
    int wallHeight =
        static_cast<int>((BLOCK_SIZE * SCREEN_WIDTH) / ray.distance);

    float screenCenterY = SCREEN_HEIGHT / 2.0f;
    float wallCenter = wallHeight / 2.0f;
    int wallInitPosY = static_cast<int>(screenCenterY - wallCenter);

    SDL_Rect wallRect = {screenPos, wallInitPosY, COL_WIDTH, wallHeight};

    // Vertical walls are rendered darker to simulate light direction
    if (ray.direction == RayDirection::VERTICAL) {
        SDL_SetRenderDrawColor(this->sdlRenderer, 0xFF, 0x00, 0x00, 0x00);
    } else {
        SDL_SetRenderDrawColor(this->sdlRenderer, 0x80, 0x05, 0x00, 0x00);
    };

    SDL_RenderFillRect(this->sdlRenderer, &wallRect);
}

void Renderer::renderWalls() {
    // We need to start to create rays from the angle of the player minus 30°
    float angleRay = this->player.getAngle() - OFFSET_RAYCASTER;

    for (int pos = 0; pos < AMOUNT_RAYS; ++pos) {
        angleRay = normalizeAngle(angleRay);

        Ray ray = this->raycaster.getRay(angleRay);
        renderWallCol(pos, ray);

        // Step is the amount neccesary to add so we can
        // fill the entire screen with the rays from -30° to +30°
        angleRay += STEP_RAYCASTER;
    }
}

void Renderer::render() {
    renderBackground();

    // this->map.render(this->sdlRenderer);
    // this->player.render(this->sdlRenderer);

    renderWalls();

    SDL_RenderPresent(this->sdlRenderer);
}
