#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "Game.h"

int main(int argc, char* argv[]){
	Game game(640, 480);
	//game.setFullScreen();

	while (!game.isGameOver()){
		game.pollEvent();
		game.render();
		sleep(1/60);
	}
	
	return 0;
}
