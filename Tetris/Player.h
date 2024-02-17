#ifndef __PLAYER_H
#define __PLAYER_H

#include "Board.h"

class Player
{
protected:
	Board board;

public:
	// Get Methods 
	// Get Board method can't be const because we make changes to its byRef return value
	Board& getBoard();

	// This function is only 
	virtual void setMove() {}

	//This method returns the key of the computer's move at a given moment
	virtual void getKeyAndPerformAction(int player) {}

	//setMetod
	virtual void setLevel(int level) {};

	virtual void getKeyAndPerformAction(int player, char keyPressed) {};
};

#endif