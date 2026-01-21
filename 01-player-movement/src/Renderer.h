#ifndef RENDERER_H
#define RENDERER_H

#include "Player.h"
#include <SDL2/SDL.h>

class Renderer {
  private:
    SDL_Renderer *sdlRenderer = nullptr;
    Player &player;

    /**
     * Clears screen
     */
    void clearScreen();

  public:
    /**
     * Constructor - initializes renderer dependencies
     */
    Renderer(Player &player);

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
