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
#define LEFT -1
#define RIGHT 1
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1
#define SECOND_POINT 1
#define ADDED_PIECE 10
#define EMPTY_CHAR ' '
#define NUM_OF_PLAYERS 2
#define BOMB_POINTS_ARRAY 1
#define NORMAL_SHAPE_ARRAY 4
#define FIRST_INDEX 0
#define ONE 1
#define MAX_BLAST_RADIUS_LEFT -4
#define MAX_BLAST_RADIUS_RIGHT 5

using namespace std;

Board::Board()
{
	// The board will be initialized to be an "empty board".
	//The background color of the board will be reset entirely to black.
	initBoard();
	score = DEFAULT_VALUE;
	backgroundColor = GameConfig::COLORS[0];
	isColor = false;
}

void Board::initBoard() {

	// set the colors matrix to black
	initColorByLocation();

	// Set characters in the board
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++) {
		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			if (i == DEFAULT_VALUE || i == (GameConfig::GAME_HEIGHT - 1) || j == 0 || j == (GameConfig::GAME_WIDTH - 1)) {
				gameBoard[i][j] = GameConfig::BOARD_BORDER_CHAR;
			}
			else
				gameBoard[i][j] = EMPTY_CHAR;
		}
	}
}

void Board::addTetromino() {
	// Add coordinates value to tetromino
	currentTetromino.setIsMoving(true);

	// Decide if the next tetromino will be a bomb or not
	if (isBomb()) {
		currentTetromino.setShape((int)GameConfig::eShapes::Bomb);
		currentTetromino.setPointsArraySize(BOMB_POINTS_ARRAY);
		currentTetromino.setXCoordinate(FIRST_INDEX, 5);
		currentTetromino.setYCoordinate(FIRST_INDEX, 1);
		setBackgroundColor(GameConfig::COLORS[8]);
		return;
	}

	// If not a bomb, Generate a random number between 1 and 7 that will decide the shape
	GameConfig::eShapes shape = (GameConfig::eShapes)(rand() % 7 + 1);
	currentTetromino.setPointsArraySize(NORMAL_SHAPE_ARRAY);
	currentTetromino.setShape((int)shape);

	//set the shape and color of the tetromino
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

	//// Add coordinates value to tetromino
	currentTetromino.setIsMoving(true);
}

