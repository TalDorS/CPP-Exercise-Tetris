#ifndef __HUMAN_PLAYER_H
#define __HUMAN_PLAYER_H

#include "Board.h"

class HumanPlayer
{
	Board board;

public:
	// This function sets up the Human player's board
	void setupBoard(const bool isColor);

	// Get Methods 
	// Get Board method can't be const because we make changes to its byRef return value
	Board& getBoard();

	void performAction(char keyPressed, int playerNumber);

};

#endif