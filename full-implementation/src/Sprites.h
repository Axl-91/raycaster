#ifndef __SPRITES__
#define __SPRITES__

#include "Constants.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
class Sprites {
  private:
    int x;
    int y;

    int spriteCols;
    int offset;

    SDL_Rect spriteRect = {x, y, BLOCK_SIZE, BLOCK_SIZE};
    SDL_Texture *texture;

  public:
    Sprites();

    /**
     * Load objects sprite sheet texture from file with the columns and the
     * offset given
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture(SDL_Renderer *renderer, int spriteCols, int offset);

    /**
     * Set the object from the sprite sheet to be used
     * @param objNum the number of the object to be used
     */
    void setSprite(int SpriteNum);

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
     * BLOCK_SIZE)
     * @param height Height of the rendered sprite in pixels (default:
     * BLOCK_SIZE)
     */
    void render(SDL_Renderer *renderer, int x, int y, int width = BLOCK_SIZE,
                int height = BLOCK_SIZE) const;

    Sprites(const Sprites &copy) = delete;
    Sprites operator=(const Sprites &copy) = delete;

    ~Sprites();
};

#endif
