#ifndef RENDERER_H
#define RENDERER_H

#include "../components/GunSprite.h"
#include "../components/HudSprite.h"
#include "../components/Player.h"
#include "../components/StaticSprite.h"
#include "../maps/Map.h"
#include "Raycaster.h"
#include <SDL2/SDL.h>

#define WALLS_PATH "assets/walls.png"
#define OBJ_PATH "assets/objects.png"

class Renderer {
  private:
    static constexpr int COL_WIDTH = 1;

    static constexpr float OFFSET_RAYCASTER = PI / 6;
    static constexpr int AMOUNT_RAYS = SCREEN_WIDTH;
    static constexpr float STEP_RAYCASTER =
        (OFFSET_RAYCASTER * 2) / AMOUNT_RAYS;

    static constexpr SDL_Color FLOOR_COLOR = {0x80, 0x80, 0x80, 0xFF};
    static constexpr SDL_Color CEILING_COLOR = {0x33, 0x33, 0x33, 0xFF};

    SDL_Renderer *sdlRenderer = nullptr;

    Map &map;
    Player &player;

    Raycaster &raycaster;
    float wallDistances[SCREEN_WIDTH];

    StaticSprite wallSprites;
    StaticSprite objectSprites;
    HudSprite hud;
    GunSprite gun;

    /**
     * Render floor and ceiling
     */
    void renderBackground() const;

    /**
     * Set the wall type that belongs to the position of the ray
     * and if it is horizontal make it as the dark variant
     * @param ray The ray that is on the position to the wall
     */
    void setWallType(Ray &ray);

    /**
     * Set the wall column to render
     * @param ray The ray that is on the position to the wall
     */
    void setWallCol(Ray &ray);

    /**
     * Render a 1px col of the wall hitted by the raycaster
     */
    void renderWallCol(int screenPos, Ray &ray) const;

    /**
     * Render all walls using raycasting
     */
    void renderWalls();

    /**
     * Render a single object
     */
    void renderObject(float offsetX, float objDistance);

    /**
     * Render all objects/sprites in the player's vision
     */
    void renderVisibleObjects();

  public:
    /**
     * Constructor - initializes renderer dependencies
     */
    Renderer(Map &map, Player &player, Raycaster &raycaster);

    /**
     * Set SDL renderer and initialize all textures
     * Must be called after SDL initialization
     */
    void setRenderer(SDL_Renderer *renderer);

    /**
     * Render complete frame (background, walls, objects, HUD, gun)
     */
    void render();

    /**
     * Get reference to gun for input handling
     */
    GunSprite &getGun() { return gun; }

    /**
     * Get reference to HUD for input handling
     */
    HudSprite &getHud() { return hud; }

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;
};

#endif
