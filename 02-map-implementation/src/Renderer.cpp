#include "Renderer.h"

Renderer::Renderer(Player &player, Map &map) : player(player), map(map) {}

void Renderer::setRenderer(SDL_Renderer *renderer) {
    this->sdlRenderer = renderer;
}

void Renderer::clearScreen() {
    SDL_SetRenderDrawColor(this->sdlRenderer, 0, 0, 0, 0);
    SDL_RenderClear(this->sdlRenderer);
}

void Renderer::render() {
    clearScreen();

    this->map.render(this->sdlRenderer);
    this->player.render(this->sdlRenderer);

    SDL_RenderPresent(this->sdlRenderer);
}
