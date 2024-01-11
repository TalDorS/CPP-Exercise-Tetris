#include "Tetromino.h"

#define DEFAULT_VALUE 0
#define NUM_OF_COORDINATES 4
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define FOURTH 3

void Tetromino::setXCoordinates(int x1, int x2, int x3, int x4) {
	xCoordinates[FIRST] = x1;
	xCoordinates[SECOND] = x2;
	xCoordinates[THIRD] = x3;
	xCoordinates[FOURTH] = x4;
}
void Tetromino::setYCoordinates(int y1, int y2, int y3, int y4) {
	yCoordinates[FIRST] = y1;
	yCoordinates[SECOND] = y2;
	yCoordinates[THIRD] = y3;
	yCoordinates[FOURTH] = y4;
}

void Tetromino::setShape(int shape) {
	this->shape = shape;
}

int* Tetromino::getXCoordinates() {
	return xCoordinates;
}

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

bool Tetromino::getIsMoving() {
	return isMoving;
}

void Tetromino::setIsMoving(bool state) {
	isMoving = state; 
}

void Tetromino::setXCoordinate(int index, int x) {
	xCoordinates[index] = x;
}

void Tetromino::setYCoordinate(int index, int y) {
	yCoordinates[index] = y;
}