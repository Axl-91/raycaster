#ifndef __PLAYER__
#define __PLAYER__

#include "Map.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Player {
  private:
    static constexpr float MOVE_SPEED = 3.0f;
    static constexpr float ROTATION_SPEED = PI / 36;

    float posX;
    float posY;
    float angle = 0;
    float distBuffer[320];
    Map mapPlayer;
    SDL_Renderer *rendererPlayer;

    void moveForward();
    void moveBackward();
    void rotateLeft();
    void rotateRight();

    void renderRaycaster();
    bool objIsVisible(Vector &posObj);
    void renderObjects();

  public:
    Player();
    void setPos(float x, float y);
    void setMap(Map &map);
    void setRenderer(SDL_Renderer *renderer);
    void handleMovement();
    void render();
    ~Player();
};

#endif
