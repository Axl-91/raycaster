#include "game/Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    Game game;

    while (!game.isGameOver()) {
        game.pollEvent();
        game.update();
        game.render();

        // ~60FPS
        SDL_Delay(GAME_DELAY);
    }

    return 0;
}
