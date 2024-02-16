#include "ComputerPlayer.h"
#include "General.h"

#define DEFAULT_VALUE 0
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1
#define LEFT -1
#define RIGHT 1
#define C_LEFT 'a'
#define C_RIGHT 'd'
#define C_CLOCKWISE 's'
#define C_COUNTERCLOCKWISE 'w'
#define C_DROP 'x'
#define EMPTY_CHAR ' '
#define PLAYER1 0
#define PLAYER2 1
#define BEST 0
#define GOOD 40
#define NOVICE 10


Board& ComputerPlayer::getBoard() {
	return this->board;
}
void ComputerPlayer::setupBoard(bool isColor) {
	// Initialize board colors
	this->board.setIsColor(isColor);

	// Initialize boards
	this->board.initBoard();

	// Set player's score to zero
	this->board.setScores();

	//Add a new tetromino shape to the board
	this->board.addTetromino();

	// ***********************************yarden
	this->setmove();
}

void ComputerPlayer::setmove()
{
	//make emty move
	move.setStep(0);
	move.initMove();

	//if the computer is not in level BEST	- CHECK 
	//withing for tal to finish is part
	if (level != BEST)
	{
		if (isMissMove())
		{
			createMissMove();
			return;
		}

	}
	//

	//if (board.isCurrentShapeBomb())
	//{
		//createMovesForBomb();//TODO
	//}
	//else
	//{
	createMovesForTetromino();
	//}

	move.setStep(0);


}

void ComputerPlayer::createMovesForTetromino()
{
	createFirstMove();

	createMovesAndChooseTheBest();

	//FORNOW - Currently in a note - do not touch
	//board.getCurrentTetromino().setIsMoving(true);
	//move.setStep(0);

}

void ComputerPlayer::createFirstMove()
{
	Board tmpBoard = board;

	//FORNOW
	//PtintCheck(tmpBoard);

	int index = 0;
	int minXVal = minX();
	while ((minXVal != 1) && (tmpBoard.spaceBelowTetromino() == true))
	{
		leftStep(tmpBoard);
		move.setCurrentStep(index, C_LEFT);
		index++;
		minXVal--;

		//FORNOW 
		//PtintCheck(tmpBoard);
	}

	dropStep(tmpBoard);
	move.setCurrentStep(index, C_DROP);

	//FORNOW
	//PtintCheck(tmpBoard);

	setIsLineFull_Rows_setSpaceInRows(tmpBoard, move);

}

void ComputerPlayer::setIsLineFull(Move& move)
{
	size_t numOfCoordinates = board.getCurrentTetrominoVecSize();
	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
		if (board.isLineFull(board.getCurrentTetromino().getYCoordinate(i)))
		{
			move.setIsLineFull(true);
			return;
		}
	}
	move.setIsLineFull(false);
}

void ComputerPlayer::setRows(Board& curBoard, Move& curMove)
{
	size_t numOfCoordinates = board.getCurrentTetrominoVecSize();
	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++)
	{
		int row = curBoard.getCurrentTetromino().getYCoordinate(i);
		curMove.setRow(i, row);

	}
	bubbleSort(curMove.getRowsAddress(), numOfCoordinates);


}

void ComputerPlayer::setSpaceInRows(Board& curBoard, Move& curMove)
{
	size_t numOfCoordinates = board.getCurrentTetrominoVecSize();
	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++)
	{
		int numOfSpaces = curBoard.getNumOfSpaceInLine(curMove.getRow(i));
		curMove.setSpaceInRow(i, numOfSpaces);

		while (curMove.getRow(i) == curMove.getRow(i + 1) && i < 3)
		{
			curMove.setSpaceInRow(i + 1, numOfSpaces);
			i++;
		}
	}

}

void ComputerPlayer::createMovesAndChooseTheBest()
{
	// save the next move and compare it to the object's move
	int numOfMutations = getNumOfMutations();
	for (int i = 0; i < numOfMutations; i++)
	{
		//for each col we build a move
		for (int col = 1; col < GameConfig::GAME_WIDTH - 2; col++)
		{
			Move tmpMove;
			Board tmpBoard = board;
			tmpMove.setStep(0);// make share we are in move[0]
			tmpMove.initMove(); // make share the move is empty
			createFirstsStepByTheShape(i, tmpMove, tmpBoard);
			createTheNextSteps(col, tmpMove, tmpBoard);
			chooseTheBestMove(tmpMove);

		}
	}
}

