#ifndef __TETROMINO_H
#define __TETROMINO_H

#include "Point.h"
#include <Vector>
#include <iostream>

#define DEFAULT_VALUE 0

using std::vector;

class Tetromino
{
	vector<Point> points;
	bool isMoving = false;
	int shape;

public:
	//here will be default empty c-tor for a Tetromino object by the compiler
	Tetromino() = default;

	// Set Methods
	void setXCoordinates(int x1, int x2, int x3, int x4);
	void setXCoordinate(int index, int x);
	void setYCoordinates(int y1, int y2, int y3, int y4);
	void setYCoordinate(int index, int y);
	void setIsMoving(bool state);
	void setShape(int shape);

	// Get Methods
	int getXCoordinate(int index) const;
	int getYCoordinate(int index) const;
	int getShape() const;
	bool getIsMoving() const;

	// This method checks if both x and y coordinate is in its arrays
	bool isContainCoordinates(int x, int y) const;
	
	// This function changes the size of points array
	void setPointsArraySize(const size_t size);

	// This function returns the size of points vector
	size_t getVecSize() const;

};

#endif