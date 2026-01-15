#ifndef __TEXTURE_HUD__
#define __TEXTURE_HUD__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Width and height of the HUD
#define HUD_WIDTH 320
#define HUD_HEIGTH 40

// Largo y alto del arma en HUD
#define HUD_GUN_WIDTH 48
#define HUD_GUN_HEIGHT 23

class Hud {
  private:
    const SDL_Rect srcHud = {0, 0, HUD_WIDTH, HUD_HEIGTH};
    SDL_Rect srcGun = {0, 42, HUD_GUN_WIDTH, HUD_GUN_HEIGHT};
    int offsetGun = 49;
    SDL_Rect srcNumber = {0, 0, 0, 0};
    SDL_Rect srcKey = {0, 0, 0, 0};
    SDL_Texture *texture;
    SDL_Renderer *winRenderer;

    /**
     * Load hud sprite sheet texture from file
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture();

  public:
    Hud();

    Hud(const Hud &copy) = delete;
    Hud operator=(const Hud &copy) = delete;

    /**
     * Set renderer for the Hud Object and initialize texture
     * @param renderer SDL renderer to use for creating textures
     */
    void setRenderer(SDL_Renderer *renderer);

    /**
     * Handles keyboard input for gun selection on HUD
     * Keys 1-4 select different guns
     */
    void pollEvent(SDL_Event &event);

    /**
     * Render the HUD sprite to the screen
     */
    void renderHud(int winWidth, int winHeight);

    /**
     * Render the gun sprite on the hud to the screen
     */
    void renderGun(int winWidth, int winHeight);

    ~Hud();
};

#endif
