#include "Renderer.h"
#include "Config.h"
#include <SDL2/SDL_log.h>
#include <cmath>

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

Renderer::Renderer(Map &map, Player &player, Raycaster &raycaster)
    : map(map), player(player), raycaster(raycaster) {}

void Renderer::setRenderer(SDL_Renderer *renderer, Config &config) {
    this->sdlRenderer = renderer;

    SpriteConfig hudConfig = config.getHudSpriteConfig();
    SpriteConfig gunsConfig = config.getGunsSpriteConfig();
    SpriteConfig wallsConfig = config.getWallsSpriteConfig();
    SpriteConfig objConfig = config.getObjectsSpriteConfig();

    this->hudSprites.loadTexture(this->sdlRenderer, hudConfig.path.c_str());
    this->gunSprites.loadTexture(this->sdlRenderer, gunsConfig.path.c_str());

    this->wallSprites.loadTexture(this->sdlRenderer, wallsConfig.path.c_str(),
                                  wallsConfig.columns);
    this->wallSprites.setVariantCount(wallsConfig.variants);

    this->objectSprites.loadTexture(this->sdlRenderer, objConfig.path.c_str(),
                                    objConfig.columns);
    this->objectSprites.setSpacing(objConfig.spacing);
}

void Renderer::renderBackground() const {
    // Fill all screen with the FLOOR_COLOR
    SDL_SetRenderDrawColor(this->sdlRenderer, FLOOR_COLOR.r, FLOOR_COLOR.g,
                           FLOOR_COLOR.b, FLOOR_COLOR.a);
    SDL_RenderClear(this->sdlRenderer);

    SDL_Rect ceilingRect = {0, 0, SCREEN_WIDTH, (USABLE_SCREEN_HEIGHT) / 2};

    // Render CEILING_COLOR on the top half of the screen
    SDL_SetRenderDrawColor(this->sdlRenderer, CEILING_COLOR.r, CEILING_COLOR.g,
                           CEILING_COLOR.b, CEILING_COLOR.a);
    SDL_RenderFillRect(this->sdlRenderer, &ceilingRect);
}

void Renderer::setWallType(Ray &ray) {
    int wallType = this->map.getBlock(ray.position) - 1;
    this->wallSprites.setSprite(wallType);

    // If its vertical I change the variant to the dark one
    if (ray.direction == RayDirection::VERTICAL) {
        this->wallSprites.changeVariant();
    }
}

void Renderer::setWallCol(Ray &ray) {
    float wallPos = ray.direction == RayDirection::HORIZONTAL
                        ? ray.position.getX()
                        : ray.position.getY();

    int intPosX = floor(wallPos);
    int xOffset = intPosX % BLOCK_SIZE;

    this->wallSprites.selectSpriteCol(xOffset);
}

void Renderer::renderWallCol(int screenPos, Ray &ray) const {
    int wallHeight =
        static_cast<int>((BLOCK_SIZE * SCREEN_WIDTH) / ray.distance);

    float screenCenterY = USABLE_SCREEN_HEIGHT / 2.0f;
    float wallCenter = wallHeight / 2.0f;
    int wallInitPosY = static_cast<int>(screenCenterY - wallCenter);

    this->wallSprites.render(this->sdlRenderer, screenPos, wallInitPosY,
                             COL_WIDTH, wallHeight);
}

void Renderer::renderWalls() {
    // We need to start to create rays from the angle of the player minus 30°
    float angleRay = this->player.getAngle() - OFFSET_RAYCASTER;

    for (int pos = 0; pos < AMOUNT_RAYS; ++pos) {
        angleRay = normalizeAngle(angleRay);

        Ray ray = this->raycaster.getRay(angleRay);
        setWallType(ray);
        setWallCol(ray);
        renderWallCol(pos, ray);

        this->wallDistances[pos] = ray.distance;

        // Step is the amount neccesary to add so we can
        // fill the entire screen with the rays from -30° to +30°
        angleRay += STEP_RAYCASTER;
    }
}

void Renderer::renderObject(float offsetX, float objDistance) {
    // How big or small im going to render in base to distance from player
    float sizeObj = (BLOCK_SIZE * SCREEN_WIDTH) / objDistance;

    // Starting point to draw object in X
    float xo = (SCREEN_WIDTH / 2.0f) + offsetX - sizeObj / 2.0f;
    int baseX = static_cast<int>(std::round(xo));

    // Starting point to draw object in Y
    float yo =
        static_cast<int>((USABLE_SCREEN_HEIGHT / 2.0f) - (sizeObj / 2.0f));

    // Number of screen columns each texture column occupies
    float colRepetitions = sizeObj / BLOCK_SIZE;

    for (int objX = 0; objX < BLOCK_SIZE; ++objX) {
        int colStart = static_cast<int>(baseX + objX * colRepetitions);
        int colEnd = static_cast<int>(baseX + (objX + 1) * colRepetitions);

        this->objectSprites.selectSpriteCol(objX);

        for (int posX = colStart; posX < colEnd; ++posX) {
            if (posX < 0 || posX >= SCREEN_WIDTH) {
                continue;
            }
            if (this->wallDistances[posX] < objDistance) {
                continue;
            }

            // If there is no wall closer I render the object column
            this->objectSprites.render(this->sdlRenderer, posX, yo, COL_WIDTH,
                                       sizeObj);
        }
    }
}

void Renderer::renderVisibleObjects() {
    Vector playerPos = this->player.getPos();

    std::vector<mapObject> mapObjects = this->map.getObjectsSorted(playerPos);

    for (mapObject obj : mapObjects) {
        if (!this->player.objIsVisible(obj.position)) {
            continue;
        }
        this->objectSprites.setSprite(obj.type);

        // Get the object angle relative to player
        // to calculate the X position on screen
        float dx = playerPos.getX() - obj.position.getX();
        float dy = playerPos.getY() - obj.position.getY();
        float angleDiff = atan2(dy, dx) - this->player.getAngle();

        float offsetX = tan(angleDiff) * PPD;
        float objDistance = playerPos.distance(obj.position);

        renderObject(offsetX, objDistance);
    }
}

void Renderer::render() {
    renderBackground();
    renderWalls();
    renderVisibleObjects();

    this->hudSprites.render(this->sdlRenderer);
    this->gunSprites.render(this->sdlRenderer);
    // this->player.render(this->sdlRenderer);

    SDL_RenderPresent(this->sdlRenderer);
}
