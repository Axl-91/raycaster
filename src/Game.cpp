#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Hud.h"
#include "Guns.h"
#include "Map.h"

Game::Game(int largo, int alto){
    int hayError;
    winLargo = largo;
    winAlto = alto;
    const char* title = "WOLFENSTEIN 3D";

	hayError = SDL_Init(SDL_INIT_VIDEO);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	hayError = SDL_CreateWindowAndRenderer(winLargo, winAlto, 
		SDL_RENDERER_ACCELERATED, &window, &renderer);
	if (hayError){
		std::cout << "ERROR : " << SDL_GetError()  << std::endl;
	}

	SDL_SetWindowTitle(window, title);
	SDL_RenderSetLogicalSize(renderer, largoReal, altoReal);

	hudGame.setRenderer(renderer);
	gunGame.setRenderer(renderer);
	mapGame.setRenderer(renderer);
	player.setPos(96,96);
	player.setMap(mapGame);
	player.setRenderer(renderer);
}

void Game::setFullScreen(){
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Game::fill(){
    /*Dibuja la pantalla en gris claro y luego dibuja
    desde la mitad para arriba en gris oscuro */
	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderClear(renderer);

    SDL_Rect rect = {0,0, largoReal, (altoReal-40)/2};
	SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
}

void Game::exitPollEvent(SDL_Event &evento){
	if (evento.type == SDL_QUIT){
		gameOver = true;
	}
	if (evento.type == SDL_KEYDOWN){
		switch(evento.key.keysym.sym){
			case SDLK_ESCAPE:
				gameOver = true;
		}
	}
}

void Game::pollEvent(){
    SDL_Event evento;

	if (SDL_PollEvent(&evento)){
		//POLL EVENT PLAYER
		exitPollEvent(evento);
		gunGame.pollEvent(evento);
		if (!gunGame.estaEnAccion()){
			hudGame.pollEvent(evento);
		}
		player.pollEvent(evento);
	}
}

void Game::render(){
	fill();
	player.render();
	//RENDER DE SPRITES
	gunGame.render(320, 240);
	hudGame.renderHud(320, 240);
	hudGame.renderGun(320,240);
    SDL_RenderPresent(renderer);
}

bool Game::isGameOver(){
	return gameOver;
}

SDL_Renderer* Game::getRenderer(){
	return renderer;
}

Game::~Game(){
	if (renderer){
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window){
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	SDL_Quit();
}
