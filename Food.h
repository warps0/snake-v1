#pragma once
#include "Cell.h"
#include "Snake.h"
#include <cstdlib>

class Food:public Cell
{
private:
	int x;
	int y;
public:
	Food();

	void setFood();
	int getFoodXPos();
	int getFoodYPos();
};

