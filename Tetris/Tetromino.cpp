#include "Tetromino.h"

#define DEFAULT_VALUE 0
#define NUM_OF_COORDINATES 4
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define FOURTH 3

//**1**
void Tetromino::setXCoordinates(int x1, int x2, int x3, int x4) {
	xCoordinates[FIRST] = x1;
	xCoordinates[SECOND] = x2;
	xCoordinates[THIRD] = x3;
	xCoordinates[FOURTH] = x4;
}
//**3**
void Tetromino::setYCoordinates(int y1, int y2, int y3, int y4) {
	yCoordinates[FIRST] = y1;
	yCoordinates[SECOND] = y2;
	yCoordinates[THIRD] = y3;
	yCoordinates[FOURTH] = y4;
}
//**6**
void Tetromino::setShape(int shape) {
	this->shape = shape;
}
//**7**
int* Tetromino::getXCoordinates() {
	return xCoordinates;
}
//**8**
int* Tetromino::getYCoordinates() {
	return yCoordinates;
}

bool Tetromino::isContainCoordinates(int y, int x) {
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		if (xCoordinates[i] == x && yCoordinates[i] == y)
			return true;
	}

	return false;
}

//**9**
bool Tetromino::getIsMoving() {
	return isMoving;
}

//**5**
void Tetromino::setIsMoving(bool state) {
	isMoving = state; 
}

//**2**
void Tetromino::setXCoordinate(int index, int x) {
	xCoordinates[index] = x;
}

//**4**
void Tetromino::setYCoordinate(int index, int y) {
	yCoordinates[index] = y;
}