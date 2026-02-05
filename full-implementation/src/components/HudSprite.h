#ifndef __TEXTURE_HUD__
#define __TEXTURE_HUD__

#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

class HudSprite : public Sprite {
  private:
    static constexpr int HUD_WIDTH = 320;
    static constexpr int HUD_HEIGHT = 40;

    static constexpr int HUD_GUN_WIDTH = 48;
    static constexpr int HUD_GUN_HEIGHT = 23;

    static constexpr int HUD_GUN_X = 255;
    static constexpr int HUD_GUN_Y = 210;

    const SDL_Rect srcHud = {0, 0, HUD_WIDTH, HUD_HEIGHT};
    SDL_Rect srcGun = {0, 42, HUD_GUN_WIDTH, HUD_GUN_HEIGHT};

    int offsetGun = 49;

  public:
    HudSprite();

    /**
     * Handles keyboard input for gun selection on HUD
     * Keys 1-4 select different guns
     */
    void pollEvent(SDL_Event &event);

    /**
     * Render the HUD sprite to the screen
     */
    void render(SDL_Renderer *renderer) const;
};

#endif
