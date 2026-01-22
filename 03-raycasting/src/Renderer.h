#ifndef RENDERER_H
#define RENDERER_H

#include "Map.h"
#include "Player.h"
#include "Raycaster.h"
#include <SDL2/SDL.h>

class Renderer {
  private:
    static constexpr float OFFSET_RAYCASTER = PI / 6;
    static constexpr float STEP_RAYCASTER =
        (OFFSET_RAYCASTER * 2) / SCREEN_WIDTH;

    SDL_Renderer *sdlRenderer = nullptr;
    Player &player;
    Map &map;
    Raycaster &raycaster;

    /**
     * Clears screen
     */
    void clearScreen();

    void renderRays();

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
