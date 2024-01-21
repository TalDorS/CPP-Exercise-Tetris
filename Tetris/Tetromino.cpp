#include "Tetromino.h"

#define DEFAULT_VALUE 0
#define NUM_OF_COORDINATES 4
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define FOURTH 3

void Tetromino::setXCoordinates(int x1, int x2, int x3, int x4) {
	points[FIRST].setXValue(x1);
	points[SECOND].setXValue(x2);
	points[THIRD].setXValue(x3);
	points[FOURTH].setXValue(x4);
}

void Tetromino::setYCoordinates(int y1, int y2, int y3, int y4) {
	points[FIRST].setYValue(y1);
	points[SECOND].setYValue(y2);
	points[THIRD].setYValue(y3);
	points[FOURTH].setYValue(y4);
}

void Tetromino::setShape(int shape) {
	this->shape = shape;
}

int Tetromino::getShape() {
	return shape;
}

int Tetromino::getXCoordinate(int index) {
	return points[index].getX();
}

int Tetromino::getYCoordinate(int index) {
	return points[index].getY();
}

bool Tetromino::isContainCoordinates(int y, int x) {
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		if (points[i].isEqual(x, y))
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
	points[index].setXValue(x);
}

void Tetromino::setYCoordinate(int index, int y) {
	points[index].setYValue(y);
}







