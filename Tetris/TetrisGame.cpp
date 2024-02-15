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

using namespace std;

void TetrisGame::game() {
	char keyPressed = DEFAULT_VALUE;

	while (keyPressed != EXIT_GAME) {
		// Show menu and get key input from the user
		keyPressed = showMenu();

		// Move the user to the next section according to his decision
		switch (keyPressed)
		{
		// Player pressed human vs human game key
		case START_GAME_HVH:
			isGameOn = false;
			gameMode = HUMAN_VS_HUMAN;
			humanPlayersArray.resize(TWO);
			computerPlayersArray.resize(NONE);
			initGame();
			break;
		// Player pressed human vs computer game key
		case START_GAME_HVC:
			isGameOn = false;
			gameMode = HUMAN_VS_COMPUTER;
			humanPlayersArray.resize(ONE);
			computerPlayersArray.resize(ONE);
			initGame();
			break;
			// Player pressed computer vs computer game key
		case START_GAME_CVC:
			isGameOn = false;
			gameMode = COMPUTER_VS_COMPUTER;
			humanPlayersArray.resize(NONE);
			computerPlayersArray.resize(TWO);
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
	if(isGameOn)
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
	// Clear console screen
	clearScreen();

	// If there is no game going on, initialize new boards
	if (isGameOn == false) {
		initBoards();
		isGameOn = true;
	}
	
	while (true) {
		// Check if one of the tetrominos is not moving or none of the players has lost and act accordingly. 
		updateScoresRemoveLinesAddTetromino();

		// Print players' boards
		setupAndPrintBoards();

		// Check if there is space below the tetrominos. if not, the function will stop them from moving
		isSpaceBelowTetrominos();

		// Move tetrominos down if there is space below them
		moveTetrominosDown();

		//to Tal from Yarden
		//Just so that the program can run now - you can download after polymorphism.
		//If you recognize that don't tell me and make it nicer
		//int counter = 0;
		int counter = 0;
		for (auto& currComputer : computerPlayersArray)
		{
			// if humen vs comuter - computer = player 2
	        // if computer vs comuter computerPlayersArray[1] IS PLAYER2) 
	        // in both of the we need to Match the characters because they are matched to player 1
	        // Just to match the current program - delete after polymorphism:
			counter++;
			if ((gameMode == HUMAN_VS_COMPUTER) || (gameMode == COMPUTER_VS_COMPUTER && counter == 2))
			{
				currComputer.updateKeysForPlayer2();
			}
		}
			
			// Check for key press and navigate to the right function. if user pressed escape the game will pause
		if (getKeyAndPerformAction())
			return;

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

	// Stop the game and clearn the screen
	isGameOn = false;
	clearScreen();

	// Print winner
	printWinner();

	// Handle return to menu
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

	// Initialize board(s) of human player(s)
	for (auto& currPlayer : humanPlayersArray)
		currPlayer.setupBoard(isColor);

	// Initialize board(s) of computer player(s)
	for (auto& currComputer : computerPlayersArray)
		currComputer.setupBoard(isColor);
}

bool TetrisGame::getKeyAndPerformAction() {
	bool isTetrominoMoving = false;
	char keyPressed = DEFAULT_VALUE;
	int playerPressed = DEFAULT_VALUE;

	//update Humen 
	for (auto& currPlayer : humanPlayersArray)
	{

		// Check for key press and navigate to the right function
		if (_kbhit())
		{
			// Get key pressed
			keyPressed = _getch();

			// If player pressed escape, we shall return to the main menu.
			if (keyPressed == ESC)
				return true;

			// Check who pressed the key
			playerPressed = whoPressed(keyPressed);

			// Check if the player who pressed the key has a moving tetromino
			isTetrominoMoving = isPressedTetrominoMoving(playerPressed);

			if (isTetrominoMoving)
			{
				navigateToPerformAction(keyPressed, playerPressed);
			}
		}
	}
		
	//line 310 + 313: Just to match the current program - delete after polymorphism
	int counter = 0;
	for (auto& currComputer : computerPlayersArray)
	{
		if (_kbhit())
		{
			// Get key pressed
			keyPressed = _getch();

			// If player pressed escape, we shall return to the main menu.
			if (keyPressed == ESC)
				return true;
		}

		keyPressed = currComputer.getKey();
		if (keyPressed)
		{
			playerPressed = whoPressed(keyPressed);

			// Check if the player who pressed the key has a moving tetromino
			isTetrominoMoving = isPressedTetrominoMoving(playerPressed);

			if (isTetrominoMoving)
			{
				navigateToPerformAction(keyPressed, playerPressed);
			}
		}
	}



	return false;
}

void TetrisGame::isSpaceBelowTetrominos() {
	// Check if there is space below the tetrominos. if not, the function will stop them from moving
	for (auto& currPlayer : humanPlayersArray)
	{
		currPlayer.getBoard().spaceBelowTetromino();

	}
	for (auto& currComputer : computerPlayersArray)
	{
		currComputer.getBoard().spaceBelowTetromino();
	}
}

void TetrisGame::moveTetrominosDown() {
	for (auto& currPlayer : humanPlayersArray)
	{
		currPlayer.getBoard().moveTetrominoDown();

	}
	for (auto& currComputer : computerPlayersArray)
	{
		currComputer.getBoard().moveTetrominoDown();
	}
}

void TetrisGame::setupAndPrintBoards() {
	switch (gameMode)
	{
	case HUMAN_VS_HUMAN: // Human vs Human game
		humanPlayersArray[ZERO].getBoard().setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		humanPlayersArray[ONE].getBoard().setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
		break;
	case HUMAN_VS_COMPUTER: // Human vs Computer game
		humanPlayersArray[ZERO].getBoard().setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		computerPlayersArray[ZERO].getBoard().setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
		break;
	case COMPUTER_VS_COMPUTER: // Computer vs Computer game
		computerPlayersArray[ZERO].getBoard().setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		computerPlayersArray[ONE].getBoard().setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
		break;
	default:
		break;
	}
}

void TetrisGame::navigateToPerformAction(char keyPressed, int playerPressed) {
	switch (gameMode)
	{
	case HUMAN_VS_HUMAN: // Human vs Human game
		// Perform movement action
		if (playerPressed == PLAYER1) {
			humanPlayersArray[PLAYER1].performAction(keyPressed, playerPressed); 
		}
		if (playerPressed == PLAYER2) {
			humanPlayersArray[PLAYER2].performAction(keyPressed, playerPressed);
		}
		break;
	case HUMAN_VS_COMPUTER: // Human vs Computer game
		// Perform movement action
		if (playerPressed == PLAYER1) {
			//humanPlayersArray[PLAYER1].performAction(keyPressed, playerPressed);
		}
		if (playerPressed == PLAYER2) {
			//computerPlayersArray[PLAYER2 - ONE].performAction(keyPressed, playerPressed);
		}
		break;
	case COMPUTER_VS_COMPUTER: // Computer vs Computer game
		// Perform movement action
		if (playerPressed == PLAYER1) {
			computerPlayersArray[PLAYER1].performAction(keyPressed, playerPressed);
		}
		if (playerPressed == PLAYER2) {
			computerPlayersArray[PLAYER2].performAction(keyPressed, playerPressed);
		}
		break;
	default:
		break;
	}
}

bool TetrisGame::isLost() {
	switch (gameMode)
	{
	case HUMAN_VS_HUMAN: // Human vs Human game
		if (humanPlayersArray[PLAYER1].getBoard().isPlayerLost() || humanPlayersArray[PLAYER2].getBoard().isPlayerLost())
			return true;
		break;
	case HUMAN_VS_COMPUTER: // Human vs Computer game
		if (humanPlayersArray[PLAYER1].getBoard().isPlayerLost() || computerPlayersArray[PLAYER2 - ONE].getBoard().isPlayerLost())
			return true;
		break;
	case COMPUTER_VS_COMPUTER: // Computer vs Computer game
		if (computerPlayersArray[PLAYER1].getBoard().isPlayerLost() || computerPlayersArray[PLAYER2 - ONE].getBoard().isPlayerLost())
			return true;
	default:
		break;
	}

	return false;
}

void TetrisGame::updateScoresRemoveLinesAddTetromino() {
	for (auto& currPlayer : humanPlayersArray)
	{
		Board& currBoard = currPlayer.getBoard();
		if (!currBoard.isTetrominoMoving())
		{
			if (!currBoard.isPlayerLost())
			{
				currBoard.updateScoreOfPlayer(STARTING_SCORE);
				currBoard.removeFullLines();
				currBoard.addTetromino();
			}
		}
	}
	for (auto& currComputer : computerPlayersArray)
	{
		Board& currBoard = currComputer.getBoard();
		if (!currBoard.isTetrominoMoving())
		{   		
			//tal - check why return false in the first run of the game after initBaorde();
			if (!currBoard.isPlayerLost())
			{   
				//FORNOW
	            currBoard.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
	            currBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);

				currBoard.updateScoreOfPlayer(STARTING_SCORE);
				currBoard.removeFullLines();
				currBoard.addTetromino();
				currComputer.setmove();
			}
		}
	}
}

void TetrisGame::printWinner(){
	int player1Score = DEFAULT_VALUE;
	int player2Score = DEFAULT_VALUE;
	bool isPlayer1Lost = false;
	bool isPlayer2Lost = false;

	// Check if players lost and get their scores
	switch (gameMode)
	{
	case HUMAN_VS_HUMAN: // Human vs Human game
		isPlayer1Lost = humanPlayersArray[PLAYER1].getBoard().isPlayerLost();
		player1Score = humanPlayersArray[PLAYER1].getBoard().getScore();
		isPlayer2Lost = humanPlayersArray[PLAYER2].getBoard().isPlayerLost();
		player2Score = humanPlayersArray[PLAYER2].getBoard().getScore();
		break;
	case HUMAN_VS_COMPUTER: // Human vs Computer game
		isPlayer1Lost = humanPlayersArray[PLAYER1].getBoard().isPlayerLost();
		player1Score = humanPlayersArray[PLAYER1].getBoard().getScore();
		isPlayer2Lost = computerPlayersArray[PLAYER2 - ONE].getBoard().isPlayerLost();
		player2Score = computerPlayersArray[PLAYER2 - ONE].getBoard().getScore();
		break;
	case COMPUTER_VS_COMPUTER: // Computer vs Computer game
		isPlayer1Lost = computerPlayersArray[PLAYER1].getBoard().isPlayerLost();
		player1Score = computerPlayersArray[PLAYER1].getBoard().getScore();
		isPlayer2Lost = computerPlayersArray[PLAYER2].getBoard().isPlayerLost();
		player2Score = computerPlayersArray[PLAYER2].getBoard().getScore();
		break;
	default:
		break;
	}

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

bool TetrisGame::isPressedTetrominoMoving(int playerPressed) {
	switch (gameMode)
	{
	case HUMAN_VS_HUMAN: // Human vs Human game
		return humanPlayersArray[playerPressed].getBoard().isTetrominoMoving();
		break;
	case HUMAN_VS_COMPUTER: // Human vs Computer game
		if(playerPressed == PLAYER1)
			return humanPlayersArray[playerPressed].getBoard().isTetrominoMoving();
		else
			return computerPlayersArray[playerPressed - ONE].getBoard().isTetrominoMoving();
		break;
	case COMPUTER_VS_COMPUTER: // Computer vs Computer game
		return computerPlayersArray[playerPressed].getBoard().isTetrominoMoving();
		break;
	default:
		break;
	}
	return false;
}


