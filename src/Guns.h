#ifndef __TEXTURE_GUNS__
#define __TEXTURE_GUNS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define GUN_WIDTH 128
#define GUN_HEIGHT 128

#define FRAMES_MAX 4
#define SPEED_FRAMES 18

class Guns {
  private:
    SDL_Rect srcGun = {0, 0, 64, 64};
    int offset = 65;
    int auxNum = 0;
    bool shooting = false;
    SDL_Texture *texture;
    SDL_Renderer *winRenderer;

    /**
     * Load gun sprite sheet texture from file
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTexture();

  public:
    Guns();
    Guns(const Guns &copy) = delete;
    Guns &operator=(const Guns &copy) = delete;

    /**
     * Set renderer for the Gun Object and initialize texture
     * @param renderer SDL renderer to use for creating textures
     */
    void setRenderer(SDL_Renderer *renderer);

    /**
     * Handles keyboard input for gun selection and shooting
     * Keys 1-4 select different guns, Space initiates shooting
     */
    void pollEvent(SDL_Event &event);

    /**
     * Handle continuous shooting input
     * Checks if Space is held and starts new shooting animation when ready
     */
    void handleShooting();

    /**
     * @return true if gun is currently shooting, false otherwise
     */
    bool isShooting();

    /**
     * Render the gun sprite to the screen
     * Handles shooting animation by cycling through sprite frames
     */
    void render();

    ~Guns();
};

#endif
