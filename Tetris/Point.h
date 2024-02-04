#ifndef __POINT_H
#define __POINT_H

class Point
{
	int xValue;
	int yValue;
public:
	//empty c-tor for a Point object
	Point(int x = 0, int y = 0) { x = xValue; y = yValue; }

	// Set Methods
	void setXYValues(int xValue, int yValue);
	void setXValue(int xValue);
	void setYValue(int yValue);

	// Get Methods
	int getX() const;
	int getY() const;

	// This method checks if the point's x and y equals to the given x and y
	bool isEqual(int xValue, int yValue)const;
};

#endif