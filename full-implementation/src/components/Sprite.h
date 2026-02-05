#ifndef __SPRITE__
#define __SPRITE__

#include "../utils/Constants.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
class Sprite {
  protected:
    int x = 0;
    int y = 0;

    SDL_Rect spriteRect = {x, y, BLOCK_SIZE, BLOCK_SIZE};
    SDL_Texture *texture;

    /**
     * Set the sprite as the next one on the sprite sheet
     */
    void nextSprite();

  public:
    Sprite();

    /**
     * Loads sprite sheet texture from file
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture(SDL_Renderer *renderer, const char *path);

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

    Sprite(const Sprite &copy) = delete;
    Sprite operator=(const Sprite &copy) = delete;

    ~Sprite();
};

#endif
