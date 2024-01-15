#include "Board.h"
#include "General.h"
#include "GameConfig.h"
#include <iostream>
#include <Windows.h>

#define DEFAULT_VALUE 0
#define NUM_OF_COORDINATES 4
#define PLAYER1 0
#define PLAYER2 1
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1

using namespace std;

void Board::initBoard() {
	// Set characters in the board
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++) {
		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			if (i == DEFAULT_VALUE || i == (GameConfig::GAME_HEIGHT - 1) || j == 0 || j == (GameConfig::GAME_WIDTH - 1))
				gameBoard[i][j] = GameConfig::BOARD_BORDER_CHAR;
			else
				gameBoard[i][j] = ' ';
		}
	}

}

void Board::printBoard(int x, int y) {
	// Print message above the boards
	gotoxy(GameConfig::FIRST_BOARD_X + 18, GameConfig::FIRST_BOARD_Y - 2);
	cout << "TETRIS";

	printScore(x, y);

	// Print tetromino characters
	printTetromino();

	// Print board
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++) {
		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			gotoxy(x + j, y + i);
			cout << gameBoard[i][j];
		}
		cout << endl;
	}
}

void Board::addTetromino() {
	// Generate a random number between 1 and 7 that will decide the shape
	srand(time(0));

	GameConfig::eShapes shape = (GameConfig::eShapes)(rand() % 7 + 1);

	// Handle according to 
	switch (shape)
	{
	case GameConfig::eShapes::Straight: // Straight Tetromino
		currentTetromino.setXCoordinates(4, 5, 6, 7);
		currentTetromino.setYCoordinates(1, 1, 1, 1);
		break;
	case GameConfig::eShapes::Square: // Square Tetromino
		currentTetromino.setXCoordinates(4, 5, 4, 5);
		currentTetromino.setYCoordinates(1, 1, 2, 2);
		break;
	case GameConfig::eShapes::TShaped: // T shaped Tetromino
		currentTetromino.setXCoordinates(4, 5, 6, 5);
		currentTetromino.setYCoordinates(1, 1, 1, 2);
		break;
	case GameConfig::eShapes::LShaped: // L shaped Tetromino
		currentTetromino.setXCoordinates(4, 4, 4, 5);
		currentTetromino.setYCoordinates(1, 2, 3, 3);
		break;
	case GameConfig::eShapes::SShaped: // S shaped Tetromino
		currentTetromino.setXCoordinates(4, 5, 5, 6);
		currentTetromino.setYCoordinates(2, 2, 1, 1);
		break;
	case GameConfig::eShapes::JShaped: // J shaped Tetromino
		currentTetromino.setXCoordinates(5, 5, 5, 4);
		currentTetromino.setYCoordinates(1, 2, 3, 3);
		break;
	case GameConfig::eShapes::ZShaped: // Z shaped Tetromino
		currentTetromino.setXCoordinates(4, 5, 5, 6);
		currentTetromino.setYCoordinates(1, 1, 2, 2);
		break;
	default:
		break;
	}

	// Add coordinates value to tetromino
	currentTetromino.setIsMoving(true);
}

bool Board::spaceBelowTetromino() {
	int* xCoordinates = currentTetromino.getXCoordinates();
	int* yCoordinates = currentTetromino.getYCoordinates();
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = xCoordinates[i];
		y = yCoordinates[i];

		// If the board has a character below a certain tetromino coordinate, and also it's not
		// the tetromino's character, return false and set tetromino to stop moving.
		if (gameBoard[y + 1][x] != ' ' && !currentTetromino.isContainCoordinates(y + 1, x)) {
			currentTetromino.setIsMoving(false);
			return false;
		}
	}
	return true;
}

