#ifndef RENDERER_H
#define RENDERER_H

#include "Guns.h"
#include "Hud.h"
#include "Map.h"
#include "Objects.h"
#include "Player.h"
#include "Raycaster.h"
#include "Walls.h"
#include <SDL2/SDL.h>

class Renderer {
  private:
    static constexpr float OFFSET_RAYCASTER = PI / 6;
    static constexpr float STEP_RAYCASTER =
        (OFFSET_RAYCASTER * 2) / SCREEN_WIDTH;

    float distancesList[SCREEN_WIDTH];

    SDL_Renderer *sdlRenderer = nullptr;

    Map &map;
    Player &player;
    Raycaster &raycaster;

    Walls wallTextures;
    Objects objectTextures;
    Hud hud;
    Guns gun;

    static constexpr SDL_Color FLOOR_COLOR = {0x80, 0x80, 0x80, 0xFF};
    static constexpr SDL_Color CEILING_COLOR = {0x33, 0x33, 0x33, 0xFF};

    /**
     * Render floor and ceiling
     */
    void renderBackground();

    /**
     * Render all walls using raycasting
     */
    void renderWalls();

    /**
     * Render all objects/sprites in the scene
     */
    void renderObjects();

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
    Guns &getGun() { return gun; }

    /**
     * Get reference to HUD for input handling
     */
    Hud &getHud() { return hud; }

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;
};

#endif
