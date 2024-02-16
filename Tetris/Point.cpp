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

bool Point::isEqual(int xValue, int yValue) const {
	if ((this->xValue) == xValue && (this->yValue == yValue))
		return true;
	return false;
}

int Point::getX() const {
	return this->xValue;
}

int Point::getY() const {
	return this->yValue;
}