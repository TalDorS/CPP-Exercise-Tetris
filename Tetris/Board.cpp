#include "Board.h"
#include "General.h"
#include "GameConfig.h"
#include "Tetromino.h"
#include "TetrisGame.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

#define DEFAULT_VALUE 0
#define NUM_OF_COORDINATES 4
#define PLAYER1 0
#define PLAYER2 1
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1
#define SECOND_POINT 1

using namespace std;

void Board::initBoard() {

	//yarden
	initColorByLocation();

	// Set characters in the board
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++) {
		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			if (i == DEFAULT_VALUE || i == (GameConfig::GAME_HEIGHT - 1) || j == 0 || j == (GameConfig::GAME_WIDTH - 1)) {
				gameBoard[i][j] = GameConfig::BOARD_BORDER_CHAR;
			}
			else
				gameBoard[i][j] = ' ';
		}
	}
}

void Board::printBoard(int x, int y) {
	// Print message above the boards
	gotoxy(GameConfig::TETRIS_MSG_X, GameConfig::TETRIS_MSG_Y);
	cout << "TETRIS";

	// Print players' scores
	printScore(x, y);

	// Print tetromino characters
	printTetromino();

	// Print board according to user's choice of colors
	if (isColor) {
		printWithColors(x, y);
	}
	else{
		printWithoutColors(x, y);
	}



	/*
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++) {
		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			gotoxy(x + j, y + i);
			//yarden
			if (gameBoard[i][j] == ' ' || gameBoard[i][j] == GameConfig::BOARD_BORDER_CHAR){
				setColor(GameConfig::COLORS[0]);
			}
			else{
				setColor(colorByLocation[i][j]);
			}
			cout << gameBoard[i][j];
		}
		//yarden
		setColor(GameConfig::COLORS[0]);
		cout << endl;
	}
	*/
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
		setBackgroundColor(GameConfig::COLORS[1]);
		break;
	case GameConfig::eShapes::Square: // Square Tetromino
		currentTetromino.setXCoordinates(4, 5, 4, 5);
		currentTetromino.setYCoordinates(1, 1, 2, 2);
		setBackgroundColor(GameConfig::COLORS[2]);
		break;
	case GameConfig::eShapes::TShaped: // T shaped Tetromino
		currentTetromino.setXCoordinates(4, 5, 6, 5);
		currentTetromino.setYCoordinates(1, 1, 1, 2);
		setBackgroundColor(GameConfig::COLORS[3]);
		break;
	case GameConfig::eShapes::LShaped: // L shaped Tetromino
		currentTetromino.setXCoordinates(4, 4, 4, 5);
		currentTetromino.setYCoordinates(1, 2, 3, 3);
		setBackgroundColor(GameConfig::COLORS[4]);
		break;
	case GameConfig::eShapes::SShaped: // S shaped Tetromino
		currentTetromino.setXCoordinates(4, 5, 5, 6);
		currentTetromino.setYCoordinates(2, 2, 1, 1);
		setBackgroundColor(GameConfig::COLORS[5]);
		break;
	case GameConfig::eShapes::JShaped: // J shaped Tetromino
		currentTetromino.setXCoordinates(5, 5, 5, 4);
		currentTetromino.setYCoordinates(1, 2, 3, 3);
		setBackgroundColor(GameConfig::COLORS[6]);
		break;
	case GameConfig::eShapes::ZShaped: // Z shaped Tetromino
		currentTetromino.setXCoordinates(4, 5, 5, 6);
		currentTetromino.setYCoordinates(1, 1, 2, 2);
		setBackgroundColor(GameConfig::COLORS[7]);
		break;
	default:
		break;
	}

	// Add coordinates value to tetromino
	currentTetromino.setIsMoving(true);
}

bool Board::spaceBelowTetromino() {
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

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
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;

	// Check for collision
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		if (gameBoard[y][x - 1] != ' ') {
			// Collision with right border or another block, do not move
			// Also check if an not empty block is part of the tetromino
			if (!currentTetromino.isContainCoordinates(y, x - 1))
				return;
		}
	}

	// Clear filled rows
	clearBlocks();

	// Move left
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);

		currentTetromino.setXCoordinate(i, x - 1);
	}
}

void Board::turnTetrominoRight() {
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;

	// Check for collision
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		if (gameBoard[y][x + 1] != ' ') {
			// Collision with right border or another block, do not move
			// Also check if an not empty block is part of the tetromino
			if (!currentTetromino.isContainCoordinates(y, x + 1))
				return;
		}
	}

	// Clear filled rows
	clearBlocks();

	// Move right
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);

		currentTetromino.setXCoordinate(i, x + 1);
	}
}

