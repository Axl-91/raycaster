#ifndef RENDERER_H
#define RENDERER_H

#include "Constants.h"
#include "Map.h"
#include "Player.h"
#include "Raycaster.h"
#include <SDL2/SDL.h>

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
    Player &player;
    Map &map;
    Raycaster &raycaster;

    /**
     * Render floor and ceiling
     */
    void renderBackground() const;

    /**
     * Render a 1px col of the wall hitted by the raycaster
     */
    void renderWallCol(int screenPos, Ray &ray) const;

    /**
     * Render all walls using raycasting
     */
    void renderWalls();

  public:
    /**
     * Constructor - initializes renderer dependencies
     */
    Renderer(Player &player, Map &map, Raycaster &raycaster);

    /**
     * Set SDL renderer
     */
    void setRenderer(SDL_Renderer *renderer);

    /**
     * Render Player and raycaster rays
     */
    void render();

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;
};

#endif
