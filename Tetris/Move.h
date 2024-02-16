
#ifndef __MOVE_H
#define __MOVE_H
#include <string.h>

class Move
{
	char move[16] = { '\0' };
	int step = 0;
	bool isLineFull = false;
	int rows[4] = { 0 };
	int spaceInRaw[4] = { 0 };
	int numOfBombed;

public:
	void setStep(int step) { this->step = step; }
	void initMove() { move[0] = '\0'; }
	void setCurrentStep(int step, char action) { move[step] = action; }
	void setIsLineFull(bool Bool) { isLineFull = Bool; }
	void setRow(int index, int row) { rows[index] = row; }
	int* getRowsAddress() { return rows; }
	int getRow(int index) const { return rows[index]; }
	void setSpaceInRow(int index, int numOfSpaces) { spaceInRaw[index] = numOfSpaces; }
	int getStep() const { return step; }
	int getSpaceInRow(int index) const { return spaceInRaw[index]; }
	int sumOfSpaceInRaws() const;
	int minNumOfSpaces()const;
	bool getIsLineFull() const { return isLineFull; }
	int moveLen() const; // { return strlen(move); }
	char getCurrentStep() const { return move[step]; }
	void printMove();

};

#endif