#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    Game game(640, 480);
    // game.setFullScreen();

    while (!game.isGameOver()) {
        game.pollEvent();
        game.update();
        game.render();

        SDL_Delay(16);
    }

    return 0;
}
