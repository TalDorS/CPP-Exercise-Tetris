#ifndef __TETRIS_GAME_H
#define __TETRIS_GAME_H

#include <iostream>
#include <vector>
#include "Board.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

class TetrisGame
{
	vector<HumanPlayer> humanPlayersArray;
	vector<ComputerPlayer> computerPlayersArray;
	int gameMode;
	bool isGameOn = false;

	// This method displays the main menu of the game to the user on the screen
	char showMenu() const;

	// This method displays the instructions of the game to the user on the screen
	void showInstructions() const;

	// This method initializes the game
	void initGame();

	// This method initializes the boards, colors, scores and tetrominos
	void initBoards();

	// This method gets a key pressed and returns the player number that is relevant to it
	int whoPressed(char keyPressed) const;

	//This method summarizes the game, announces the winner and returns to the main menu.
	void endGame() ;

	//This method presents the user with the option to play with colors or not and get the user's choice
	bool playWithColor() const;

	// This method sets up the boards and prints them
	void setupAndPrintBoards();

	// This method handles key presses and moves to the right action. if user pressed ESCAPE will return true
	bool getKeyAndPerformAction();

	// This method moves the tetrominos one line down if there is space
	void moveTetrominosDown();

	// This method checks if there is space below the two tetrominos. if not, they will stop
	void isSpaceBelowTetrominos();

	// Utility method of 'getKeyAndPerformAction', it navigates to the right perform action function by player type and number
	void navigateToPerformAction(char keyPressed, int playerPressed);

	// This method checks if any player lost
	bool isLost();

	// This method is a utility method of 'initGame' which if a tetromino is still moving and the player hasn't lost, updates the scores of players,
	// removes full lines and adds a new tetromino
	void updateScoresRemoveLinesAddTetromino();

	// This method is a utility method of 'endGame', it prints the winner of the game according to the game's outcome
	void printWinner();

	// This method is a utility method of 'getKeyAndPerformAction'. it checks who pressed the key to perform an action, and returns if its tetromino is moving or not.
	bool isPressedTetrominoMoving(int playerPressed);

public:
	// This is the main method of the game,
	//from here we control the flow of the game with the help of the menu
	void game();

	// Enable empty constructor
	TetrisGame() {}

	// Delete copy constructor
	TetrisGame(const TetrisGame&) = delete;

	//yarden
	void setMove();

};

#endif