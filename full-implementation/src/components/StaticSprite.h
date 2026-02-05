#ifndef __STATIC_SPRITE__
#define __STATIC_SPRITE__

#include "Sprite.h"

class StaticSprite : public Sprite {
  private:
    int spriteCols = 1;
    int spacing = 0;
    int variantCount = 1;

  public:
    StaticSprite();

    /**
     * Load objects sprite sheet texture
     * @param path the path to the sprite sheet to load
     * @param spriteCols the amount of columns of the sprite sheet
     * @param transparent true if the sprite has a transparent background, false
     * otherwise
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture(SDL_Renderer *renderer, const char *path, int spriteCols);

    /**
     * Set the sprite from the sprite sheet to be used
     * @param spriteNum the number of the sprite to be used
     */
    void setSprite(int spriteNum);

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
     * Select which column of the sprite sheet to render
     * @param xOffset Column offset from the left edge of the sprite (in pixels)
     */
    void selectSpriteCol(int xOffset);

    void changeVariant() { this->nextSprite(); }
};

#endif