bool Board::spaceBelowTetromino(bool isComputerCheck) {
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;
	size_t numOfCordinates = currentTetromino.getVecSize();

	for (int i = DEFAULT_VALUE; i < numOfCordinates; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		// If the board has a character below a certain tetromino coordinate, and also it's not
		// the tetromino's character, return false and set tetromino to stop moving.
		// If the tetromino is a bomb, explode it
		if (gameBoard[y + 1][x] != EMPTY_CHAR && !currentTetromino.isContainCoordinates(y + 1, x)) {
			//Check if the tetromino was a bomb. if it is, explode it.
			if (isCurrentShapeBomb() && !isComputerCheck)
				explodeBomb();
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
			turnTetrominoLeftOrRight(LEFT);
			break;
		case 'A':
			turnTetrominoLeftOrRight(LEFT);
			break;
			// Go Right
		case 'd':
			turnTetrominoLeftOrRight(RIGHT);
			break;
		case 'D':
			turnTetrominoLeftOrRight(RIGHT);
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
			turnTetrominoLeftOrRight(LEFT);
			break;
		case 'J':
			turnTetrominoLeftOrRight(LEFT);
			break;

			// Go Right
		case 'l':
			turnTetrominoLeftOrRight(RIGHT);
			break;
		case 'L':
			turnTetrominoLeftOrRight(RIGHT);
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

bool Board::isTetrominoMoving() const {
	return currentTetromino.getIsMoving();
}

void Board::turnTetrominoLeftOrRight(int num) {
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;
	size_t numOfCordinates = currentTetromino.getVecSize();

	// Check for collision
	for (int i = DEFAULT_VALUE; i < numOfCordinates; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		if (gameBoard[y][x + num] != EMPTY_CHAR) {
			// Collision with right border or another block, do not   
			// Also check if an not empty block is part of the tetromino
			if (!currentTetromino.isContainCoordinates(y, x + num) || gameBoard[y][x + num] == GameConfig::BOARD_BORDER_CHAR)
				return;
		}
	}

	// Clear filled rows
	clearBlocks();

	// Move left
	for (int i = DEFAULT_VALUE; i < numOfCordinates; i++) {
		x = currentTetromino.getXCoordinate(i);

		currentTetromino.setXCoordinate(i, x + num);
	}
}

void Board::turnTetrominoClockwise(int num) {
	// Don't perform function for squared shape or bomb
	int shape = currentTetromino.getShape();
	if (shape == (int)GameConfig::eShapes::Square || shape == (int)GameConfig::eShapes::Bomb)
		return;

	int x = DEFAULT_VALUE, xSecond = currentTetromino.getXCoordinate(SECOND_POINT);
	int y = DEFAULT_VALUE, ySecond = currentTetromino.getYCoordinate(SECOND_POINT);
	size_t numOfCoordinates = currentTetromino.getVecSize();

	Tetromino rotatedTetromino = currentTetromino;

	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
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

	// Check for collision
	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
		// Fetch the x and y coordinates of the new point
		x = rotatedTetromino.getXCoordinate(i);
		y = rotatedTetromino.getYCoordinate(i);

		if (gameBoard[y][x] != EMPTY_CHAR) {
			return;
		}
	}

	clearBlocks();

	currentTetromino = rotatedTetromino;
}

void Board::dropTetromino() {
	int y = DEFAULT_VALUE;
	size_t numOfCoordinates = currentTetromino.getVecSize();

	while (spaceBelowTetromino(false)) {
		// Drop tetromino
		for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
			y = currentTetromino.getYCoordinate(i);
			currentTetromino.setYCoordinate(i, y + 1);
		}
	}
	if (!isCurrentShapeBomb())
		printTetromino();
}

void Board::clearBlocks() {
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;
	size_t numOfCoordinates = currentTetromino.getVecSize();


	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		gameBoard[y][x] = EMPTY_CHAR;

		//after we clear the blocks we need to update the background color to black
		updateColorByLocation(y, x, GameConfig::COLORS[0]);
	}
}

void Board::removeFullLines() {
	for (int y = DEFAULT_VALUE + 1; y < GameConfig::GAME_HEIGHT - 1; y++) {
		// If a line is full and no tetromino is moving, delete the line
		if (isLineFull(y) && !currentTetromino.getIsMoving()) {
			makeLineEmpty(y);
			moveEverythingDown(y);
			updateScoreOfPlayer(ADDED_PIECE);
		}
	}
}

bool Board::isLineFull(int y) const {
	for (int x = DEFAULT_VALUE; x < GameConfig::GAME_WIDTH; x++) {
		if (gameBoard[y][x] == EMPTY_CHAR)
			return false;
	}

	return true;
}

void Board::makeLineEmpty(int y) {
	for (int x = DEFAULT_VALUE; x < GameConfig::GAME_WIDTH; x++) {
		if (gameBoard[y][x] != GameConfig::BOARD_BORDER_CHAR) {
			gameBoard[y][x] = EMPTY_CHAR;
			//update the line to background color black
			updateColorByLocation(y, x, GameConfig::COLORS[0]);
		}

	}
}

void Board::moveTetrominoDown() {
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;
	size_t numOfCoordinates = currentTetromino.getVecSize();

	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		if (gameBoard[y + 1][x] != EMPTY_CHAR) {
			// Collision with right border or another block, do not move
			if (!currentTetromino.isContainCoordinates(y + 1, x))
				return;
		}
	}
	// Clear filled rows
	clearBlocks();

	// move tetromino down
	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);

		// Update coordinates and colors
		currentTetromino.setYCoordinate(i, y + 1);
		updateColorByLocation(y + 1, x, getBackgroundColor());
	}
}

