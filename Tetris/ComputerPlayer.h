#ifndef __COMPUTER_PLAYER_H
#define __COMPUTER_PLAYER_H

#include "HumanPlayer.h"
#include "Board.h"
#include "Move.h"

class ComputerPlayer : public HumanPlayer
{
	Board board;
	//********************************yarden*******************************
	Move move; // move contains the best move the computer can make and data that can help it decide which of the moves is the best.
	int level = 0; //  the level of the computer
	int counter = 0; // counters of tetrominos from the start


public:

	//This method initializes the board data at the beginning of the game
	//and initializes the first move of the computer
	void setupBoard(bool isColor);
	//This method creating the computer's move according to the board and the Tetromino shape or the bomb
	void setmove();
	//This method creates the best fit move for a type shape Tetromino.
	void createMovesForTetromino();
	//This method produces the diplomatic move
	void createFirstMove();
	//This method checks if there is a full line in a certain move
	void setIsLineFull(Move& move);
	//This method updates the array of rows (int Move Class) that the shape contains and sorts it.
	void setRows(const Tetromino& curTetromino, Move& curMove);
	//This method checks for each row that the shape contains the number of empty slots in the row
	//inserts it into the array. The array corresponds in its position to the row array.
	void setSpaceInRows(Board& curBoard, Move& curMove);
	//This method creates one by one all the possible moves of a certain shape, and chooses the best move.
	void createMovesAndChooseTheBest();
	//This method the number of possible appearances of a certain shape
	int getNumOfMutations();
	//This method builds the first steps for the move if the form has the possibility to appear in more performances.
	void createFirstsStepByTheShape(int i, Move& tmpMove, Board& tmpBoard);
	//This method builds the next possible move
	void createTheNextSteps(int col, Move& tmpMove, Board& tmpBoard);
	//This method returns the minimum column that contains the shape at a given moment.
	int minX();
	//This method returns the maximum column that contains the shape at a given moment.
	int maxX();
	//This method compares two moves and updates the best move of the two
	void chooseTheBestMove(Move& tmpMove);
	//This method updates the player's keys if he is player 2
	void updateKeysForPlayer2();
	//This method returns the key of the computer's move at a given moment
	char getKey();

};

#endif

