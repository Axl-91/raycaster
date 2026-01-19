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

Renderer::Renderer(Map &map, Player &player, Raycaster &raycaster)
    : map(map), player(player), raycaster(raycaster) {}

void Renderer::setRenderer(SDL_Renderer *renderer) {
    this->sdlRenderer = renderer;

    this->hud.loadTexture(this->sdlRenderer);
    this->gun.loadTextures(this->sdlRenderer);
    this->wallTextures.loadTexture(this->sdlRenderer);

    this->map.setRenderer(this->sdlRenderer);
}

void Renderer::renderBackground() {
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
    bool isDark = ray.direction == RayDirection::VERTICAL ? true : false;

    int wallType = this->map.getBlock(ray.position) - 1;
    this->wallTextures.setWall(wallType, isDark);
}

void Renderer::setColWall(Ray &ray) {
    float wallPos = ray.direction == RayDirection::HORIZONTAL
                        ? ray.position.getX()
                        : ray.position.getY();

    int intPosX = floor(wallPos);
    int xOffset = intPosX % BLOCK_SIZE;

    this->wallTextures.selectSpriteCol(xOffset);
}

void Renderer::renderWallCol(int screenPos, Ray &ray) {
    int wallHeight =
        static_cast<int>((BLOCK_SIZE * SCREEN_WIDTH) / ray.distance);

    float screenCenterY = USABLE_SCREEN_HEIGHT / 2.0f;
    float wallCenter = wallHeight / 2.0f;
    int wallInitPosY = static_cast<int>(screenCenterY - wallCenter);

    this->wallTextures.render(this->sdlRenderer, screenPos, wallInitPosY,
                              COL_WIDTH, wallHeight);
}

void Renderer::renderWalls() {
    Raycaster raycaster(this->player, this->map);

    // We need to start to create rays from the angle of the player minus 30°
    float angleRay = this->player.getAngle() - OFFSET_RAYCASTER;

    for (int pos = 0; pos < SCREEN_WIDTH; ++pos) {
        angleRay = normalizeAngle(angleRay);

        Ray ray = raycaster.getRay(angleRay);
        setWallType(ray);
        setColWall(ray);
        renderWallCol(pos, ray);

        this->distancesList[pos] = ray.distance;

        // Step is the amount neccesary to add so we can
        // fill the entire screen with the rays from -30° to +30°
        angleRay += STEP_RAYCASTER;
    }
}

void Renderer::renderObjects() {
    int uno = 1;
    Vector posJugador = this->player.getPos();
    this->map.sortObjByDist(posJugador);
    std::vector<mapObject> mapObjects = this->map.getObjects();

    for (mapObject obj : mapObjects) {
        if (!this->player.objIsVisible(obj.position)) {
            continue;
        }
        float distanciaObj = posJugador.distance(obj.position);

        // Coordenadas en Y
        float sizeObj = (64 * 320) / distanciaObj;
        float yo = 100 - (sizeObj / 2);
        // Coordenadas en X
        float dx = posJugador.getX() - obj.position.getX();
        float dy = posJugador.getY() - obj.position.getY();

        float anguloObj = atan2(dy, dx) - this->player.getAngle();
        float xo = tan(anguloObj) * 277.1281;
        float x = 160.0f + xo - sizeObj / 2.0f;

        float anchura = sizeObj / 64;
        int yoInt = yo;
        int sizeObjInt = sizeObj;
        this->map.setObjType(obj.type);

        for (int i = 0; i < 64; ++i) {
            for (int j = 0; j < anchura; ++j) {
                int z = round(x) + ((i)*anchura) + j;
                if (z < 0 || z > 320) {
                    continue;
                }

                if (this->distancesList[z] > distanciaObj) {
                    this->map.setColObject(i);
                    this->map.renderObject(z, yoInt, uno, sizeObjInt);
                }
            }
        }
    }
}

void Renderer::render() {
    renderBackground();
    renderWalls();
    renderObjects();

    this->hud.renderHud(this->sdlRenderer);
    this->gun.render(this->sdlRenderer);

    SDL_RenderPresent(this->sdlRenderer);
}
