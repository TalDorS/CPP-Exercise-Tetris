#ifndef __POINT_H
#define __POINT_H

class Point
{
	int xValue;
	int yValue;
public:
	//empty c-tor for a Point object
	Point() : xValue(0), yValue(0) {};
	Point(const int _xValue, const int _yValue) : xValue(_xValue), yValue(_yValue) {};


	// Set Methods
	void setXYValues(int xValue, int yValue);
	void setXValue(int xValue);
	void setYValue(int yValue);

	// Get Methods
	int getX() const;
	int getY() const;

	// This method checks if the point's x and y equals to the given x and y
	bool isEqual(int xValue, int yValue) const;
};

#endif