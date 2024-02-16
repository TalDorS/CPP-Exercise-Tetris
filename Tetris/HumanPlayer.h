#ifndef __HUMAN_PLAYER_H
#define __HUMAN_PLAYER_H

#include "Board.h"

class HumanPlayer
{
	Board board;
public:
	// Get Methods 
	// Get Board method can't be const because we make changes to its byRef return value
	Board& getBoard();

	//char getKey(int player);
	//char checkKey(char key, int player);


	void getKeyAndPerformAction(int  playerPressed, char keyPressed = 0);



};

#endif