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
	//**1**
	void setXCoordinates(int x1, int x2, int x3, int x4);
	//**2**
	void setXCoordinate(int index, int x);
	//**3**
	void setYCoordinates(int y1, int y2, int y3, int y4);
	//**4**
	void setYCoordinate(int index, int y);
	//**5**
	void setIsMoving(bool state);
	//**6**
	void setShape(int shape);

	// Get Methods
	//**7**
	int* getXCoordinates();
	//**8**
	int* getYCoordinates();
	//**9**
	bool getIsMoving();

	//**10**
	// This method checks if both x and y coordinate is in its arrays
	bool isContainCoordinates(int x, int y);
};

#endif