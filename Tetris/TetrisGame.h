#ifndef __TETRIS_GAME_H
#define __TETRIS_GAME_H

#include "Player.h"

enum Level { BEST = 0, NOVICE = 10, GOOD = 40};

class TetrisGame
{
	vector<Player*> playersArr = { nullptr, nullptr };
	bool isGameOn = false;
	Level gameLevel;

	// This method displays the main menu of the game to the user on the screen
	char showMenu() const;

	// This method displays the instructions of the game to the user on the screen
	void showInstructions() const;

	// This method initializes the game
	void initGame();

	// This method initializes the boards, colors, scores and tetrominos
	void initBoards();

	//This method summarizes the game, announces the winner and returns to the main menu.
	void endGame();

	//This method presents the user with the option to play with colors or not and get the user's choice
	bool playWithColor() const;

	// This method gets a key pressed and returns the player number that is relevant to it
	int whoPressed(char keyPressed) const;

	// This method gets a vector of Players* and sets it to nullptr
	void makeEmptyVector(vector<Player*>& vector);

	// This method is a utility method of 'initGame' which if a tetromino is still moving and the player hasn't lost, updates the scores of players,
	// removes full lines and adds a new tetromino
	void updateScoresRemoveLinesAddTetromino();

	// This method sets up the boards and prints them
	void setupAndPrintBoards();

	// This method checks if there is space below the two tetrominos. if not, they will stop
	void isSpaceBelowTetrominos();

	// This method moves the tetrominos one line down if there is space
	void moveTetrominosDown();

	// This method checks if any player lost
	bool isLost();

	// This is a set function of the game level
	void setLevel(int level);

	// This function gets a computer level from the user
	void chooseComputerLevel();

	// This method is a utility method of 'endGame', it prints the winner of the game according to the game's outcome
	void printWinner();

	// This method is a utility method of 'game' function, it sets up the vector according to the mode, and initiates the game in the end 
	void preGame(char mode);
public:
	// This is the main method of the game,
	//from here we control the flow of the game with the help of the menu
	void game();

	// Enable empty constructor
	TetrisGame() {}

	// Delete copy constructor
	TetrisGame(const TetrisGame&) = delete;

	// Dtor
	~TetrisGame() {	makeEmptyVector(this->playersArr); }
};

#endif