int ComputerPlayer::getNumOfMutations() const
{
	if (board.getCurrentTetromino().getShape() == 2 || board.getCurrentTetromino().getShape() == 8)
	{
		return 1;
	}
	else if (board.getCurrentTetromino().getShape() == 1 || board.getCurrentTetromino().getShape() == 5 || board.getCurrentTetromino().getShape() == 7)
	{
		return 2;
	}
	else
	{
		return 4;
	}
}

void ComputerPlayer::createFirstsStepByTheShape(int i, Move& tmpMove, Board& tmpBoard)
{
	int index = 0;
	tmpBoard.printTetromino();
	tmpMove.setStep(0);// make share we are in move[0]

	if (tmpBoard.spaceBelowTetromino() == true)
	{
		switch (i)
		{
		case (1):
			//first step - one time CLOCKWISE
			clockWiseStep(tmpBoard);
			tmpMove.setCurrentStep(index, C_CLOCKWISE);
			tmpMove.setStep(index + 1);
			//FORNOW
			//PtintCheck(tmpBoard);
			break;
		case (2):
			//first two step - twice CLOCKWISE
			clockWiseStep(tmpBoard);
			tmpMove.setCurrentStep(index, C_CLOCKWISE);
			tmpMove.setStep(index + 1);
			if (tmpBoard.spaceBelowTetromino() == true)
			{
				index++;
				clockWiseStep(tmpBoard);
				tmpMove.setCurrentStep(index, C_CLOCKWISE);
				tmpMove.setStep(index + 1);
			}
			//FORNOW
			//PtintCheck(tmpBoard); 
			break;
		case (3):
			//first step - one time COUNTERCLOCKWISE
			counterClockWiseStep(tmpBoard);
			tmpMove.setCurrentStep(index, C_COUNTERCLOCKWISE);
			tmpMove.setStep(index + 1);
			//FORNOW
			//PtintCheck(tmpBoard); 
		default:
			break;
		}
	}
}


void ComputerPlayer::createTheNextSteps(int col, Move& tmpMove, Board& tmpBoard)
{
	//FORNOW 
	//PtintCheck(tmpBoard);

	int minXVal = minX();
	int index = tmpMove.getStep();

	//If the col number is less than the minimum number of columns of the shape,
	//we will create a move to the left until we reach a column
	if (minXVal > col)
	{
		while ((minXVal > col) && (tmpBoard.spaceBelowTetromino() == true))
		{
			leftStep(tmpBoard);
			tmpMove.setCurrentStep(index, C_LEFT);
			index++;
			minXVal--;
			//FORNOW 
			//PtintCheck(tmpBoard);
		}
		dropStep(tmpBoard);
		tmpMove.setCurrentStep(index, C_DROP);
		//FORNOW 
		//PtintCheck(tmpBoard);

	}
	// If the number of the column is greater than the minimum number of columns of the shape, 
	//we will create a move to the right until we reach a column
	else if (minXVal < col)
	{
		while ((minXVal < col) && (tmpBoard.spaceBelowTetromino() == true))
		{
			rightStep(tmpBoard);
			tmpMove.setCurrentStep(index, C_RIGHT);
			index++;
			minXVal++;
			//FORNOW 
			//PtintCheck(tmpBoard);
		}
		dropStep(tmpBoard);
		tmpMove.setCurrentStep(index, C_DROP);

		//FORNOW
		//PtintCheck(tmpBoard);

	}
	else // If the column number is equal to the minimum column of the shape DROP is done
	{
		dropStep(tmpBoard);
		tmpMove.setCurrentStep(index, C_DROP);
		//FORNOW
		//PtintCheck(tmpBoard);

	}
	//FORNOW
	//PtintCheck(tmpBoard);

	setIsLineFull_Rows_setSpaceInRows(tmpBoard, tmpMove);
}

int ComputerPlayer::minX() const
{
	size_t numOfCoordinates = board.getCurrentTetrominoVecSize();
	int res = board.getCurrentTetromino().getXCoordinate(0);
	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++)
	{
		if (res > board.getCurrentTetromino().getXCoordinate(i))
		{
			res = board.getCurrentTetromino().getXCoordinate(i);
		}
	}

	return res;
}

