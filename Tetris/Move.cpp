#include "Move.h"
#include "General.h"
#include <iostream>
#include <string>

using namespace std;

int Move::sumOfSpaceInRaws() const
{
	int res = spaceInRaw[0];
	for (int i = 1; i < 4; i++)
	{
		res += spaceInRaw[i];
	}
	return res;
}

int Move::minNumOfSpaces() const
{
	int min = spaceInRaw[0];
	for (int i = 1; i < 4; i++)
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


void Move::printMove()
{

	for (int i = 0; i < moveLen(); i++)
	{
		cout << move[i] << ' ';;
	}

}


