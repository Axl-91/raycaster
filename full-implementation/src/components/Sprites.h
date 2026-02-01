#ifndef __SPRITES__
#define __SPRITES__

#include "../utils/Constants.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
class Sprites {
  private:
    int x = 0;
    int y = 0;

    int spriteCols;
    int spacing = 0;
    int variantCount = 1;

    SDL_Rect spriteRect = {x, y, BLOCK_SIZE, BLOCK_SIZE};
    SDL_Texture *texture;

  public:
    Sprites();

    /**
     * Load objects sprite sheet texture
     * @param path the path to the sprite sheet to load
     * @param spriteCols the amount of columns of the sprite sheet
     * @param transparent true if the sprite has a transparent background, false
     * otherwise
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture(SDL_Renderer *renderer, const char *path, int spriteCols,
                     bool transparent);

    /**
     * Set the horizontal spacing between sprites in the sprite sheet
     * to prevent texture bleeding during rendering
     * @param separator Pixel spacing between sprites
     */
    void setSpacing(int spacing) { this->spacing = spacing; }

    /**
     * Set how many variants each sprite has
     * Walls have 2 variants (light + dark), objects have 1
     * @param variantCount Number of sprite variants
     */
    void setVariantCount(int variantCount) {
        this->variantCount = variantCount;
    }

    /**
     * Set the sprite from the sprite sheet to be used
     * @param spriteNum the number of the sprite to be used
     */
    void setSprite(int spriteNum);

    /**
     * Set the sprite as the next one on the sprite sheet
     */
    void nextSprite();

    /**
     * Select which column of the sprite sheet to render
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