void ComputerPlayer::chooseTheBestMove(Move& tmpMove)
{
	//FORNOW
	/*clearScreen();
	cout << " tmpMove: ";
	tmpMove.printMove();
	cout << " Move before: ";
	move.printMove();*/

	// If the tmpmove has a full line and there is not in move, we selected in the tmpmove to be the move;
	if (tmpMove.getIsLineFull() == true && move.getIsLineFull() == false) {
		move = tmpMove;
		return;
	}
	else
	{
		int i = 3;
		if (tmpMove.getRow(i) == move.getRow(i))
		{
			while (tmpMove.getRow(i) == move.getRow(i) && i >= 0) 			//Is the lowest row equal?
			{
				//If the number of the row that the shape occupies is equal, 
				//the one that causes the row to have less spaces is chosen.
				if (tmpMove.getSpaceInRow(3) < move.getSpaceInRow(3)) {
					move = tmpMove;
					return;
				}
				i--;
			}
		}
		else {
			//Choose the form that causes the formation of as few spaces as possible
			if (tmpMove.sumOfSpaceInRaws() < move.sumOfSpaceInRaws()) {
				move = tmpMove;
				return;
			}
			//If the sum of spaces is equal, we will choose the move that has the minimum number of spaces.
			else if (tmpMove.minNumOfSpaces() < move.minNumOfSpaces()) {
				move = tmpMove;
				return;
			}
		}

	}

	//FORNOW
	//cout << " Move after: ";
	//move.printMove();
	//clearScreen();

}

char ComputerPlayer::updateKeysForPlayer2(char res)
{
	switch (res)
	{
	case (C_LEFT):
		return 'j';
		break;
	case C_RIGHT:
		return 'l';
		break;
	case C_CLOCKWISE:
		return 'k';
		break;
	case C_COUNTERCLOCKWISE:
		return 'i';
		break;
	case C_DROP:
		return 'm';
		break;
	default:
		break;
	}
}

void ComputerPlayer::getKeyAndPerformAction(int player)
{
	char keyPressed = move.getCurrentStep();
	move.setStep(move.getStep() + 1);
	if (player == PLAYER2)
	{
		keyPressed = updateKeysForPlayer2(keyPressed);
	}

	if (board.isTetrominoMoving())
	{
		board.performAction(keyPressed, player);
	}


}

void ComputerPlayer::leftStep(Board& tmpBoard)
{
	tmpBoard.printTetromino();
	tmpBoard.moveTetrominoDown();
	tmpBoard.turnTetrominoLeftOrRight(LEFT);
}

void ComputerPlayer::rightStep(Board& tmpBoard)
{
	tmpBoard.printTetromino();
	tmpBoard.moveTetrominoDown();
	tmpBoard.turnTetrominoLeftOrRight(RIGHT);
}
void ComputerPlayer::dropStep(Board& tmpBoard)
{
	tmpBoard.printTetromino();
	tmpBoard.moveTetrominoDown();
	tmpBoard.dropTetromino();
}

void ComputerPlayer::clockWiseStep(Board& tmpBoard)
{
	tmpBoard.moveTetrominoDown();
	tmpBoard.turnTetrominoClockwise(CLOCKWISE);
}

void ComputerPlayer::counterClockWiseStep(Board& tmpBoard)
{
	tmpBoard.moveTetrominoDown();
	tmpBoard.turnTetrominoClockwise(COUNTERCLOCKWISE);
}

void ComputerPlayer::setIsLineFull_Rows_setSpaceInRows(Board& tmpBoard, Move& tmpMove)
{
	setIsLineFull(tmpMove);
	setRows(tmpBoard, tmpMove);
	setSpaceInRows(tmpBoard, tmpMove);
}

//delete in the end
void ComputerPlayer::PtintCheck(Board& tmpBoard)
{
	board.printBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
	tmpBoard.printBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
}

bool ComputerPlayer::isMissMove() const
{
	int num = (rand() % level + 1);
	if (num == level)
	{
		return true;
	}
	return false;
}

void ComputerPlayer::createMissMove()
{
	Board tmpBoard = board;
	move.setStep(0);
	int index = 0;
	while (tmpBoard.spaceBelowTetromino() == true)
	{
		int num = (rand() % 2 + 1);

		if (num == 1)
		{
			leftStep(tmpBoard);
			move.setCurrentStep(index, C_LEFT);
			index++;
			move.setStep(index);
		}
		else
		{
			rightStep(tmpBoard);
			move.setCurrentStep(index, C_RIGHT);
			index++;
			move.setStep(index);
		}
	}
	move.setStep(0);
}

