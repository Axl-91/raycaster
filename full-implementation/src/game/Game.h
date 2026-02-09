#ifndef __GAME__
#define __GAME__

#include "../components/GunSprite.h"
#include "../components/HudSprite.h"
#include "../components/Player.h"
#include "../maps/Map.h"
#include "../utils/Constants.h"
#include "Raycaster.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game {
  private:
    Config config;

    int realWidth = SCREEN_WIDTH;
    int realHeight = SCREEN_HEIGHT;

    bool gameOver = false;

    SDL_Window *window = nullptr;
    SDL_Renderer *sdlRenderer = nullptr;

    Map map;
    Player player;
    Raycaster raycaster;
    Renderer gameRenderer;

    /**
     * Handle window close and exit events
     * Closes game on window close (X button) or ESC key press
     * @param event SDL event to process
     */
    void exitPollEvent(SDL_Event &event);

  public:
    /**
     * Constructor - initializes SDL and creates game window
     * Sets up all game subsystems (HUD, guns, map, player)
     * @param width Physical window width in pixels
     * @param height Physical window height in pixels
     * @throws std::runtime_error if SDL initialization fails
     */
    Game();

    /**
     * Set the game window to fullscreen mode
     */
    void setFullScreen();

    /**
     * Render one complete frame
     * Drawing order: background → player/raycasting → gun → HUD → present
     */
    void render();

    /**
     * Poll and process all SDL events for one frame
     * Handles exit events, gun input, HUD input, and player movement
     * Gun shooting blocks HUD input to prevent weapon switching during
     * animation
     */
    void pollEvent();

    /**
     * Update game state each frame
     * Handles continuous input (player movement, gun shooting)
     * Called every frame to process held keys
     */
    void update();

    /**
     * Check if the game should exit
     * @return true if game should close, false otherwise
     */
    bool isGameOver() const;

    Game(const Game &copy) = delete;
    Game operator=(const Game &copy) = delete;

    ~Game();
};

#endif
