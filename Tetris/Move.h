
#ifndef __MOVE_H
#define __MOVE_H
#include <string.h>

#define MAX_STEPS_IN_MOVE 16
#define SIZE_OF_TETROMINO 4

class Move
{
	char move[MAX_STEPS_IN_MOVE] = { '\0' }; // a sring of the entire move which in order of the step of the move
	int step = 0; // an index to the current step in the move sring
	bool isLineFull = false;
	int rows[SIZE_OF_TETROMINO] = { 0 }; //a sorted array that holds all the rows that a tetromino takes at the end of move 
	int spaceInRaw[SIZE_OF_TETROMINO] = { 0 }; //in coordination with an array of rows, it holds the number of spaces that are in the row at the end of the move
	int numOfExplodedCubs; // the number of cubes exploded at the end of a move of a bomb type shape

public:

	// set methods
	void setStep(int step) { this->step = step; }
	void setCurrentStep(int step, char action) { move[step] = action; }
	void setIsLineFull(bool Bool) { isLineFull = Bool; }
	void setRow(int index, int row) { rows[index] = row; }
	void setSpaceInRow(int index, int numOfSpaces) { spaceInRaw[index] = numOfSpaces; }
	void setnumOfExplodedCubs(int num) { numOfExplodedCubs = num; }


	// get methods
	int* getRowsAddress() { return rows; }
	int getRow(int index) const { return rows[index]; }
	int getStep() const { return step; }
	int getSpaceInRow(int index) const { return spaceInRaw[index]; }
	bool getIsLineFull() const { return isLineFull; }
	char getCurrentStep() const { return move[step]; }
	int getnumOfExplodedCubs() const { return numOfExplodedCubs; }


	void initMove() { move[0] = '\0'; }

	//This method calculates the total of all the values in the array  paceInRaw[4]
	int sumOfSpaceInRaws() const;

	//This method that returns the lowest value in the array paceInRaw[4]
	int minNumOfSpaces()const;

	//This method calculates the logical size of the string move
	int moveLen() const; // { return strlen(move); }

	//delete in the end
	//void printMove();
	

};

#endif