void Board::printTetromino() {
	// Add tetromino to board
	int x = DEFAULT_VALUE;
	int y = DEFAULT_VALUE;
	size_t numOfCoordinates = currentTetromino.getVecSize();
	int backGroundColor = getBackgroundColor();

	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
		x = currentTetromino.getXCoordinate(i);
		y = currentTetromino.getYCoordinate(i);
		gameBoard[y][x] = GameConfig::TETROMINO_CHAR;
		// update the background color of the blocks of the tetromino
		colorByLocation[y][x] = backGroundColor;
	}
}


void Board::moveEverythingDown(int y) {
	for (y = y - 1; y > 1; y--) {
		for (int x = DEFAULT_VALUE; x < GameConfig::GAME_WIDTH; x++) {
			if (gameBoard[y][x] == GameConfig::TETROMINO_CHAR) {
				gameBoard[y + 1][x] = GameConfig::TETROMINO_CHAR;
				updateColorByLocation(y + 1, x, colorByLocation[y][x]);
				gameBoard[y][x] = EMPTY_CHAR;
				updateColorByLocation(y, x, GameConfig::COLORS[0]);
			}
		}
	}
}

Tetromino Board::getCurrentTetromino() const {
	return currentTetromino;
}

bool Board::isPlayerLost() const
{
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_WIDTH; i++)
	{
		// if there is a TETROMINO_CHAR in the in the highest row of the board it means that the player has lost.
		if (gameBoard[1][i] == GameConfig::TETROMINO_CHAR && !currentTetromino.getIsMoving())
		{
			return true;
		}
	}
	return false;
}


void Board::setScores()
{
	//set score to zero.
	score = DEFAULT_VALUE;
}

int Board::getScore() const
{
	return score;
}


void Board::updateScoreOfPlayer(int num)
{
	score += num;
}

void Board::printScore(int x, int y) const
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

void Board::whatColor(int color) const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Board::setupAllAndPrintBoard(int x, int y) {
	// Print message above the boards
	gotoxy(GameConfig::TETRIS_MSG_X, GameConfig::TETRIS_MSG_Y);
	cout << "TETRIS";

	// Print players' scores
	printScore(x, y);

	// Print tetromino characters
	printTetromino();

	// Print board according to user's choice of colors
	if (isColor) {
		printBoardWithColors(x, y);
	}
	else {
		printBoardWithoutColors(x, y);
	}
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
	colorByLocation[x][y] = color;
}

void Board::setBackgroundColor(int color)
{
	backgroundColor = color;
}

int Board::getBackgroundColor() const
{
	return backgroundColor;
}

void Board::printBoardWithColors(int x, int y) const
{
	for (int i = DEFAULT_VALUE; i < GameConfig::GAME_HEIGHT; i++) {
		for (int j = DEFAULT_VALUE; j < GameConfig::GAME_WIDTH; j++) {
			gotoxy(x + j, y + i);

			//if there is a TETROMINO_CHAR then print with color.
			if (gameBoard[i][j] == EMPTY_CHAR || gameBoard[i][j] == GameConfig::BOARD_BORDER_CHAR) {
				whatColor(GameConfig::COLORS[0]);
			}
			else {
				whatColor(colorByLocation[i][j]);
			}
			cout << gameBoard[i][j];
		}

		//after printing the board with the colors, return the print color to be black
		whatColor(GameConfig::COLORS[0]);
		cout << endl;
	}
}

void Board::printBoardWithoutColors(int x, int y) const
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

int Board::getNumOfSpaceInLine(int line) const
{
	int res = 0;
	for (int i = 1; i < GameConfig::GAME_WIDTH - 1; i++)
	{
		if (gameBoard[line][i] == EMPTY_CHAR)
		{
			res++;
		}
	}
	return res;

}

