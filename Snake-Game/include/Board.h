#pragma once
#include "Cell.h"
#include "Snake.h"
#include "Food.h"
#include "SDL.h"

class Board:public Cell
{
private:
	Cell board[10][10];
	Snake* snakeHead;

	SDL_Rect* square;
	SDL_Renderer* boardRenderer;

	char snakeDirection;

	Food* food;

	bool isAlive;
	int score;
public:
	Board(SDL_Renderer* renderer);

	void renderBoard();

	void updateBoard(Snake* snakeList);
	Snake* getSnakeHead();

	void changeDirection(char dir);
	void changeSnakeHeadDirection();

	bool isFoodOnPath(Food* food);
	void createFood(Food* food);

	bool isSnakeAlive();
	int getScore();
};

