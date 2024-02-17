#ifndef __COMPUTER_PLAYER_H
#define __COMPUTER_PLAYER_H

#include "Player.h"
#include "Board.h"
#include "Move.h"

class ComputerPlayer : public Player
{
	Move move; // move contains the best move the computer can make and data that can help it decide which of the moves is the best.
	int level = 0; //  the level of the computer

	//This method creates the best fit move for a type shape Tetromino.
	void createMove();

	//This method produces the defult move
	void createFirstMove();

	//This method the three functions under it
	void setIsLineFull_Rows_setSpaceInRows(Board& tmpBoard, Move& tmpMove);

	//This method checks if there is a full line in a certain move
	void setIsLineFull(Move& move);

	//This method updates the array of rows (int Move Class) that the shape contains and sorts it.
	void setRows(Board& curBoard, Move& curMove);

	//This method checks for each row that the shape contains the number of empty slots in the row
	//inserts it into the array. The array corresponds in its position to the row array.
	void setSpaceInRows(Board& curBoard, Move& curMove);

	//This method creates one by one all the possible moves of a certain shape, and chooses the best move.
	void createMovesAndChooseTheBest();

	//This method the number of possible appearances of a certain shape
	int getNumOfMutations() const;

	//This method builds the first steps for the move if the form has the possibility to appear in more performances.
	void createFirstsStepByTheShape(int i, Move& tmpMove, Board& tmpBoard);

	//This method builds the next possible move
	void createTheNextSteps(int col, Move& tmpMove, Board& tmpBoard);

	//This method returns the minimum column that contains the shape at a given moment.
	int minX() const;

	//This method compares two moves and updates the best move of the two
	void chooseTheBestMove(Move& tmpMove);

	//This method updates the player's keys if he is player 2
	char updateKeysForPlayer2(char res);

	// This methods causes the next step to be to the left/right/drop/colocwise/counterClockWise
	void leftStep(Board& tmpBoard);
	void rightStep(Board& tmpBoard);
	void dropStep(Board& tmpBoard);
	void clockWiseStep(Board& tmpBoard);
	void counterClockWiseStep(Board& tmpBoard);

	// This method gets a random number between 1 and "level" (10 or 40), and if its equal to the level its mean that new the cumputer need to miss;
	bool isMissMove() const;
	
	// This method gets a random number between 1 and 2, and if its equal to 1 the next step will be to the left Otherwise there will be a step to the right
	void createMissMove();

	//get method
	int getLevel() const { return level; }

	// this Method set the number of cuns that exploded in the and of bomb move
	void setnumOfExplodedCubs(Board& curBoard, Move& curMove);

	//This method compares two moves of bomb and updates the best move of the two
	void chooseMoveForBomb(Move& tmpMove);
	
	//This method compares two moves of tetromino and updates the best move of the two
	void chooseMoveForTetromino(Move& tmpMove);


public:

	Board& getBoard();

	//setMetod
	void setLevel(int level) { this->level = (int)level; }

	//This method creating the computer's move according to the board and the Tetromino shape or the bomb
	void setMove();

	//This method returns the key of the computer's move at a given moment
	void getKeyAndPerformAction(int player);

	//This method initializes the board data at the beginning of the game
	//and initializes the first move of the computer
	void setupBoard(bool isColor);

	// delete this method in the end
	//void PtintCheck(Board& tmpBoard);

	virtual void getKeyAndPerformAction(int player, char keyPressed) {};

};

#endif