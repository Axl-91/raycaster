#ifndef __TEXTURE_OBJECTS__
#define __TEXTURE_OBJECTS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector.h"
#define LADO 64

class Objects{
private:
    int srcX = 0;
    int srcY = 0;
    int offset = 65;
    SDL_Rect src = {srcX, srcY, LADO, LADO};
    SDL_Texture* textura;
    SDL_Renderer* rendererWin;
    void getTexture();
    void setSrc(int x, int y, int largo, int alto);
public:
    Objects();
    void setRenderer(SDL_Renderer* renderer);
    void setObject(int num);
    void recortar(int x, int y, int largo = LADO, int alto = LADO);
    void render(int x, int y, int largo = LADO, int alto = LADO);
    ~Objects();
};

#endif