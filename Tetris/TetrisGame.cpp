#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "TetrisGame.h"
#include "General.h"
#include "GameConfig.h"
#include "Tetromino.h"
#include "Board.h"

#define DEFAULT_VALUE 0
#define WITH_COLORS '1'
#define WITHOUT_COLORS '0'
#define STARTING_SCORE 1
#define PLAYER1 0
#define PLAYER2 1
#define ABORT -1
#define START_GAME '1'
#define CONTINUE_GAME '2'
#define SHOW_INSTRUCTIONS '8'
#define EXIT_GAME '9'
#define RETURN_TO_MENU '0'
#define ESC 27

using namespace std;

void TetrisGame::game() {
	char keyPressed = DEFAULT_VALUE;

	while (keyPressed != EXIT_GAME) {
		// Show menu and get key input from the user
		keyPressed = showMenu();

		// Move the user to the next section according to his decision
		switch (keyPressed)
		{
			// Player pressed start game key
		case START_GAME:
			isGameOn = false;
			initGame();
			break;
		case CONTINUE_GAME:
			initGame();
			break;
			// Player pressed show instructions key
		case SHOW_INSTRUCTIONS:
			showInstructions();
			break;
			// Player pressed exit game key
		case EXIT_GAME:
			clearScreen();
			return;
			break;
		}
	}
}

char TetrisGame::showMenu() const {
	char keyPressed = DEFAULT_VALUE;

	clearScreen();

	std::cout << "******************************" << std::endl;
	std::cout << "*        TETRIS GAME         *" << std::endl;
	std::cout << "******************************" << std::endl;

	// Present menu to user
	cout << "(1) Start a new game" << endl;
	if(isGameOn)
		cout << "(2) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;

	while (true)
	{
		if (_kbhit()) {
			keyPressed = getKeyFromUser();

			if (keyPressed == START_GAME || (keyPressed == CONTINUE_GAME && isGameOn) || keyPressed == SHOW_INSTRUCTIONS || keyPressed == EXIT_GAME)
				break;
		}			
	}
		
	return keyPressed;
}

void TetrisGame::showInstructions() const {
	char keyPressed = DEFAULT_VALUE;

	clearScreen();

	cout << "Tetris Game Instructions" << endl << endl;

	cout << "Welcome to the world of Tetris! This challenging classic game will test" << endl;
	cout << "your awareness and quick decision making skills. Below are the instructions" << endl;
	cout << "to help you understand and enjoy the game." << endl << endl;

	cout << "Game Objective:" << endl << endl;

	cout << "Arrange the falling c (tetris blocks) so that no empty space remains." << endl;
	cout << "The goal is to prevent the stack of Tetrominos from reaching the top of the playing field." << endl;
	cout << "The first player whose Tetrominos reach the top layer, lose the game!" << endl;
	cout << "In case of both players reaching the top layer at the same time, the user who has the most points will win." << endl << endl;

	cout << "Controls:" << endl << endl;

	cout << "* Move Left: a or A for Left Player, j or J for Right Player" << endl;
	cout << "* Move Right: d or D for Left Player, l or L for Right Player" << endl;
	cout << "* Rotate Clockwise: s or S for Left Player, k or K for Right Player" << endl;
	cout << "* Rotate Counterclockwise: w or W for Left Player, i or I for Right Player" << endl;
	cout << "* Drop: x or X for Left Player, m or M for Right Player" << endl << endl;

	cout << "Scoring method:" << endl;
	cout << "For each Tetromino entered to the board the player receives 1 point." << endl;
	cout << "For each row dropped, the  player receives 10 points" << endl << endl;

	cout << "Have Fun and Good Luck!" << endl << endl;

	cout << "Press (0) to return to the main menu";

	while (keyPressed != RETURN_TO_MENU)
		keyPressed = getKeyFromUser();

	return;
}

void TetrisGame::initGame() {
	// Clear console screen
	clearScreen();

	// If there is no game going on, initialize new boards
	if (isGameOn == false) {
		initBoards();
		isGameOn = true;
	}
	
	// Check if one of the tetrominos is not moving and act accordingly. 
	while (true) {
		for (int player = PLAYER1; player < NUM_OF_PLAYERS; ++player) {
			if (!boards[player].isTetrominoMoving())
			{
				if (!boards[player].isPlayerLost())
				{
					boards[player].updateScoreOfPlayer(STARTING_SCORE);
					boards[player].removeFullLines();
					boards[player].addTetromino();
				}
			}
		}
		
		// Print players' boards
		boards[PLAYER1].setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		boards[PLAYER2].setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);

		// Check if there is space below the tetrominos. if not, the function will stop them from moving
		isSpaceBelowTetrominos();

		// Move tetrominos down if there is space below them
		moveTetrominosDown();

		// Check for key press and navigate to the right function
		getKeyAndPerformAction();

		// Check if one of the players lost
		isLost();

		// Put delay for humans
		Sleep(GameConfig::GAME_TIME);
	}
}

