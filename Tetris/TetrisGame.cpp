#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "TetrisGame.h"
#include "General.h"
#include "GameConfig.h"
#include "Tetromino.h"
#include "Board.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

#define PLAYER1 0
#define PLAYER2 1
#define DEFAULT_VALUE 0
#define WITH_COLORS '1'
#define WITHOUT_COLORS '0'
#define STARTING_SCORE 1
#define PLAYER1 0
#define PLAYER2 1
#define ABORT -1
#define START_GAME_HVH '1'
#define START_GAME_HVC '2'
#define START_GAME_CVC '3'
#define HUMAN_VS_HUMAN 0
#define HUMAN_VS_COMPUTER 1
#define COMPUTER_VS_COMPUTER 2
#define CONTINUE_GAME '4'
#define SHOW_INSTRUCTIONS '8'
#define EXIT_GAME '9'
#define RETURN_TO_MENU '0'
#define ESC 27
#define TWO 2
#define ONE 1
#define NONE 0
#define ZERO 0
#define BEST 0
#define GOOD 40
#define NOVICE 10
#define TWO_COMPUTERS 2
#define ONE_COMPUTER 1

using namespace std;

void TetrisGame::game() {
	char keyPressed = DEFAULT_VALUE;

	// Utility function for rand function
	srand(time(DEFAULT_VALUE));

	// Disable cursor Method
	showConsoleCursor(false);

	while (keyPressed != EXIT_GAME) {
		// Show menu and get key input from the user
		keyPressed = showMenu();

		// Move the user to the next section according to his decision
		switch (keyPressed)
		{
			// Player pressed human vs human game key
		case START_GAME_HVH:
			preGame(START_GAME_HVH);
			break;
			// Player pressed human vs computer game key
		case START_GAME_HVC:
			preGame(START_GAME_HVC);
			break;
			// Player pressed computer vs computer game key
		case START_GAME_CVC:
			preGame(START_GAME_CVC);
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
		default:
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
	cout << "(1) Start a new game - Human vs Human" << endl;
	cout << "(2) Start a new game - Human vs Computer" << endl;
	cout << "(3) Start a new game - Computer vs Computer" << endl;
	if (isGameOn)
		cout << "(4) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;

	while (true)
	{
		if (_kbhit()) {
			keyPressed = getKeyFromUser();

			if (keyPressed == START_GAME_HVH || keyPressed == START_GAME_HVC || keyPressed == START_GAME_CVC || (keyPressed == CONTINUE_GAME && isGameOn) || keyPressed == SHOW_INSTRUCTIONS || keyPressed == EXIT_GAME)
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
	char keyPressedPlayer1 = EMPTY_CHAR;
	char keyPressedPlayer2 = EMPTY_CHAR;

	// Clear console screeng
	clearScreen();

	// If there is no game going on, initialize new boards
	if (isGameOn == false) {
		initBoards();
		isGameOn = true;
	}

	while (true) {
		// Restart values
		keyPressedPlayer1 = EMPTY_CHAR;
		keyPressedPlayer2 = EMPTY_CHAR;

		// Check if one of the tetrominos is not moving or none of the players has lost and act accordingly. 
		updateScoresRemoveLinesAddTetromino();

		// Print players' boards
		setupAndPrintBoards();

		// Check if there is space below the tetrominos. if not, the function will stop them from moving
		isSpaceBelowTetrominos();
		
		// Move tetrominos down if there is space below them
		moveTetrominosDown();

	   // Check for key press and assign the key pressed to the right player. if user pressed escape, but game will pause
		if (getKeyPress(keyPressedPlayer1, keyPressedPlayer2))
			return;

		// Make a move!
		playersArr[PLAYER1]->getKeyAndPerformAction(PLAYER1, keyPressedPlayer1);
		playersArr[PLAYER2]->getKeyAndPerformAction(PLAYER2, keyPressedPlayer2);

		// Check if one of the players lost and if so end the game
		if (isLost())
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

	// Stop the game and clear the screen
	isGameOn = false;
	clearScreen();

	// Print winner
	printWinner();

	// Handle return to menu
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

	for (auto& currPlayer : playersArr) {
		Board& currBoard = currPlayer->getBoard();

		// Initialize board colors
		currBoard.setIsColor(isColor);

		// Initialize boards
		currBoard.initBoard();

		// Set player's score to zero
		currBoard.setScores();

		// Add a new tetromino shape to the board
		currBoard.addTetromino();

		//COMPUTER
		//currPlayer->setLevel(this->gameLevel);
		currPlayer->setMove();
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

void TetrisGame::makeEmptyVector(vector<Player*>& vector) {
	for (auto& ptr : vector) {
		if (ptr) {
			delete ptr;
			ptr = nullptr;
		}
	}
}

void TetrisGame::updateScoresRemoveLinesAddTetromino() {
	for (size_t i = DEFAULT_VALUE; i < NUM_OF_PLAYERS; i++)
	{
		Board& currBoard = playersArr[i]->getBoard();
		if (!currBoard.isTetrominoMoving())
		{
			if (!currBoard.isPlayerLost())
			{
				currBoard.updateScoreOfPlayer(STARTING_SCORE);
				currBoard.removeFullLines();
				currBoard.addTetromino();

				// If player is a computer, set his move for this tetromino
				playersArr[i]->setMove();
			}
		}
	}
}

void TetrisGame::setupAndPrintBoards() {
	playersArr[PLAYER1]->getBoard().setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
	playersArr[PLAYER2]->getBoard().setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
}

void TetrisGame::isSpaceBelowTetrominos() {
	playersArr[PLAYER1]->getBoard().spaceBelowTetromino(false);
	playersArr[PLAYER2]->getBoard().spaceBelowTetromino(false);
}

void TetrisGame::moveTetrominosDown() {
	playersArr[PLAYER1]->getBoard().moveTetrominoDown();
	playersArr[PLAYER2]->getBoard().moveTetrominoDown();
}

bool TetrisGame::isLost() {
	Board& firstPlayerBoard = playersArr[PLAYER1]->getBoard();
	Board& secondPlayerBoard = playersArr[PLAYER2]->getBoard();

	if (firstPlayerBoard.isPlayerLost() || secondPlayerBoard.isPlayerLost())
		return true;

	return false;
}

void TetrisGame::chooseComputerLevel(int numOfComputerPlayers) {
	char keyPressed = DEFAULT_VALUE;
	bool condition = true;

	clearScreen();


	for (int i = DEFAULT_VALUE; i < numOfComputerPlayers; i++) {
		condition = true;

		std::cout << "******************************" << std::endl;
		std::cout << "*        TETRIS GAME         *" << std::endl;
		std::cout << "******************************" << std::endl;

		// Present menu to user
		if(numOfComputerPlayers == ONE)
			cout << "Please select computer's difficulty!" << endl;
		if (numOfComputerPlayers == TWO)
			cout << "Please select computer " << i + ONE << "'s difficulty!" << endl;
		cout << "(a) BEST" << endl;
		cout << "(b) GOOD" << endl;
		cout << "(c) NOVICE" << endl;

		while (condition)
		{
			if (_kbhit()) {
				keyPressed = getKeyFromUser();

				switch (keyPressed)
				{
					// Best level
				case 'a':
					if (numOfComputerPlayers == ONE)
						playersArr[PLAYER2]->setLevel(BEST);
					if (numOfComputerPlayers == TWO)
						playersArr[i]->setLevel(BEST);
					condition = false;
					break;
				case 'A':
					if (numOfComputerPlayers == ONE)
						playersArr[PLAYER2]->setLevel(BEST);
					if (numOfComputerPlayers == TWO)
						playersArr[i]->setLevel(BEST);
					condition = false;
					break;
					// Best level
				case 'b':
					if (numOfComputerPlayers == ONE)
						playersArr[PLAYER2]->setLevel(GOOD);
					if (numOfComputerPlayers == TWO)
						playersArr[i]->setLevel(GOOD);
					condition = false;
					break;
				case 'B':
					if (numOfComputerPlayers == ONE)
						playersArr[PLAYER2]->setLevel(GOOD);
					if (numOfComputerPlayers == TWO)
						playersArr[i]->setLevel(GOOD);
					condition = false;
					break;
					// Best level
				case 'c':
					if (numOfComputerPlayers == ONE)
						playersArr[PLAYER2]->setLevel(NOVICE);
					if (numOfComputerPlayers == TWO)
						playersArr[i]->setLevel(NOVICE);
					condition = false;
					break;
				case 'C':
					if (numOfComputerPlayers == ONE)
						playersArr[PLAYER2]->setLevel(NOVICE);
					if (numOfComputerPlayers == TWO)
						playersArr[i]->setLevel(NOVICE);
					condition = false;
					break;
				default:
					break;
				}
			}
		}

		clearScreen();
	}

}

void TetrisGame::printWinner() {
	// Get Boards
	Board& player1Board = playersArr[PLAYER1]->getBoard();
	Board& player2Board = playersArr[PLAYER2]->getBoard();

	// Get players' scores
	int player1Score = player1Board.getScore();
	int player2Score = player2Board.getScore();

	// Save who lost and who won
	bool isPlayer1Lost = player1Board.isPlayerLost();
	bool isPlayer2Lost = player2Board.isPlayerLost();

	// if both of the players lost in the same time the winner is the one with the higher score
	if (isPlayer1Lost && isPlayer2Lost) {
		if (player1Score > player2Score) {
			cout << "The Winner is player #1 with the score: " << player1Score << endl;
		}
		else if (player1Score < player2Score) {
			cout << "The Winner is player #2 with the score: " << player2Score << endl;
		}
		else {
			cout << "A tie between the players with the score: " << player1Score << endl;
		}
	}
	else if (isPlayer2Lost) {
		cout << "The Winner is player #1 with the score: " << player1Score << endl;
	}
	else {
		cout << "The Winner is player #2 with the score: " << player2Score << endl;
	}
}

void TetrisGame::preGame(char mode) {
	// Set Game on to false
	isGameOn = false;

	// Reset Players Array and free memory
	makeEmptyVector(this->playersArr);

	switch (mode)
	{
		// Player pressed human vs human game key
	case START_GAME_HVH:
		// Set values to players array according to players' choice
		playersArr = { new HumanPlayer, new HumanPlayer };
		break;
		// Player pressed human vs computer game key
	case START_GAME_HVC:
		// Set values to players array according to players' choice
		playersArr = { new HumanPlayer, new ComputerPlayer };
		break;
		// Player pressed computer vs computer game key
	case START_GAME_CVC:
		// Set values to players array according to players' choice
		playersArr = { new ComputerPlayer, new ComputerPlayer };
		break;
	default:
		break;
	}

	// Get difficulty from user
	if(mode == START_GAME_CVC)
		chooseComputerLevel(TWO_COMPUTERS);
	else if(mode == START_GAME_HVC)
		chooseComputerLevel(ONE_COMPUTER);

	// Begin game!
	initGame();
}

bool TetrisGame::getKeyPress(char& keyPressedPlayer1, char& keyPressedPlayer2) {
	char keyPressed;

	if (_kbhit())
	{
		// Get key pressed
		keyPressed = _getch();

		// If player pressed escape, we shall return to the main menu.
		if (keyPressed == ESC)
			return true;

		int playerPressed = whoPressed(keyPressed);

		if (playerPressed == PLAYER1)
			keyPressedPlayer1 = keyPressed;
		else
			keyPressedPlayer2 = keyPressed;
	}

	return false;
}
