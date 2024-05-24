#include <iostream>
#include <cstdlib>
#include <time.h>
#include "SDL.h"
#include "Game.h"
#include "Board.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int FPS = 5;
	const int FRAME_DELAY = 1000 / FPS;

	Uint64 frameStart;
	int frameTime;

	Game* game = new Game();
	game->init("Snake", 250, 250);

	Board* board = new Board(game->getRenderer());

	while (game->running()) {
		frameStart = SDL_GetTicks64();

		game->eventHandler(board);
		board->changeSnakeHeadDirection();
		board->updateBoard(board->getSnakeHead());
		board->renderBoard();

		if (!board->isSnakeAlive()) {
			delete board;
			board = new Board(game->getRenderer());
		}

		frameTime = SDL_GetTicks64() - frameStart;
		if (FRAME_DELAY > frameTime) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	game->clean();
	return 0;
}