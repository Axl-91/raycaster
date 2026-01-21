#ifndef RENDERER_H
#define RENDERER_H

#include "Map.h"
#include "Player.h"
#include <SDL2/SDL.h>

class Renderer {
  private:
    SDL_Renderer *sdlRenderer = nullptr;
    Player &player;
    Map &map;

    /**
     * Clears screen
     */
    void clearScreen();

  public:
    /**
     * Constructor - initializes renderer dependencies
     */
    Renderer(Player &player, Map &map);

    /**
     * Set SDL renderer
     */
    void setRenderer(SDL_Renderer *renderer);

    /**
     * Render Player
     */
    void render();

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;
};

#endif
