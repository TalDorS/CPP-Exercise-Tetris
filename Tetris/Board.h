#ifndef __BOARD_H
#define __BOARD_H

#include "Tetromino.h"
#include "GameConfig.h"

// This class controls the players' board and everything that is going on inside it
class Board
{
	Tetromino currentTetromino;
	char gameBoard[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];

public:
	// This function initalizes a board, with a border and empty interior
	void initBoard();

	// This function prints the board and all its contents
	void printBoard(int x, int y);

	// This function adds a new tetromino to the board
	void addTetromino();

	// Tetromino movement methods
	void turnTetrominoLeft();
	void turnTetrominoRight();
	void turnTetrominoClockwise(int num);
	void dropTetromino();

	// This function clears a certain blocks according to X and Y coordinates
	void clearBlocks();

	// This function moves the tetromino according to the user's choice
	void performAction(char keyPressed, int playerNumber);

	// This function checks if a line is full
	bool isLineFull(int y);

	// This function deletes a line from the board
	void makeLineEmpty(int y);

	// This function removes full lines which are occupied by characters
	void removeFullLines();

	// This function returns the isMoving variable in its current tetromino
	bool isTetrominoMoving();

	// This method checks if there is space below the tetromino while it's going down
	bool spaceBelowTetromino();
};

#endif