#ifndef __TEXTURE_GUNS__
#define __TEXTURE_GUNS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define GUN_WIDTH 128
#define GUN_HEIGHT 128

#define FRAMES_MAX 4

class Guns {
  private:
    SDL_Rect srcGun = {0, 0, 64, 64};
    int offset = 65;
    int auxNum = 0;
    bool isShooting = false;
    SDL_Texture *texture;
    SDL_Renderer *winRenderer;
    void loadTexture();
    void shoot();

  public:
    Guns();
    Guns(const Guns &copy) = delete;
    Guns &operator=(const Guns &copy) = delete;
    void setRenderer(SDL_Renderer *renderer);
    void pollEvent(SDL_Event &event);
    bool getIsShooting();
    void render();
    ~Guns();
};

#endif