void Board::performAction(char keyPressed, int playerNumber) {
	if (playerNumber == PLAYER1)
	{
		switch (keyPressed)
		{
		// Go Left
		case 'a':
			turnTetrominoLeft();
			break;
		case 'A':
			turnTetrominoLeft();
			break;
		// Go Right
		case 'd':
			turnTetrominoRight();
			break;
		case 'D':
			turnTetrominoRight();
			break;
		
		// Rotate Clockwise
		case 's':
			turnTetrominoClockwise(CLOCKWISE);
			break;
		case 'S':
			turnTetrominoClockwise(CLOCKWISE);
			break;

		// Rotate Counter-Clockwise
		case 'w':
			turnTetrominoClockwise(COUNTERCLOCKWISE);
			break;
		case 'W':
			turnTetrominoClockwise(COUNTERCLOCKWISE);
			break;

		// Drop
		case 'x':
			dropTetromino();
			break;
		case 'X':
			dropTetromino();
			break;
		default:
			break;
		}
	}
	else if (playerNumber == PLAYER2) 
	{
		switch (keyPressed)
		{
		// Go Left
		case 'j':
			turnTetrominoLeft();
			break;
		case 'J':
			turnTetrominoLeft();
			break;

		// Go Right
		case 'l':
			turnTetrominoRight();
			break;
		case 'L':
			turnTetrominoRight();
			break;

		// Rotate Clockwise
		case 'k':
			turnTetrominoClockwise(CLOCKWISE);
			break;
		case 'K':
			turnTetrominoClockwise(CLOCKWISE);
			break;

		// Rotate Counter-Clockwise
		case 'i':
			turnTetrominoClockwise(COUNTERCLOCKWISE);
			break;
		case 'I':
			turnTetrominoClockwise(COUNTERCLOCKWISE);
			break;

		// Drop
		case 'm':
			dropTetromino();
			break;
		case 'M':
			dropTetromino();
			break;
		default:
			break;
		}
	}
	
}

bool Board::isTetrominoMoving() {
	return currentTetromino.getIsMoving();
}

void Board::turnTetrominoLeft() {
	int* xCoordinates = currentTetromino.getXCoordinates();
	int* yCoordinates = currentTetromino.getYCoordinates();

	// Check for collision
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		if (gameBoard[yCoordinates[i]][xCoordinates[i] - 1] != ' ') {
			// Collision with right border or another block, do not move
			// Also check if an not empty block is part of the tetromino
			if (!currentTetromino.isContainCoordinates(yCoordinates[i], xCoordinates[i] - 1))
				return;
		}
	}

	// Clear filled rows
	clearBlocks();

	// Move left
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		currentTetromino.setXCoordinate(i, xCoordinates[i] - 1);
	}
}

void Board::turnTetrominoRight() {
	int* xCoordinates = currentTetromino.getXCoordinates();
	int* yCoordinates = currentTetromino.getYCoordinates();

	// Check for collision
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		if (gameBoard[yCoordinates[i]][xCoordinates[i] + 1] != ' ') {
			// Collision with right border or another block, do not move
			// Also check if an not empty block is part of the tetromino
			if (!currentTetromino.isContainCoordinates(yCoordinates[i], xCoordinates[i] + 1))
				return;
		}
	}

	// Clear filled rows
	clearBlocks();

	// Move right
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		currentTetromino.setXCoordinate(i, xCoordinates[i] + 1);
	}
}

void Board::turnTetrominoClockwise(int num) {
	int* xCoordinates = currentTetromino.getXCoordinates();
	int* yCoordinates = currentTetromino.getYCoordinates();

	Tetromino rotatedTetromino = currentTetromino;

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		int relativeX = xCoordinates[i] - xCoordinates[1];
		int relativeY = yCoordinates[i] - yCoordinates[1];

		// rotate clockwise or counterclockwise according to user's decision
		int newX = num * -relativeY;
		int newY = num * relativeX;

		// Update rotated tetromino coordinates
		rotatedTetromino.setXCoordinate(i, xCoordinates[1] + newX);
		rotatedTetromino.setYCoordinate(i, yCoordinates[1] + newY);
	}

	clearBlocks();

	int* newxCoordinates = rotatedTetromino.getXCoordinates();
	int* newyCoordinates = rotatedTetromino.getYCoordinates();

	// Check for collision
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		if (gameBoard[newyCoordinates[i]][newxCoordinates[i] + 1] != ' ') {
			// Collision with right border or another block, do not move
			// Also check if an not empty block is part of the tetromino
			// if (!currentTetromino.isContainCoordinates(yCoordinates[i], xCoordinates[i] + 1))
			return;
		}
	}


	currentTetromino = rotatedTetromino;
}

