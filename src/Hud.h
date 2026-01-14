#ifndef __TEXTURE_HUD__
#define __TEXTURE_HUD__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Largo y alto del HUD
#define HUDL 320
#define HUDA 40
//Largo y alto del arma en HUD
#define HGUNL 48
#define HGUNA 23

class Hud{
private:
    const SDL_Rect srcHud = {0, 0, HUDL, HUDA};
    SDL_Rect srcGun = {0, 42, HGUNL, HGUNA};
    int offsetGun = 49;
    SDL_Rect srcNumber = {0, 0, 0, 0};
    SDL_Rect srcKey = {0, 0, 0, 0};
    SDL_Texture* textura;
    SDL_Renderer* winRenderer;
    void getTexture();
public:
    Hud();
	Hud(const Hud &copy) = delete;
	Hud operator=(const Hud &copy) = delete;
    void setRenderer(SDL_Renderer* renderer);
    void pollEvent(SDL_Event &evento);
    void renderHud(int posX, int posY);
    void renderGun(int posX, int posY);
    void renderKey(int posX, int posY);
    ~Hud();
};

#endif