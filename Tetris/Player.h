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

	// This method sets a move only for computer player
	virtual void setMove() {};

	// This method sets up the level of 
	virtual void setLevel(int level) {};

	// This method gets a key and performs the right action
	virtual void getKeyAndPerformAction(int player, char keyPressed) {};
};

#endif