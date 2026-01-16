#include "Game.h"
#include "Guns.h"
#include "Hud.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

Game::Game(int width, int height) {
    this->winWidth = width;
    this->winHeight = height;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init failed: ") +
                                 SDL_GetError());
    }

    if (SDL_CreateWindowAndRenderer(this->winWidth, this->winHeight,
                                    SDL_RENDERER_ACCELERATED, &this->window,
                                    &this->renderer) != 0) {
        SDL_Quit();
        throw std::runtime_error(std::string("Window creation failed: ") +
                                 SDL_GetError());
    }

    SDL_SetWindowTitle(this->window, "WOLFENSTEIN 3D");
    SDL_RenderSetLogicalSize(this->renderer, this->realWidth, this->realHeight);

    this->hud.setRenderer(this->renderer);
    this->gun.setRenderer(this->renderer);
    this->map.setRenderer(this->renderer);

    // TODO: Fix magic numbers
    this->player.setPos(96, 96);
    this->player.setMap(this->map);
    this->player.setRenderer(this->renderer);
}

void Game::setFullScreen() {
    SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
}

void Game::fill() {
    static constexpr SDL_Color FLOOR_COLOR = {0x80, 0x80, 0x80, 0xFF};
    static constexpr SDL_Color CEILING_COLOR = {0x33, 0x33, 0x33, 0xFF};

    // Fill all screen with the FLOOR_COLOR
    SDL_SetRenderDrawColor(this->renderer, FLOOR_COLOR.r, FLOOR_COLOR.g,
                           FLOOR_COLOR.b, FLOOR_COLOR.a);
    SDL_RenderClear(this->renderer);

    // TODO: The 40 is the height of the HUD, change it, no magic numbers
    SDL_Rect ceilingRect = {0, 0, this->realWidth, (this->realHeight - 40) / 2};

    // Render CEILING_COLOR on the top half of the screen
    SDL_SetRenderDrawColor(this->renderer, CEILING_COLOR.r, CEILING_COLOR.g,
                           CEILING_COLOR.b, CEILING_COLOR.a);
    SDL_RenderFillRect(this->renderer, &ceilingRect);
}

void Game::exitPollEvent(SDL_Event &event) {
    if (event.type == SDL_QUIT) {
        this->gameOver = true;
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        gameOver = true;
    }
}

void Game::pollEvent() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        exitPollEvent(event);
        this->gun.pollEvent(event);

        if (!this->gun.isShooting()) {
            this->hud.pollEvent(event);
        }
    }
}

void Game::handleMovement() { player.handleMovement(); }

void Game::render() {
    // Draw ceiling and floor colors
    fill();

    // render sprites
    this->player.render();
    this->gun.render();
    this->hud.renderHud(this->realWidth, this->realHeight);
    this->hud.renderGun(this->realWidth, this->realHeight);

    SDL_RenderPresent(this->renderer);
}

bool Game::isGameOver() { return this->gameOver; }

Game::~Game() {
    if (this->renderer) {
        SDL_DestroyRenderer(renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }

    SDL_Quit();
}
