#include "HumanPlayer.h"

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