#ifndef __PLAYER__
#define __PLAYER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"

#define PI 3.14159265358979323846

class Player{
private:
    float posX;
    float posY;
    float angulo = 0;
    float dx = 5*cos(angulo);
    float dy = 5*sin(angulo);
    float distBuffer[320];
    Map mapPlayer;
    SDL_Renderer* rendererPlayer;
    void avanzar();
    void retroceder();
    void renderRaycaster();
    bool objEsVisible(Vector &posObj);
    void renderObjects();
public:
    Player();
    void setPos(float x, float y);
    void setMap(Map &map);
    void setRenderer(SDL_Renderer* renderer);
    void pollEvent(SDL_Event &evento);
    void render();
    ~Player();
};

#endif
