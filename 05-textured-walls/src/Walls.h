#ifndef __TEXTURE_WALLS__
#define __TEXTURE_WALLS__

#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

class Walls {
  private:
    // This offset is created because the walls have light/dark sprites
    static constexpr int OFFSET_WALL = 2;
    static constexpr int SPRITE_COLS = 3;

    int wallX = 0;
    int wallY = 0;
    SDL_Rect wallRect = {wallX, wallY, BLOCK_SIZE, BLOCK_SIZE};
    SDL_Texture *texture;

  public:
    Walls();

    /**
     * Load wall sprite sheet texture from file
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture(SDL_Renderer *renderer);

    /**
     * Set the wall from the sprite sheet to be used
     * if isDark is true we change the sprite to the dark variant
     * @param numWall the number of the wall to be used
     */
    void setWall(int numWall, bool isDark);

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
    void render(SDL_Renderer *renderer, int x, int y, int width,
                int height) const;

    Walls(const Walls &copy) = delete;
    Walls operator=(const Walls &copy) = delete;

    ~Walls();
};

#endif