int TetrisGame::whoPressed(char keyPressed) const {
	if (keyPressed == 'a' || keyPressed == 'A' || keyPressed == 'd' || keyPressed == 'D' || keyPressed == 's'
		|| keyPressed == 'S' || keyPressed == 'w' || keyPressed == 'W' || keyPressed == 'x' || keyPressed == 'X')
		return PLAYER1;
	if (keyPressed == 'j' || keyPressed == 'J' || keyPressed == 'l' || keyPressed == 'L' || keyPressed == 'k'
		|| keyPressed == 'K' || keyPressed == 'i' || keyPressed == 'I' || keyPressed == 'm' || keyPressed == 'M')
		return PLAYER2;

	return ABORT;
}

void TetrisGame::endGame()
{
	// Get all past inputs
	while (_kbhit())
		_getch();

	isGameOn = false;
	clearScreen();

	// if both of the players lost in the same time the winner is the one with the higher score
	if (boards[PLAYER1].isPlayerLost() && boards[PLAYER2].isPlayerLost()){
		if (boards[PLAYER1].getScore() > boards[PLAYER2].getScore()){
			cout << "The Winner is player #1 with the score: " << boards[PLAYER1].getScore() << endl;
		}
		else if (boards[PLAYER1].getScore() < boards[PLAYER2].getScore()){
			cout << "The Winner is player #2 with the score: " << boards[PLAYER2].getScore() << endl;
		}
		else{
			cout << "A tie between the players with the score: " << boards[PLAYER1].getScore() << endl;
		}
	}
	else if (boards[PLAYER2].isPlayerLost()){
		cout << "The Winner is player #1 with the score: " << boards[PLAYER1].getScore() << endl;
	}
	else{
		cout << "The Winner is player #2 with the score: " << boards[PLAYER2].getScore() << endl;
	}

	cout << endl << "Press any key to return to the menu";
	
	while (true){
		if (_kbhit()){
			_getch();
			return;
		}
	}

}

bool TetrisGame::playWithColor() const
{
	char keyPressed = DEFAULT_VALUE;

	clearScreen();

	// Instructions message for user
	cout << "Before we begin.." << endl;
	cout << "You need to decide if you want to play with colors." << endl;
	cout << "To play without colors press (0)" << endl;
	cout << "To play with colors press (1)" << endl;

	// Get decision from user
	while (true)
	{
		if (_kbhit()) {
			keyPressed = getKeyFromUser();

			if (keyPressed == WITH_COLORS) {
				return true;
			}
			if (keyPressed == WITHOUT_COLORS) {
				return false;
			}
		}
	}
	return false;
}

void TetrisGame::initBoards() {
	bool isColor;

	// Get user's info if he wants to play with color or not
	isColor = playWithColor();
	clearScreen();

	for (int player = PLAYER1; player < NUM_OF_PLAYERS; ++player) {
		// Initialize board colors
		boards[player].setIsColor(isColor);

		// Initialize boards
		boards[player].initBoard();

		// Set player's score to zero
		boards[player].setScores();

		// Add a new tetromino shape to the board
		boards[player].addTetromino();
	}
}

void TetrisGame::isLost() {
	if (boards[PLAYER1].isPlayerLost() || boards[PLAYER2].isPlayerLost())
	{
		endGame();
		return;
	}
}

inline void TetrisGame::getKeyAndPerformAction() {
	char keyPressed = DEFAULT_VALUE;
	int playerPressed = DEFAULT_VALUE;

	// Check for key press and navigate to the right function
	if (_kbhit())
	{
		// Get key pressed
		keyPressed = _getch();

		// If player pressed escape, we show return to the main menu.
		if (keyPressed == ESC)
			return;

		// Check who pressed the key
		playerPressed = whoPressed(keyPressed);

		// Check if the player who pressed the key has a moving tetromino
		if (boards[playerPressed].isTetrominoMoving())
		{
			// Perform movement action
			if (playerPressed == PLAYER1 || playerPressed == PLAYER2) {
				boards[playerPressed].performAction(keyPressed, playerPressed);
			}
		}
	}
}

void TetrisGame::isSpaceBelowTetrominos() {
	// Check if there is space below the tetrominos. if not, the function will stop them from moving
	for (int player = PLAYER1; player < NUM_OF_PLAYERS; ++player) {
		boards[player].spaceBelowTetromino();
	}
}

void TetrisGame::moveTetrominosDown() {
	for (int player = PLAYER1; player < NUM_OF_PLAYERS; ++player) {
		boards[player].moveTetrominoDown();
	}
}