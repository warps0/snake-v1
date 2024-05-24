#include "Board.h"
#include "Cell.h"
#include "Snake.h"
#include "Food.h"
#include <cstdlib>
#include <iostream>

Board::Board(SDL_Renderer* renderer) {
	int sX, sY;
	boardRenderer = renderer;

	square = new SDL_Rect();
	square->w = 25;
	square->h = 25;
	
	snakeDirection = '-';

	sX = rand() % 10;
	sY = rand() % 10;

	snakeHead = new Snake(sX, sY, nullptr);

	food = new Food();
	createFood(food);

	isAlive = true;
	score = 0;
}

void Board::renderBoard() {
	//SDL_RenderClear(boardRenderer);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (board[i][j].getCell())
			{
			case 0:
				SDL_SetRenderDrawColor(boardRenderer, 255, 150, 0, 255);
				break;
			case 1:
				SDL_SetRenderDrawColor(boardRenderer, 0, 0, 0, 255);
				break;
			case 2:
				SDL_SetRenderDrawColor(boardRenderer, 255, 0, 0, 255);
				break;
			}

			square->x = j * 25;
			square->y = i * 25;

			SDL_RenderFillRect(boardRenderer, square);
			SDL_RenderPresent(boardRenderer);
		}
	}
}

void Board::updateBoard(Snake* snakeList) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j].getCell() != 2) {
				board[i][j].setCell(0);
			}
		}
	}

	while (snakeList) {
		board[snakeList->getSnakeYPos()][snakeList->getSnakeXPos()].setCell(1);
		snakeList = snakeList->getSnakeNextNode();
	}
}

Snake* Board::getSnakeHead() {
	return snakeHead;
}

void Board::changeDirection(char dir) {
	if (snakeDirection == 'u' && dir != 'd') {
		snakeDirection = dir;
	}
	else if (snakeDirection == 'd' && dir != 'u') {
		snakeDirection = dir;
	}
	else if (snakeDirection == 'l' && dir != 'r') {
		snakeDirection = dir;
	}
	else if (snakeDirection == 'r' && dir != 'l') {
		snakeDirection = dir;
	}
	else {
		snakeDirection = dir;
	}
}

void Board::changeSnakeHeadDirection() {
	switch (snakeDirection)
	{
	case 'u':
		if (snakeHead->getSnakeYPos() > 0) {
			if (!board[snakeHead->getSnakeYPos() - 1][snakeHead->getSnakeXPos()].getCell()) {
				snakeHead->moveSnake(snakeHead->getSnakeXPos(), snakeHead->getSnakeYPos() - 1);
			}
			else if (board[snakeHead->getSnakeYPos() - 1][snakeHead->getSnakeXPos()].getCell() == 2) {
				board[snakeHead->getSnakeXPos()][snakeHead->getSnakeYPos() - 1].setCell(0);
				snakeHead->growSnake();
				snakeHead->setSnakePos(snakeHead->getSnakeXPos(), snakeHead->getSnakeYPos() - 1);

				score++;
				createFood(food);
			}
			else {
				isAlive = false;
			}
		}
		else {
			isAlive = false;
		}
		break;
	case 'd':
		if (snakeHead->getSnakeYPos() < 9) {
			if (!board[snakeHead->getSnakeYPos() + 1][snakeHead->getSnakeXPos()].getCell()) {
				snakeHead->moveSnake(snakeHead->getSnakeXPos(), snakeHead->getSnakeYPos() + 1);
			}
			else if (board[snakeHead->getSnakeYPos() + 1][snakeHead->getSnakeXPos()].getCell() == 2) {
				board[snakeHead->getSnakeXPos()][snakeHead->getSnakeYPos() + 1].setCell(0);
				snakeHead->growSnake();
				snakeHead->setSnakePos(snakeHead->getSnakeXPos(), snakeHead->getSnakeYPos() + 1);
			
				score++;
				createFood(food);
			}
			else {
				isAlive = false;
			}
		}
		else {
			isAlive = false;
		}
		break;
	case 'l':
		if (snakeHead->getSnakeXPos() > 0) {
			if (!board[snakeHead->getSnakeYPos()][snakeHead->getSnakeXPos() - 1].getCell()) {
				snakeHead->moveSnake(snakeHead->getSnakeXPos() - 1, snakeHead->getSnakeYPos());
			}
			else if (board[snakeHead->getSnakeYPos()][snakeHead->getSnakeXPos() - 1].getCell() == 2) {
				board[snakeHead->getSnakeXPos() - 1][snakeHead->getSnakeYPos()].setCell(0);
				snakeHead->growSnake();
				snakeHead->setSnakePos(snakeHead->getSnakeXPos() - 1, snakeHead->getSnakeYPos());
			
				score++;
				createFood(food);
			}
			else {
				isAlive = false;
			}
		}
		else {
			isAlive = false;
		}
		break;
	case 'r':
		if (snakeHead->getSnakeXPos() < 9) {
			if (!board[snakeHead->getSnakeYPos()][snakeHead->getSnakeXPos() + 1].getCell()) {
				snakeHead->moveSnake(snakeHead->getSnakeXPos() + 1, snakeHead->getSnakeYPos());
			}
			else if (board[snakeHead->getSnakeYPos()][snakeHead->getSnakeXPos() + 1].getCell() == 2) {
				board[snakeHead->getSnakeXPos() + 1][snakeHead->getSnakeYPos()].setCell(0);
				snakeHead->growSnake();
				snakeHead->setSnakePos(snakeHead->getSnakeXPos() + 1, snakeHead->getSnakeYPos());
			
				score++;
				createFood(food);
			}
			else {
				isAlive = false;
			}
		}
		else {
			isAlive = false;
		}
		break;
	}
}

bool Board::isFoodOnPath(Food* food) {
	bool isOnPath = false;
	Snake* snakeList = snakeHead;

	while (snakeList && !isOnPath) {
		if (snakeList->getSnakeXPos() == food->getFoodXPos() && snakeList->getSnakeYPos() == food->getFoodYPos()) {
			isOnPath = true;
		}
		snakeList = snakeList->getSnakeNextNode();
	}

	return isOnPath;
}

void Board::createFood(Food* food) {
	food->setFood();
	while (isFoodOnPath(food)) {
		food->setFood();
	}

	board[food->getFoodYPos()][food->getFoodXPos()].setCell(2);
}

bool Board::isSnakeAlive() {
	return isAlive;
}

int Board::getScore() {
	return score;
}