void Board::turnTetrominoClockwise(int num) {
	int x = DEFAULT_VALUE, xSecond = currentTetromino.getXCoordinate(SECOND_POINT);
	int y = DEFAULT_VALUE, ySecond = currentTetromino.getYCoordinate(SECOND_POINT);

	Tetromino rotatedTetromino = currentTetromino;

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		// Fetch the x and y coordinates of the current point
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);
		
		// Get the relative x and y values of the current point to the second point in the shape
		int relativeX = x - xSecond;
		int relativeY = y - ySecond;

		// rotate clockwise or counterclockwise according to user's decision
		int newX = num * -relativeY;
		int newY = num * relativeX;

		// Update rotated tetromino coordinates
		rotatedTetromino.setXCoordinate(i, xSecond + newX);
		rotatedTetromino.setYCoordinate(i, ySecond + newY);
	}

	clearBlocks();

	// Check for collision
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		// Fetch the x and y coordinates of the new point
		x = rotatedTetromino.getXCoordinate(i);
		y = rotatedTetromino.getYCoordinate(i);

		if (gameBoard[y][x + 1] != ' ') {
			// Collision with right border or another block, do not move
			// Also check if an not empty block is part of the tetromino
			// if (!currentTetromino.isContainCoordinates(yCoordinates[i], xCoordinates[i] + 1))
			return;
		}
	}


	currentTetromino = rotatedTetromino;
}

void Board::dropTetromino() {
	int y = DEFAULT_VALUE;

	while (spaceBelowTetromino()) {
		// Drop tetromino
		for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
			y = currentTetromino.getYCoordinate(i);

			currentTetromino.setYCoordinate(i, y + 1);
		}
	}


	printTetromino();
}

void Board::clearBlocks() {
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		gameBoard[y][x] = ' ';

		//yarden**********************************************************
		updateColorByLocation(y, x, GameConfig::COLORS[0]);
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
		//yarden
		updateColorByLocation(y, x, GameConfig::COLORS[0]);

	}
}

void Board::moveTetrominoDown() {
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		if (gameBoard[y + 1][x] != ' ') {
			// Collision with right border or another block, do not move
			if (!currentTetromino.isContainCoordinates(y + 1, x))
				return;
		}
	}
	// Clear filled rows
	clearBlocks();

	// move tetromino down
	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		currentTetromino.setYCoordinate(i, y + 1);
		updateColorByLocation(x, y + 1, getBackgroundColor());

	}
}

void Board::printTetromino() {
	// Add tetromino to board
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;

	for (int i = DEFAULT_VALUE; i < NUM_OF_COORDINATES; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);
		gameBoard[y][x] = GameConfig::TETROMINO_CHAR;
		//****************************************************YARDEN*****************
		colorByLocation[y][x] = getBackgroundColor();
	}
}

void Board::moveEverythingDown(int y) {
	for (y = y-1; y > 1; y--) {
		for (int x = DEFAULT_VALUE; x < GameConfig::GAME_WIDTH; x++) {
			if (gameBoard[y][x] == GameConfig::TETROMINO_CHAR) {
				gameBoard[y + 1][x] = GameConfig::TETROMINO_CHAR;
				//yarden
				updateColorByLocation(y + 1, x, colorByLocation[y][x]);

				gameBoard[y][x] = ' ';
				//yarden
				updateColorByLocation(y + 1, x, GameConfig::COLORS[0]);
			}
		}
	}
}

Tetromino Board::getCurrentTetromino() {
	return currentTetromino;
}

//****************************************************YARDEN*****************
bool Board::isPlayerLost()
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		if (gameBoard[1][i] == GameConfig::TETROMINO_CHAR && !currentTetromino.getIsMoving())
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

void Board::WhatColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Board::initColorByLocation()
{
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++)
	{

		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			colorByLocation[i][j] = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
		}

	}
}

void Board::updateColorByLocation(int x, int y, int color)
{
	colorByLocation[x][y] =color;
}

void Board::setBackgroundColor(int color)
{
	backgroundColor = color;
}

int Board::getBackgroundColor()
{
	return backgroundColor;
}

void Board::printWithColors(int x, int y)
{
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++) {
		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			gotoxy(x + j, y + i);
			//yarden
			if (gameBoard[i][j] == ' ' || gameBoard[i][j] == GameConfig::BOARD_BORDER_CHAR) {
				WhatColor(GameConfig::COLORS[0]);
			}
			else {
				WhatColor(colorByLocation[i][j]);
			}
			cout << gameBoard[i][j];
		}
		//yarden
		WhatColor(GameConfig::COLORS[0]);
		cout << endl;
	}
}

void Board::printWithoutColors(int x,int y)
{
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++) {
		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			gotoxy(x + j, y + i);			
			cout << gameBoard[i][j];
		}
		cout << endl;
	}
}

void Board::setIsColor(bool isColor) {
	this->isColor = isColor;
}

