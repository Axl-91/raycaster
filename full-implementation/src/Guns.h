#ifndef __TEXTURE_GUNS__
#define __TEXTURE_GUNS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

class Guns {
  private:
    static constexpr int GUN_WIDTH = 128;
    static constexpr int GUN_HEIGHT = 128;
    static constexpr int FRAMES_MAX = 4;
    static constexpr int ANIMATION_SPEED = 18;

    SDL_Rect srcGun = {0, 0, 64, 64};
    int offset = 65;
    int auxNum = 0;
    bool shooting = false;
    SDL_Texture *texture;

  public:
    Guns();

    /**
     * Load gun sprite sheet texture from file
     * @throws std::runtime_error if surface or texture creation fails
     */
    void loadTextures(SDL_Renderer *renderer);

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
    void render(SDL_Renderer *renderer);

    Guns(const Guns &copy) = delete;
    Guns operator=(const Guns &copy) = delete;

    ~Guns();
};

#endif
