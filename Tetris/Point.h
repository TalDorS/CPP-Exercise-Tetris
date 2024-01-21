#ifndef __POINT_H
#define __POINT_H

class Point
{
	int xValue;
	int yValue;
public:
	// Set Methods
	void setXYValues(int xValue, int yValue);
	void setXValue(int xValue);
	void setYValue(int yValue);

	// Get Methods
	int getX();
	int getY();

	// This method checks if the point's x and y equals to the given x and y
	bool isEqual(int xValue, int yValue);
};

#endif