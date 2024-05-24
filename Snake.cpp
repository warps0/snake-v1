#include "Snake.h"
#include "Cell.h"
#include <iostream>

Snake::Snake(int inX, int inY, Snake* toNode) {
	x = inX;
	y = inY;
	snakeNode = toNode;
	setCell(1);
}

//Not used
void Snake::setSnakePos(int inX, int inY) {
	x = inX;
	y = inY;
}

int Snake::getSnakeXPos() {
	return x;
}

int Snake::getSnakeYPos() {
	return y;
}

Snake* Snake::getSnakeNextNode() {
	return snakeNode;
}

/*
growSnake:
	It will create a new snake body node at the snake head position.
	Later the head will point to this new node.
	Head position has to be updated after the grow.
*/
void Snake::growSnake() {
	Snake* newNode = new Snake(x, y, snakeNode);
	snakeNode = newNode;
}

/*
moveSnake:
	It will iterate the snake list till last node.
	Then the snake body node position its updated with the previos node position recursively.
*/
void Snake::moveSnake(int inX,int inY) {
	if (getSnakeNextNode()) {
		snakeNode->moveSnake(x,y);
	}

	x = inX;
	y = inY;
}

//Debug tool
void Snake::printSnake(Snake* head) {
	while (head) {
		std::cout << head <<"-> x: " << head->x << " y:" << head->y << std::endl;
		head = head->snakeNode;
	}
}