void Board::dropTetromino() {
	int* xCoordinates = currentTetromino.getXCoordinates();
	int* yCoordinates = currentTetromino.getYCoordinates();

	while (spaceBelowTetromino()) {
		// Drop tetromino
		for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
			currentTetromino.setYCoordinate(i, yCoordinates[i] + 1);
		}
	}


	printTetromino();
}

void Board::clearBlocks() {
	int* xCoordinates = currentTetromino.getXCoordinates();
	int* yCoordinates = currentTetromino.getYCoordinates();

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		gameBoard[yCoordinates[i]][xCoordinates[i]] = ' ';
	}
}

void Board::removeFullLines() {
	for (int y = DEFAULT_VALUE + 1; y < GameConfig::GAME_HEIGHT - 1; y++) {
		// If a line is full and no tetromino is moving, delete the line
		if (isLineFull(y) && !currentTetromino.getIsMoving()) {
			makeLineEmpty(y);
			moveEverythingDown(y);
			//************************************************************YARDEN**************************
			updateScoreOfPlayer(10);
		}
	}
}

bool Board::isLineFull(int y) {
	for (int x = DEFAULT_VALUE; x < GameConfig::GAME_WIDTH; x++) {
		if (gameBoard[y][x] == ' ')
			return false;
	}

	return true;
}

void Board::makeLineEmpty(int y) {
	for (int x = DEFAULT_VALUE; x < GameConfig::GAME_WIDTH; x++) {
		if (gameBoard[y][x] != GameConfig::BOARD_BORDER_CHAR)
			gameBoard[y][x] = ' ';
	}
}

void Board::moveTetrominoDown() {
	int* xCoordinates = currentTetromino.getXCoordinates();
	int* yCoordinates = currentTetromino.getYCoordinates();

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		if (gameBoard[yCoordinates[i] + 1][xCoordinates[i]] != ' ') {
			// Collision with right border or another block, do not move
			if (!currentTetromino.isContainCoordinates(yCoordinates[i] + 1, xCoordinates[i]))
				return;
		}
	}
	// Clear filled rows
	clearBlocks();

	// move tetromino down
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		currentTetromino.setYCoordinate(i, yCoordinates[i] + 1);
	}
}

void Board::printTetromino() {
	// Add tetromino to board
	int* xCoordinates = currentTetromino.getXCoordinates();
	int* yCoordinates = currentTetromino.getYCoordinates();

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		gameBoard[yCoordinates[i]][xCoordinates[i]] = GameConfig::TETRINOM_CHAR;
	}
}

void Board::moveEverythingDown(int y) {
	for (y = y-1; y > 1; y--) {
		for (int x = DEFAULT_VALUE; x < GameConfig::GAME_WIDTH; x++) {
			if (gameBoard[y][x] == GameConfig::TETRINOM_CHAR) {
				gameBoard[y + 1][x] = GameConfig::TETRINOM_CHAR;
				gameBoard[y][x] = ' ';
			}
		}
	}
}


//****************************************************YARDEN*****************
bool Board::isPlayerLost()
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		if (gameBoard[1][i] == GameConfig::TETRINOM_CHAR)
		{
			return true;
		}
	}
	return false;
}

void Board::setScores()
{
	score= 0;
}

int Board::getScore()
{
	return score;
}

void Board::updateScoreOfPlayer(int num)
{
	 score+=num;
}

void Board::printScore(int x, int y)
{
	gotoxy(x - 4, y - 1);
	if (x == GameConfig::FIRST_BOARD_X)
	{
		cout << "Score of player #1: " << getScore();
	}
	else
	{
		cout << "Score of player #2: " << getScore();
	}

}