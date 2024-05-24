#pragma once
#include "Cell.h"
class Snake:public Cell
{
private:
	int x;
	int y;

	Snake* snakeNode;
public:
	Snake(int inX, int inY, Snake* toNode);

	void setSnakePos(int inX,int inY);
	int getSnakeXPos();
	int getSnakeYPos();
	Snake* getSnakeNextNode();

	void growSnake();
	void moveSnake(int inX, int inY);

	void printSnake(Snake* head);
};

