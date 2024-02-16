#include "HumanPlayer.h"
#include <conio.h>

#define  DEFAULT_VALUE 0
#define ESC 27
#define PLAYER1 0
#define PLAYER2 1
#define ABORT -1



Board& HumanPlayer::getBoard() {
	return this->board;
}

//char HumanPlayer::getKey(int player)
//{
//	char keyPressed = DEFAULT_VALUE;
//
//	if (_kbhit())
//	{
//		// Get key pressed
//		keyPressed = _getch();
//
//		if (keyPressed == ESC)
//		{
//			return ESC;
//		}
//
//		keyPressrd = checkKey(keyPressed, player);
//	}
//
//
//
//	return keyPressed;
//}

//char HumanPlayer::checkKey(char key, int player)
//{
//	if ((player == PLAYER1) && (key == 'a' || key == 'A' || key == 'd' || key == 'D' || key == 's'
//		|| key == 'S' || key == 'w' || key == 'W' || key == 'x' || key == 'X'))
//		return key;
//	else if ((player == PLAYER2) && (key == 'j' || key == 'J' || key == 'l' || key == 'L' || key == 'k'
//		|| key == 'K' || key == 'i' || key == 'I' || key == 'm' || key == 'M'))
//		return key;
//	else
//		return DEFAULT_VALUE;
//}



void HumanPlayer::getKeyAndPerformAction(int  playerPressed, char keyPressed) {

	if (board.isTetrominoMoving())
	{
		board.performAction(keyPressed, playerPressed);
	}


}