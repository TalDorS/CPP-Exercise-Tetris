#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "TetrisGame.h"
#include "General.h"
#include "GameConfig.h"

#define DEFAULT_VALUE 0
#define PLAYER1 0
#define PLAYER2 1
#define ABORT -1
#define START_GAME '1'
#define SHOW_INSTRUCTIONS '8'
#define EXIT_GAME '9'

using namespace std;

void TetrisGame::game() {
	char keyPressed = DEFAULT_VALUE;

	while (true) {
		// Show menu and get key input
		keyPressed = showMenu();

		// Move the user to the next section according to his decision
		switch (keyPressed)
		{
		// Player pressed start game key
		case START_GAME:
			initGame();
			break;
			// ************** TODO: Continue game *****************
		// Player pressed show instructions key
		case SHOW_INSTRUCTIONS:
			showInstructions();
			break;
		// Player pressed exit game key
		case EXIT_GAME:
			return;
			break;
		}
	}
}

char TetrisGame::showMenu() {
	char keyPressed = 0;

	clearScreen();

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

			if (keyPressed == '1' || (keyPressed == '2' && isGameOn) || keyPressed == '8' || keyPressed == '9')
				break;
		}			
	}
		

	return keyPressed;
}

void TetrisGame::showInstructions() {
	char keyPressed = 0;

	clearScreen();

	cout << "Tetris Game Instructions" << endl << endl;

	cout << "Welcome to the world of Tetris! This challenging classic game will test" << endl;
	cout << "your awareness and quick decision making skills. Below are the instructions" << endl;
	cout << "to help you understand and enjoy the game." << endl << endl;

	cout << "Game Objective:" << endl << endl;

	cout << "Arrange the falling Tetrominos (tetris blocks) so that no empty space remains." << endl;
	cout << "The goal is to prevent the stack of Tetrominos from reaching the top of the playing field." << endl;
	cout << "The first player whose Tetrominos reach the top layer, lose the game!" << endl;
	cout << "In case of both players reaching the top layer at the same time, the user who has the most points will win." << endl << endl;

	cout << "Controls:" << endl << endl;

	cout << "* Move Left: a or A for Left Player, j or J for Right Player" << endl;
	cout << "* Move Right: d or D for Left Player, l or L for Right Player" << endl;
	cout << "* Rotate Clockwise: s or S for Left Player, k or K for Right Player" << endl;
	cout << "* Rotate Counterclockwise: w or W for Left Player, i or I for Right Player" << endl;
	cout << "* Drop: x or X for Left Player, m or M for Right Player" << endl << endl;

	cout << "Have Fun and Good Luck!" << endl << endl;

	cout << "Press (0) to return to the main menu";

	while (keyPressed != '0')
		keyPressed = getKeyFromUser();

	game();
}

void TetrisGame::initGame() {
	char keyPressed = DEFAULT_VALUE;
	int playerPressed = DEFAULT_VALUE;
	isGameOn = true;

	clearScreen();

	// Initialize player boards
	boards[PLAYER1].initBoard();
	boards[PLAYER2].initBoard();

	while (true) {
		// Add new tetrominos to players if their tetrominos are not moving
		if (!boards[PLAYER1].isTetrominoMoving()) {
			boards[PLAYER1].removeFullLines();
			boards[PLAYER1].addTetromino();
		}
		if (!boards[PLAYER2].isTetrominoMoving()) {
			boards[PLAYER2].removeFullLines();
			boards[PLAYER2].addTetromino();
		}

		// Print players' boards
		boards[PLAYER1].printBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		boards[PLAYER2].printBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
		
		// Check if there is space below the tetrominos. if not, the function will stop them from moving
		boards[PLAYER1].spaceBelowTetromino();
		boards[PLAYER2].spaceBelowTetromino();

		// Pull tetrominos down every 2 seconds

		boards[PLAYER1].dropTetromino();
		boards[PLAYER2].dropTetromino();

		// Check for key press and navigate to the right function
		if (_kbhit())
		{
			// Get key pressed
			keyPressed = _getch();

			// Check who pressed the key
			playerPressed = whoPressed(keyPressed);

			// Check if the player who pressed the key has a moving tetromino
			if (boards[playerPressed].isTetrominoMoving())
			{
				// Perform movement action
				if (playerPressed == PLAYER1 || playerPressed == PLAYER2) {
					boards[playerPressed].performAction(keyPressed, playerPressed);
					cout.flush();
				}
			}
		}

		// Put delay for humans
		Sleep(GameConfig::GAME_TIME);
	}
}

int TetrisGame::whoPressed(char keyPressed) {
	if (keyPressed == 'a' || keyPressed == 'A' || keyPressed == 'd' || keyPressed == 'D' || keyPressed == 's'
		|| keyPressed == 'S' || keyPressed == 'w' || keyPressed == 'W' || keyPressed == 'x' || keyPressed == 'X')
		return PLAYER1;
	if (keyPressed == 'j' || keyPressed == 'J' || keyPressed == 'l' || keyPressed == 'L' || keyPressed == 'k'
		|| keyPressed == 'K' || keyPressed == 'i' || keyPressed == 'I' || keyPressed == 'm' || keyPressed == 'M')
		return PLAYER2;

	return ABORT;
}