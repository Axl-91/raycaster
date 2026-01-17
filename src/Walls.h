#ifndef __TEXTURE_WALLS__
#define __TEXTURE_WALLS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Walls {
  private:
    // This offset is created because the walls have light/dark sprites
    static constexpr int OFFSET_WALL = 2;
    static constexpr int SPRITE_SIZE = 64;
    static constexpr int SPRITE_COLS = 3;

    int wallX = 0;
    int wallY = 0;
    SDL_Rect wallRect = {wallX, wallY, SPRITE_SIZE, SPRITE_SIZE};
    SDL_Texture *texture;
    SDL_Renderer *renderer;

    /**
     * Load wall sprite sheet texture from file
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture();

  public:
    Walls();

    /**
     * Set renderer for the Wall and initialize texture
     * @param renderer SDL renderer to use for creating textures
     */
    void setRenderer(SDL_Renderer *renderer);

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
     * SPRITE_SIZE)
     * @param height Height of the rendered sprite in pixels (default:
     * SPRITE_SIZE)
     */
    void render(int x, int y, int width, int height);

    ~Walls();
};

#endif
