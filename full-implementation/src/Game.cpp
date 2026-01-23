#include "Game.h"
#include "Constants.h"
#include "Player.h"
#include "Raycaster.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

Game::Game(int width, int height)
    : winWidth(width), winHeight(height), map(),
      player(INIT_POS_X, INIT_POS_Y, this->map),
      raycaster(this->player, this->map),
      gameRenderer(this->map, this->player, this->raycaster) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init failed: ") +
                                 SDL_GetError());
    }

    if (SDL_CreateWindowAndRenderer(this->winWidth, this->winHeight,
                                    SDL_RENDERER_ACCELERATED, &this->window,
                                    &this->sdlRenderer) != 0) {
        SDL_Quit();
        throw std::runtime_error(std::string("Window creation failed: ") +
                                 SDL_GetError());
    }

    SDL_SetWindowTitle(this->window, "WOLFENSTEIN 3D");
    SDL_RenderSetLogicalSize(this->sdlRenderer, this->realWidth,
                             this->realHeight);

    this->gameRenderer.setRenderer(this->sdlRenderer);
}

void Game::setFullScreen() {
    SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
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
        this->gameRenderer.getGun().pollEvent(event);

        if (!this->gameRenderer.getGun().isShooting()) {
            this->gameRenderer.getHud().pollEvent(event);
        }
    }
}

void Game::update() {
    this->player.handleMovement();
    this->gameRenderer.getGun().handleShooting();
}

void Game::render() { this->gameRenderer.render(); }

bool Game::isGameOver() const { return this->gameOver; }

Game::~Game() {
    if (this->sdlRenderer) {
        SDL_DestroyRenderer(sdlRenderer);
        this->sdlRenderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }

    SDL_Quit();
}
