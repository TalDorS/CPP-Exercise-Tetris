#include "Move.h"
#include "General.h"
#include <iostream>
#include <string>

using namespace std;
 
#define FIRST_STEP 0 
#define FIRST_ROW 0
#define SIZE_0F_ROWS 4

void Move::initMove() 
{ 
	move[FIRST_STEP] = '\0'; 
	setStep(FIRST_STEP);
}

int Move::sumOfSpaceInRaws() const
{
	int res = spaceInRaw[FIRST_ROW];
	for (int i = 1; i < SIZE_0F_ROWS; i++)
	{
		res += spaceInRaw[i];
	}
	return res;
}

int Move::minNumOfSpaces() const
{
	int min = spaceInRaw[FIRST_ROW];
	for (int i = 1; i < SIZE_0F_ROWS; i++)
	{
		if (min > spaceInRaw[i])
			min = spaceInRaw[i];
	}
	return min;

}

int Move::moveLen() const
{
	return strlen(move);
}