int Board::numOfExplodedCubs() const
{
	int numOfExplodedCubs = DEFAULT_VALUE;
	int x = currentTetromino.getXCoordinate(FIRST_INDEX);
	int y = currentTetromino.getYCoordinate(FIRST_INDEX);

	for (int i = 4; i > -5; i--) 
	{ // Go from bottom to up in the y-axis
		for (int j = MAX_BLAST_RADIUS_LEFT; j < MAX_BLAST_RADIUS_RIGHT; j++)
		{
			if (isInBoard(x + j, y + i))
			{
				if (gameBoard[y + i][x + j] == GameConfig::TETROMINO_CHAR) 
				{
					numOfExplodedCubs++;
				}
				
			}
		}
	}

	return numOfExplodedCubs;
}


bool Board::isBomb() const {
	int num = (rand() % 100 + 1);

	// Get a bomb at 5% chance as required
	if (num > 95)
		return true;

	return false;
}

bool Board::isCurrentShapeBomb() const {
	if (currentTetromino.getShape() == (int)GameConfig::eShapes::Bomb)
		return true;

	return false;
}

void Board::explodeBomb() {

	int x = currentTetromino.getXCoordinate(FIRST_INDEX);
	int y = currentTetromino.getYCoordinate(FIRST_INDEX);
	bool moveDown1 = false;
	bool moveDown2 = false;
	bool moveDown3 = false;

	// Bomb explosion
	for (int i = 4; i > -5; i--) { // Go from bottom to up in the y-axis
		for (int j = MAX_BLAST_RADIUS_LEFT; j < MAX_BLAST_RADIUS_RIGHT; j++) {
			if (isInBoard(x + j, y + i)) {
				if (gameBoard[y + i][x + j] == GameConfig::TETROMINO_CHAR) {
					// Make Empty
					gameBoard[y + i][x + j] = EMPTY_CHAR;

					//update the cell to background color black
					updateColorByLocation(y + i, x + j, GameConfig::COLORS[0]);

					// Move every block above it down
					if (i == MAX_BLAST_RADIUS_LEFT)
						moveAboveDown(x + j, y + i);
				}
			}
		}
	}
}

void Board::moveAboveDown(int x, int y) {
	vector<char> charArr;
	vector<int> colorArr;
	int height = DEFAULT_VALUE;
	int defaultColor = getBackgroundColor();
	int ind = 0;

	// Check if there is any block above to move to even start the algorithm
	if (gameBoard[y - 1][x] != GameConfig::TETROMINO_CHAR)
		return;

	// Get the height that we'll need to get them down to
	while (gameBoard[y + ind][x] == EMPTY_CHAR) {
		height++;
		ind++;
	}

	// Get the vectors of characters and colors of the cells we'd like to move down
	ind = 1;
	while (gameBoard[y - ind][x] == GameConfig::TETROMINO_CHAR) {
		// Push characters and remove it from the board
		charArr.push_back(gameBoard[y - ind][x]);
		gameBoard[y - ind][x] = EMPTY_CHAR;

		// Push color and remove it from the board
		colorArr.push_back(colorByLocation[y - ind][x]);
		colorByLocation[y - ind][x] = defaultColor;

		ind++;
	}

	// Get Vector size
	int vecSize = charArr.size();

	// Insert the vector to his new place
	ind = 1;
	for (int i = DEFAULT_VALUE; i < vecSize; i++) {
		gameBoard[y + height - ind][x] = charArr[i];
		colorByLocation[y + height - ind][x] = colorArr[i];
		ind++;
	}
}

size_t Board::getCurrentTetrominoVecSize() const {
	return this->currentTetromino.getVecSize();
}

bool Board::isInBoard(int x, int y) const
{
	if (x < ONE || x > GameConfig::GAME_WIDTH - 2)
		return false;
	if (y < ONE || y > GameConfig::GAME_HEIGHT - 2)
		return false;

	return true;
}