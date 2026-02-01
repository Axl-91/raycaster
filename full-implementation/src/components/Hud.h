#ifndef __TEXTURE_HUD__
#define __TEXTURE_HUD__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

class Hud {
  private:
    static constexpr int HUD_WIDTH = 320;
    static constexpr int HUD_HEIGHT = 40;
    static constexpr int HUD_GUN_WIDTH = 48;
    static constexpr int HUD_GUN_HEIGHT = 23;

    const SDL_Rect srcHud = {0, 0, HUD_WIDTH, HUD_HEIGHT};
    SDL_Rect srcGun = {0, 42, HUD_GUN_WIDTH, HUD_GUN_HEIGHT};
    int offsetGun = 49;
    SDL_Rect srcNumber = {0, 0, 0, 0};
    SDL_Rect srcKey = {0, 0, 0, 0};
    SDL_Texture *texture;

  public:
    Hud();

    /**
     * Load hud sprite sheet texture from file
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture(SDL_Renderer *renderer);

    /**
     * Handles keyboard input for gun selection on HUD
     * Keys 1-4 select different guns
     */
    void pollEvent(SDL_Event &event);

    /**
     * Render the HUD sprite to the screen
     */
    void renderHud(SDL_Renderer *renderer) const;

    Hud(const Hud &copy) = delete;
    Hud operator=(const Hud &copy) = delete;

    ~Hud();
};

#endif
