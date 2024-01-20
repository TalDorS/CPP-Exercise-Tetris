#ifndef __TETRIS_GAME_H
#define __TETRIS_GAME_H

#include "Board.h"

#define NUM_OF_BOARDS 2
#define NUM_OF_COORDINATES 2

class TetrisGame
{
	Board boards[NUM_OF_BOARDS];
	bool isGameOn = false;
	bool isColor;

public:
	// This is the main method of the game,
	//from here we control the flow of the game with the help of the menu
	void game();

	// This method displays the main menu of the game to the user on the screen
	char showMenu();

	// This method displays the instructions of the game to the user on the screen
	void showInstructions();

	// This method initializes the game
	void initGame();

	// This method gets a key pressed and returns the player number that is relevant to it
	int whoPressed(char keyPressed);

	//***************************************************************YARDEN**********************************************************
	//This method summarizes the game, announces the winner and returns to the main menu.
	void endGame();

	//This method presents the user with the option to play with colors and get the user's choice
	void playWithColor();

	void setIsColor(bool state);

	bool getIsColor();

};

#endif