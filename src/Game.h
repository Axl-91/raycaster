#ifndef __GAME__
#define __GAME__

#include "Guns.h"
#include "Hud.h"
#include "Map.h"
#include "Player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game {
  private:
    int largoReal = 320;
    int altoReal = 240;
    bool gameOver = false;
    int winLargo;
    int winAlto;
    Hud hudGame;
    Guns gunGame;
    Map mapGame;
    Player player;
    SDL_Window *window;
    SDL_Renderer *renderer;
    void exitPollEvent(SDL_Event &evento);
    void fill();

  public:
    Game(int largo = 320, int ancho = 240);
    void setFullScreen();
    void render();
    void pollEvent();
    bool isGameOver();
    SDL_Renderer *getRenderer();
    ~Game();
};

#endif