#include "HumanPlayer.h"
#include <conio.h>

#define  DEFAULT_VALUE 0
#define ESC 27
#define PLAYER1 0
#define PLAYER2 1
#define ABORT -1


void HumanPlayer::getKeyAndPerformAction(int playerPressed, char keyPressed) {

	if (board.isTetrominoMoving())
	{
		board.performAction(keyPressed, playerPressed);
	}
	getBoard();

}