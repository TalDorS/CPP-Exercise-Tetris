#include "Point.h"

void Point::setXYValues(int xValue, int yValue) {
	setXValue(xValue);
	setYValue(yValue);
}

void Point::setXValue(int xValue) {
	this->xValue = xValue;
}

void Point::setYValue(int yValue) {
	this->yValue = yValue;
}

bool Point::isEqual(int xValue, int yValue) {
	if ((this->xValue) == xValue && (this->yValue == yValue))
		return true;
	return false;
}

int Point::getX() {
	return this->xValue;
}

int Point::getY() {
	return this->yValue;
}