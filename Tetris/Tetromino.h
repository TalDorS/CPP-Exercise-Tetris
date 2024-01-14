#ifndef __TETROMINO_H
#define __TETROMINO_H

#define NUMBER_OF_COORDINATES 4

class Tetromino
{
	int xCoordinates[NUMBER_OF_COORDINATES];
	int yCoordinates[NUMBER_OF_COORDINATES]; 
	bool isMoving = false;
	int shape;
public:
	// Set Methods
	void setXCoordinates(int x1, int x2, int x3, int x4);
	void setXCoordinate(int index, int x);
	void setYCoordinates(int y1, int y2, int y3, int y4);
	void setYCoordinate(int index, int y);
	void setIsMoving(bool state);
	void setShape(int shape);

	// Get Methods
	int* getXCoordinates();
	int* getYCoordinates();
	bool getIsMoving();

	// This method checks if both x and y coordinate is in its arrays
	bool isContainCoordinates(int x, int y);
};

#endif