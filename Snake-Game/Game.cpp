#include "Game.h"
#include <iostream>
#include "SDL.h"
#include "Game.h"
#include "Board.h"

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	isRunning = true;
}

void Game::init(const char* title, int width, int height) {
	isRunning = false;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

		if (window) {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
			if (renderer) {
				isRunning = true;				
			}
			else
			{
				std::cout << "Failed to create renderer!" << std::endl;
			}
		}
		else {
			std::cout << "Failed to create window!" << std::endl;
		}
	}
	else {
		std::cout << "Failed to initialize SDL_VIDEO!" << std::endl;
	}
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	std::cout << "Game cleaned!" << std::endl;
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 150, 0, 255);
	SDL_RenderPresent(renderer);
}

void Game::eventHandler(Board* board) {
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				board->changeDirection('u');
				break;
			case SDLK_DOWN:
				board->changeDirection('d');
				break;
			case SDLK_LEFT:
				board->changeDirection('l');
				break;
			case SDLK_RIGHT:
				board->changeDirection('r');
				break;
			}
			
		}
	}
}

bool Game::running() {
	return isRunning;
}

SDL_Renderer* Game::getRenderer() {
	return renderer;
}
