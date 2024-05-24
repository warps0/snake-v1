#pragma once
class Cell
{
private:
	//type: 0 - empty, 1 - snake body, 2 - food
	int type;
public:
	Cell();

	void setCell(int isType);
	int getCell();
};

