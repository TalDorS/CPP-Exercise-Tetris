#include "Tetromino.h"

void Tetromino::setXCoordinates(int x1, int x2, int x3, int x4) {
	xCoordinates[0] = x1;
	xCoordinates[1] = x2;
	xCoordinates[2] = x3;
	xCoordinates[3] = x4;
}
void Tetromino::setYCoordinates(int y1, int y2, int y3, int y4) {
	yCoordinates[0] = y1;
	yCoordinates[1] = y2;
	yCoordinates[2] = y3;
	yCoordinates[3] = y4;
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
	for (int i = 0; i < 4; i++) {
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