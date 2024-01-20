#ifndef __BOARD_H
#define __BOARD_H

#include "Tetromino.h"
#include "GameConfig.h"
#include "Point.h"

#define NUM_OF_PLAYERS 2

// This class controls the players' board and everything that is going on inside it
class Board
{
	Tetromino currentTetromino;
	char gameBoard[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	int score;
	bool isColor;
	int colorByLocation[(GameConfig::GAME_HEIGHT)][(GameConfig::GAME_WIDTH)];
	int backgroundColor;
public:

	//set Methods
	void setScores();
	void setIsColor(bool isColor);
	void setBackgroundColor(int color);


	//get Methods
	int getScore();
	int getBackgroundColor();


	// This method initalizes a board, with a border and empty interior
	void initBoard();

	// This method prints the board and all its contents
	void printBoard(int x, int y);

	// This method prints the tetromino to the game board
	void printTetromino();

	// This method adds a new tetromino to the board
	void addTetromino();

	// Tetromino movement methods
	void turnTetrominoLeft();
	void turnTetrominoRight();
	void turnTetrominoClockwise(int num);
	void dropTetromino();
	void moveTetrominoDown();

	// This method clears a certain blocks according to X and Y coordinates
	void clearBlocks();

	// This method moves the tetromino according to the user's choice
	void performAction(char keyPressed, int playerNumber);

	// This method checks if a line is full
	bool isLineFull(int y);

	// This method deletes a line from the board
	void makeLineEmpty(int y);

	// This method removes full lines which are occupied by characters, and drops everything else by one level
	void removeFullLines();

	// This method returns the isMoving variable in its current tetromino
	bool isTetrominoMoving();

	// This method checks if there is space below the tetromino while it's going down
	bool spaceBelowTetromino();

	// This method moves everything that is above a y value down
	void moveEverythingDown(int y);

	// This method gets the current tetromino
	Tetromino getCurrentTetromino();

	//This method checks if the player has lost
	bool isPlayerLost();

	// The following methods:
	//dealing with each player's score, (Initializing the score to 0, accessing the current score and updating the score)
	void updateScoreOfPlayer(int num);

	//This method prints the player's score in the relevant place on the screen
	void printScore(int x, int y);

	//COLORS METHODS:
	//The color printing methods will work as follows:
	//There will be a matrix of colors in the size of the board whose positions in the matrix will be coordinated with the position of a point on the board.

	//This method gets a color and defines the color to be the background color of the print
	void WhatColor(int color);

	//This method initializes the entire matrix to be black
	void initColorByLocation( );

	//This method receives a color and a location on the board and updates the color in a colors matrix.
	void updateColorByLocation(int x, int y, int color);

	//This method prints the board according to the colors that are updated in a colors matrix
	void printWithColors(int x, int y);
    
	//This method prints the board without colors
	void printWithoutColors(int x, int y);

	
};

#endif