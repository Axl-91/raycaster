#ifndef __TEXTURE_GUNS__
#define __TEXTURE_GUNS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Largo y alto del arma
#define GUNL 128
#define GUNA 128

class Guns{
private:
    SDL_Rect srcGun = {0, 0, 64, 64};
    int offset = 65;
    int numAuxiliar = 0;
    bool estaDisparando = false;
    SDL_Texture* textura;
    SDL_Renderer* winRenderer;
    void getTexture();
    void disparar();
public:
    Guns();
	Guns(const Guns &copy) = delete;
	Guns operator=(const Guns &copy) = delete;
    void setRenderer(SDL_Renderer* renderer);
    void pollEvent(SDL_Event &evento);
    bool estaEnAccion();
    void render(int posX, int posY);
    ~Guns();
};

#endif