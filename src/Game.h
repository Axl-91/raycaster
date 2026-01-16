#ifndef __GAME__
#define __GAME__

#include "Guns.h"
#include "Hud.h"
#include "Map.h"
#include "Player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game {
  private:
    int realWidth = 320;
    int realHeight = 240;
    bool gameOver = false;
    int winWidth;
    int winHeight;
    Hud hud;
    Guns gun;
    Map map;
    Player player;
    SDL_Window *window;
    SDL_Renderer *renderer;

    /**
     * Handle window close and exit events
     * Closes game on window close (X button) or ESC key press
     * @param event SDL event to process
     */
    void exitPollEvent(SDL_Event &event);

    /**
     * Fill the screen with background (ceiling and floor)
     * Draws dark gray ceiling and medium gray floor with horizon line
     */
    void fill();

  public:
    /**
     * Constructor - initializes SDL and creates game window
     * Sets up all game subsystems (HUD, guns, map, player)
     * @param width Physical window width in pixels
     * @param height Physical window height in pixels
     * @throws std::runtime_error if SDL initialization fails
     */
    Game(int width = 320, int height = 240);

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
    bool isGameOver();

    ~Game();
};

#endif
