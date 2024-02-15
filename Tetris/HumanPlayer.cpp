#include "HumanPlayer.h"
#define ESC 27
#define PLAYER1 0
#define PLAYER2 1
#define ABORT -1
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1
#define LEFT -1
#define RIGHT 1


void HumanPlayer::setupBoard(bool isColor) {
	// Initialize board colors
	this->board.setIsColor(isColor);

	// Initialize boards
	this->board.initBoard();

	// Set player's score to zero
	this->board.setScores();

	// Add a new tetromino shape to the board
	this->board.addTetromino();
}

Board& HumanPlayer::getBoard() {
	return this->board;
}

void HumanPlayer::performAction(char keyPressed, int playerNumber) {
	if (playerNumber == PLAYER1)
	{
		switch (keyPressed)
		{
			// Go Left
		case 'a':
			board.turnTetrominoLeftOrRight(LEFT);
			break;
		case 'A':
			board.turnTetrominoLeftOrRight(LEFT);
			break;
			// Go Right
		case 'd':
			board.turnTetrominoLeftOrRight(RIGHT);
			break;
		case 'D':
			board.turnTetrominoLeftOrRight(RIGHT);
			break;

			// Rotate Clockwise
		case 's':
			board.turnTetrominoClockwise(CLOCKWISE);
			break;
		case 'S':
			board.turnTetrominoClockwise(CLOCKWISE);
			break;

			// Rotate Counter-Clockwise
		case 'w':
			board.turnTetrominoClockwise(COUNTERCLOCKWISE);
			break;
		case 'W':
			board.turnTetrominoClockwise(COUNTERCLOCKWISE);
			break;

			// Drop
		case 'x':
			board.dropTetromino();
			break;
		case 'X':
			board.dropTetromino();
			break;
		default:
			break;
		}
	}
	else if (playerNumber == PLAYER2)
	{
		switch (keyPressed)
		{
			// Go Left
		case 'j':
			board.turnTetrominoLeftOrRight(LEFT);
			break;
		case 'J':
			board.turnTetrominoLeftOrRight(LEFT);
			break;

			// Go Right
		case 'l':
			board.turnTetrominoLeftOrRight(RIGHT);
			break;
		case 'L':
			board.turnTetrominoLeftOrRight(RIGHT);
			break;

			// Rotate Clockwise
		case 'k':
			board.turnTetrominoClockwise(CLOCKWISE);
			break;
		case 'K':
			board.turnTetrominoClockwise(CLOCKWISE);
			break;

			// Rotate Counter-Clockwise
		case 'i':
			board.turnTetrominoClockwise(COUNTERCLOCKWISE);
			break;
		case 'I':
			board.turnTetrominoClockwise(COUNTERCLOCKWISE);
			break;

			// Drop
		case 'm':
			board.dropTetromino();
			break;
		case 'M':
			board.dropTetromino();
			break;
		default:
			break;
		}
	}

}
