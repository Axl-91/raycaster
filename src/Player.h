#ifndef __PLAYER__
#define __PLAYER__

#include "Map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define PI 3.14159265358979323846

static constexpr float MOVE_SPEED = 3.0f;
static constexpr float ROTATION_SPEED = PI / 36;

class Player {
  private:
    float posX;
    float posY;
    float angle = 0;

    float dx = 5 * cos(angle);
    float dy = 5 * sin(angle);
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
