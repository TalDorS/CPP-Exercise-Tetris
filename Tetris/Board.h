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
	int colorByLocation[(GameConfig::GAME_HEIGHT)][(GameConfig::GAME_WIDTH)];
	int backgroundColor;
	bool isColor;

	// This method clears a certain blocks according to X and Y coordinates
	void clearBlocks();

	// This method deletes a line from the board
	void makeLineEmpty(int y);

	// This method moves everything that is above a y value down
	void moveEverythingDown(int y);


	//This method prints the player's score in the relevant place on the screen
	void printScore(int x, int y) const;

	//This method gets a color and defines the color to be the background color of the print
	void whatColor(int color) const;


	//This method initializes the entire matrix to be black
	void initColorByLocation();


	//This method receives a color and a location on the board and updates the color in a colors matrix.
	void updateColorByLocation(int x, int y, int color);

	//This method prints the board according to the colors that are updated in a colors matrix
	void printBoardWithColors(int x, int y) const;

	//This method prints the board without colors
	void printBoardWithoutColors(int x, int y) const;

	// This method returns if a given coordinate is in the board
	bool isInBoard(int x, int y) const;
public:
	//empty c-tor for a Board object 
	Board();


	//set Methods
	void setScores();
	void setIsColor(bool isColor);
	void setBackgroundColor(int color);


	//get Methods
	int getBackgroundColor() const;
	int getScore() const;
	size_t getCurrentTetrominoVecSize() const;


	// This method initalizes a board, with a border and empty interior
	void initBoard();

	// This method adds a new tetromino to the board
	void addTetromino();

	// Tetromino movement methods
	void moveTetrominoDown();

	// This method moves the tetromino according to the user's choice
	void performAction(char keyPressed, int playerNumber);

	// This method removes full lines which are occupied by characters, and drops everything else by one level
	void removeFullLines();

	// This method returns the isMoving variable in its current tetromino
	bool isTetrominoMoving() const;

	// This method checks if there is space below the tetromino while it's going down
	bool spaceBelowTetromino();

	// This method gets the current tetromino
	Tetromino getCurrentTetromino() const;

	//This method checks if the player has lost
	bool isPlayerLost() const;

	// The following methods:
	//dealing with each player's score, (Initializing the score to 0, accessing the current score and updating the score)
	void updateScoreOfPlayer(int num);

	//COLORS METHODS:
	//The color printing methods will work as follows:
	//There will be a matrix of colors in the size of the board whose positions in the matrix will be coordinated with the position of a point on the board.

	// This method prints the tetromino to the game board
	void printTetromino();

	// Tetromino movement methods
	// Tetromino movement methods
	void turnTetrominoLeftOrRight(int direction);
	void turnTetrominoClockwise(int num);
	void dropTetromino();

	// This method checks if a line is full
	bool isLineFull(int y) const;


	//******************************************************yarden - new methos

	//This method receives a row number and returns the current number of spaces in the row
	int getNumOfSpaceInLine(int line) const;

	//This method returns the number of cubes that are going to explode at the end of a certain move of a bomb
	int numOfExplodedCubs() const;

	//*****************************************************************new function for bomb from Tal

	// This method gets a random number between 1 and 100, and if its between 95 to 100, it returns true
	bool isBomb() const;

	// This method checks if the current tetromino is a bomb
	bool isCurrentShapeBomb() const;

	// This method explodes the bomb tetromino
	void explodeBomb();

	// This function moves all of the points above a certain point down, untill the point above it hits empty char or border
	void moveAboveDown(int x, int y);

	// This method prints the board and all its contents
	// ** NOT CONSTANT BECAUSE IT CHANGES THINGS **
	void setupAllAndPrintBoard(int x, int y);
};

#endif