#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "TetrisGame.h"
#include "General.h"
#include "GameConfig.h"
#include "Tetromino.h"
#include "Board.h"
#include "HumanPlayer.h"

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
#define BEST 0
#define GOOD 40
#define NOVICE 10

using namespace std;

void TetrisGame::game() {
	char keyPressed = DEFAULT_VALUE;

	while (keyPressed != EXIT_GAME) {
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
	if (isGameOn)
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
	char keyPressed = DEFAULT_VALUE;
	int playerPressed = DEFAULT_VALUE;

	// Clear console screeng
	clearScreen();

	// If there is no game going on, initialize new boards
	if (isGameOn == false) {
		initBoards();
		isGameOn = true;
	}

	while (true) {

		// Add new tetrominos to players if their tetrominos are not moving
		if (!player1.getBoard().isTetrominoMoving())
		{
			if (!player1.getBoard().isPlayerLost())
			{
				player1.getBoard().updateScoreOfPlayer(STARTING_SCORE);
				player1.getBoard().removeFullLines();
				player1.getBoard().addTetromino();
				//COMPUTER
				player1.setmove();
			}
		}

		if (!player2.getBoard().isTetrominoMoving())
		{
			if (!player2.getBoard().isPlayerLost())
			{
				player2.getBoard().updateScoreOfPlayer(STARTING_SCORE);
				player2.getBoard().removeFullLines();
				player2.getBoard().addTetromino();
				//COMPUTER
				player2.setmove();
			}
		}

		// Print players' boards
		player1.getBoard().printBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		player2.getBoard().printBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);

		// Check if there is space below the tetrominos. if not, the function will stop them from moving
		player1.getBoard().spaceBelowTetromino();
		player2.getBoard().spaceBelowTetromino();
		
		// Pull tetrominos down every 2 seconds
		player1.getBoard().moveTetrominoDown();
		player2.getBoard().moveTetrominoDown();

		//HUMEN

	   // Check for key press and navigate to the right function
		/*if (_kbhit())
		{
			char keyPressed;
			// Get key pressed
			keyPressed = _getch();

			// If player pressed escape, we shall return to the main menu.
			if (keyPressed == ESC)
				return;

			int playerPressed = whoPressed(keyPressed);

			if (playerPressed == PLAYER1)
				player1.getKeyAndPerformAction(PLAYER1,keyPressed);
			else
				player2.getKeyAndPerformAction(PLAYER2,keyPressed);
		}
		*/



		//COMPUTER

		player1.getKeyAndPerformAction(PLAYER1);
		player2.getKeyAndPerformAction(PLAYER2);


		// Check if one of the player lost
		if (player1.getBoard().isPlayerLost() || player2.getBoard().isPlayerLost())
		{
			endGame();
			return;
		}

		// Put delay for humans
		Sleep(GameConfig::GAME_TIME);
	}
}

void TetrisGame::endGame()
{
	// Get all past inputs
	while (_kbhit())
		_getch();

	isGameOn = false;
	clearScreen();

	// if both of the players lost in the same time the winner is the one with the higher score
	if (player1.getBoard().isPlayerLost() && player2.getBoard().isPlayerLost()) {
		if (player1.getBoard().getScore() > player2.getBoard().getScore()) {
			cout << "The Winner is player #1 with the score: " << player1.getBoard().getScore() << endl;
		}
		else if (player1.getBoard().getScore() < player2.getBoard().getScore()) {
			cout << "The Winner is player #2 with the score: " << player2.getBoard().getScore() << endl;
		}
		else {
			cout << "A tie between the players with the score: " << player1.getBoard().getScore() << endl;
		}
	}
	else if (player2.getBoard().isPlayerLost()) {
		cout << "The Winner is player #1 with the score: " << player1.getBoard().getScore() << endl;
	}
	else {
		cout << "The Winner is player #2 with the score: " << player2.getBoard().getScore() << endl;
	}

	cout << endl << "Press any key to return to the menu";

	while (true) {
		if (_kbhit()) {
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

	//init player1 board:

		// Initialize board colors
	player1.getBoard().setIsColor(isColor);

	// Initialize boards
	player1.getBoard().initBoard();

	// Set player's score to zero
	player1.getBoard().setScores();

	// Add a new tetromino shape to the board
	player1.getBoard().addTetromino();

	//COMPUTER
	player1.setLevel(GOOD);
	player1.setmove();

	//init player2 board:

		// Initialize board colors
	player2.getBoard().setIsColor(isColor);

	// Initialize boards
	player2.getBoard().initBoard();

	// Set player's score to zero
	player2.getBoard().setScores();

	// Add a new tetromino shape to the board
	player2.getBoard().addTetromino();

	//COMPUTER
	player2.setLevel(NOVICE);
	player2.setmove();

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


