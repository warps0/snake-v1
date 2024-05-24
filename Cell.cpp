#include "Cell.h"

Cell::Cell() {
	type = 0;
}

void Cell::setCell(int isType) {
	type = isType;
}

int Cell::getCell() {
	return type;
}