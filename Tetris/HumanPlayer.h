#ifndef __HUMAN_PLAYER_H
#define __HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{
public:

	//This method returns the key of the computer's move at a given moment
	void getKeyAndPerformAction(int  playerPressed) {};

	//This method returns the key of the computer's move at a given moment
	void getKeyAndPerformAction(int  playerPressed, char keyPressed);
};

#endif