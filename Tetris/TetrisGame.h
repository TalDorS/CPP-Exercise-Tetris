#ifndef __TETRIS_GAME_H
#define __TETRIS_GAME_H

#include "Board.h"

class TetrisGame
{
	static constexpr int NUM_OF_BOARDS = 3;
	Board boards[NUM_OF_BOARDS];
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

public:
	// This is the main method of the game,
	//from here we control the flow of the game with the help of the menu
	void game();

	// Enable empty constructor
	TetrisGame() {}

	// Delete copy constructor
	TetrisGame(const TetrisGame&) = delete;
};

#endif