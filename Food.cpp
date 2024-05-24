#include "Food.h"
#include "Cell.h"
#include <cstdlib>

Food::Food() {
	x = 0;
	y = 0;
	setCell(2);
}

void Food::setFood() {
	x = rand() % 10;
	y = rand() % 10;
}

int Food::getFoodXPos() {
	return x;
}

int Food::getFoodYPos() {
	return y;
}