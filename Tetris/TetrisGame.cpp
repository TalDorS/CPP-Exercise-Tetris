#pragma warning (disable:4996)

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "TetrisGame.h"
#include "General.h"
#include "GameConfig.h"
#include "Tetromino.h"

#define DEFAULT_VALUE 0
#define PLAYER1 0
#define PLAYER2 1
#define ABORT -1
#define START_GAME '1'
#define CONTINUE_GAME '2'
#define SHOW_INSTRUCTIONS '8'
#define EXIT_GAME '9'
#define ESC 27

using namespace std;

void TetrisGame::game() {
	char keyPressed = DEFAULT_VALUE;

	// Show menu and get key input
	keyPressed = showMenu();

	
	
		// Move the user to the next section according to his decision
		switch (keyPressed)
		{
			// Player pressed start game key
		case START_GAME:
			isGameOn = false;
			initGame();
			break;
			/********************************************************************************YARDEN********************************************************/
		case CONTINUE_GAME:
			initGame();
			break;
			/********************************************************************************YARDEN********************************************************/
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

char TetrisGame::showMenu() {
	char keyPressed = DEFAULT_VALUE;

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

			if (keyPressed == START_GAME || (keyPressed == CONTINUE_GAME && isGameOn) || keyPressed == SHOW_INSTRUCTIONS || keyPressed == EXIT_GAME)
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
	cout << "For eachTetromino entered to the board the player receives 1 point." << endl;
	cout << "For each row dropped, the  player receives 10 points" << endl << endl;

	cout << "Have Fun and Good Luck!" << endl << endl;

	cout << "Press (0) to return to the main menu";

	while (keyPressed != '0')
		keyPressed = getKeyFromUser();

	game();
}

void TetrisGame::initGame() {
	char keyPressed = DEFAULT_VALUE;
	int playerPressed = DEFAULT_VALUE;


	clearScreen();

	/********************************************************************************YARDEN********************************************************/
	if (isGameOn == false) {
		// Initialize player boards
		boards[PLAYER1].initBoard();
		boards[PLAYER2].initBoard();

		boards[PLAYER1].setScores();
		boards[PLAYER2].setScores();


	}

	isGameOn = true;
	/********************************************************************************YARDEN********************************************************/


	while (true) {


		// Add new tetrominos to players if their tetrominos are not moving
		if (!boards[PLAYER1].isTetrominoMoving())
		{
			if (!boards[PLAYER1].isPlayerLost())
			{   
				boards[PLAYER1].updateScoreOfPlayer(1);
				boards[PLAYER1].removeFullLines();
				boards[PLAYER1].addTetromino();
			}
		}

		if (!boards[PLAYER2].isTetrominoMoving())
		{
			if (!boards[PLAYER2].isPlayerLost())
			{
				boards[PLAYER2].updateScoreOfPlayer(1);
				boards[PLAYER2].removeFullLines();
				boards[PLAYER2].addTetromino();
			}
		}

		// Print players' boards
		boards[PLAYER1].printBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		boards[PLAYER2].printBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
		
		// Check if there is space below the tetrominos. if not, the function will stop them from moving
		boards[PLAYER1].spaceBelowTetromino();
		boards[PLAYER2].spaceBelowTetromino();

		// Pull tetrominos down every 2 seconds

		boards[PLAYER1].moveTetrominoDown();
		boards[PLAYER2].moveTetrominoDown();

		// Check for key press and navigate to the right function
		if (_kbhit())
		{
			// Get key pressed
			keyPressed = _getch();

			/********************************************************************************YARDEN********************************************************/
			if (keyPressed == ESC)
			{
				game();
				break;
			}
			/********************************************************************************YARDEN********************************************************/


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

		if (boards[PLAYER1].isPlayerLost() && boards[PLAYER2].isPlayerLost())
		{
			endGame();
			break;
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


void TetrisGame::endGame()
{
	isGameOn = false;
	clearScreen();

	if (boards[PLAYER1].getScore() > boards[PLAYER2].getScore())
	{
		cout << "The Winner is player #1 with the score: " << boards[PLAYER1].getScore() << endl;
	}
	else if (boards[PLAYER1].getScore() < boards[PLAYER2].getScore())
	{
		cout << "The Winner is player #2 with the score: " << boards[PLAYER2].getScore() << endl;
	}
	else
	{
		cout << "A tie between the players with the score: " << boards[PLAYER1].getScore() << endl;
	}

	cout << endl << "press any ket to return to the menu";

	flushall();
	
	while (true)
	{
		if (_kbhit())
		{
			game();
			break;
		}
	}

}
