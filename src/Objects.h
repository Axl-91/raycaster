#ifndef __TEXTURE_OBJECTS__
#define __TEXTURE_OBJECTS__

#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Objects {
  private:
    static constexpr int SPRITE_SIZE = 64;
    static constexpr int SPRITE_COLS = 5;
    static constexpr int SPRITE_BORDER = 1;

    int objX = 0;
    int objY = 0;
    SDL_Rect objRect = {objX, objY, SPRITE_SIZE, SPRITE_SIZE};
    SDL_Texture *texture;
    SDL_Renderer *renderer;

    /**
     * Load objects sprite sheet texture from file
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture();

  public:
    Objects();

    /**
     * Set renderer for the Object and initialize texture
     * @param renderer SDL renderer to use for creating textures
     */
    void setRenderer(SDL_Renderer *renderer);

    /**
     * Set the object from the sprite sheet to be used
     * @param objNum the number of the object to be used
     */
    void setObject(int objNum);

    /**
     * Select which column of the sprite sheet to render
     * Used for vertical slice rendering in raycasting (1 pixel wide columns)
     * @param xOffset Column offset from the left edge of the sprite (in pixels)
     */
    void selectSpriteCol(int xOffset);

    /**
     * Render the sprite to the screen at specified position
     * @param x Screen X coordinate where sprite will be drawn
     * @param y Screen Y coordinate where sprite will be drawn
     * @param width Width of the rendered sprite in pixels (default:
     * SPRITE_SIZE)
     * @param height Height of the rendered sprite in pixels (default:
     * SPRITE_SIZE)
     */
    void render(int x, int y, int width = SPRITE_SIZE,
                int height = SPRITE_SIZE);

    ~Objects();
};

#endif
