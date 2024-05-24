#pragma once
#include "SDL.h"
#include "Board.h"

class Game
{
public:
	Game();

	void init(const char* title, int width, int height);
	void clean();

	void render();
	void eventHandler(Board* board);

	bool running();
	SDL_Renderer* getRenderer();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunning;
};

