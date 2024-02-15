#include "ComputerPlayer.h"
#include "General.h"

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


void ComputerPlayer::setupBoard(bool isColor) {
	// Initialize board colors
	this->board.setIsColor(isColor);

	// Initialize boards
	this->board.initBoard();

	// Set player's score to zero
	this->board.setScores();

	//Add a new tetromino shape to the board
	// 
	// ***********************************yarden
	this->board.addTetromino();

	this->setmove();
}

void ComputerPlayer::setmove()
{
	move.setStep(0);
	move.initMove();

	if (board.isCurrentShapeBomb())
	{
		//createMovesForBomb();//TODO
	}
	else
	{
		createMovesForTetromino();
	}

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

	//FORNOW - Currently in a note - do not touch
	//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
	//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);

	int index = 0;
	int minXVal = minX();
	while ((minXVal != 1) && (tmpBoard.spaceBelowTetromino() == true))
	{
		//Later it will go to a function that contains all these actions that will look nice
		tmpBoard.printTetromino();
		tmpBoard.moveTetrominoDown();
		tmpBoard.turnTetrominoLeftOrRight(LEFT);
		move.setCurrentStep(index, C_LEFT);
		index++;
		minXVal--;
		//FORNOW - Currently in a note - do not touch
		//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);

	}

	//Later it will go to a function that contains all these actions that will look nice
	tmpBoard.printTetromino();
	tmpBoard.moveTetrominoDown();
	tmpBoard.dropTetromino();
	move.setCurrentStep(index, C_DROP);
	
	//FORNOW - Currently in a note - do not touch
	//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
	//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);

	//Later it will go to a function that contains all these actions that will look nice
	setIsLineFull(move);
	setRows(tmpBoard.getCurrentTetromino(), move);
	setSpaceInRows(tmpBoard, move);

}

void ComputerPlayer::setIsLineFull(Move& move)
{
	for (int i = 0; i < 4; i++) {
		if (board.isLineFull(board.getCurrentTetromino().getYCoordinate(i)))
		{
			move.setIsLineFull(true);
			return;
		}
	}
	move.setIsLineFull(false);
}

void ComputerPlayer::setRows(const Tetromino& curTetromino, Move& curMove)
{

	for (int i = 0; i < 4; i++)
	{
		int row = curTetromino.getYCoordinate(i);
		curMove.setRow(i, row);

	}
	bubbleSort(curMove.getRowsAddress(), 4);


}

void ComputerPlayer::setSpaceInRows(Board& curBoard, Move& curMove)
{

	for (int i = 0; i < 4; i++)
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

int ComputerPlayer::getNumOfMutations()
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
			tmpBoard.moveTetrominoDown();
			tmpBoard.turnTetrominoClockwise(CLOCKWISE);
			tmpMove.setCurrentStep(tmpMove.getStep(), C_CLOCKWISE);
			tmpMove.setStep(index + 1);
			//FORNOW - Currently in a note - do not touch
			//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
			//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
			break;
		case (2):
			//first two step - twice CLOCKWISE
			tmpBoard.moveTetrominoDown();
			tmpBoard.turnTetrominoClockwise(CLOCKWISE);
			tmpMove.setCurrentStep(tmpMove.getStep(), C_CLOCKWISE);
			tmpMove.setStep(index + 1);
			if (tmpBoard.spaceBelowTetromino() == true)
			{
				index++;
				tmpBoard.moveTetrominoDown();
				tmpBoard.turnTetrominoClockwise(CLOCKWISE);
				tmpMove.setCurrentStep(tmpMove.getStep(), C_CLOCKWISE);
				tmpMove.setStep(index + 1);
			}
			//FORNOW - Currently in a note - do not touch
			//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
			//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
			break;
		case (3):
			//first step - one time COUNTERCLOCKWISE
			tmpBoard.moveTetrominoDown();
			//tmpBoard.printTetromino();
			tmpBoard.turnTetrominoClockwise(COUNTERCLOCKWISE);
			tmpMove.setCurrentStep(tmpMove.getStep(), C_COUNTERCLOCKWISE);
			tmpMove.setStep(index + 1);
			//FORNOW - Currently in a note - do not touch
			//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
			//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
		default:
			break;
		}
	}
}

void ComputerPlayer::createTheNextSteps(int col, Move& tmpMove, Board& tmpBoard)
{
	//FORNOW - Currently in a note - do not touch
	//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
	//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);

	int minXVal = minX();
	int index = tmpMove.getStep();

	//If the col number is less than the minimum number of columns of the shape,
	//we will create a move to the left until we reach a column
	if (minXVal > col)
	{
		while ((minXVal > col) && (tmpBoard.spaceBelowTetromino() == true))
		{
			tmpBoard.printTetromino();
			tmpBoard.moveTetrominoDown();
			tmpBoard.turnTetrominoLeftOrRight(LEFT);
			tmpMove.setCurrentStep(index, C_LEFT);
			index++;
			minXVal--;
			//FORNOW
			//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
			//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
		}
		tmpBoard.printTetromino();
		tmpBoard.moveTetrominoDown();
		tmpBoard.dropTetromino();
		tmpMove.setCurrentStep(index, C_DROP);
		//FORNOW
		//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);

	}
	// If the number of the column is greater than the minimum number of columns of the shape, 
	//we will create a move to the right until we reach a column
	else if (minXVal < col)
	{
		while ((minXVal<col) && (tmpBoard.spaceBelowTetromino() == true))
		{
			tmpBoard.printTetromino();
			tmpBoard.moveTetrominoDown();
			tmpBoard.turnTetrominoLeftOrRight(RIGHT);
			tmpMove.setCurrentStep(index, C_RIGHT);
			index++;
			minXVal++;
			//FORNOW
			//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
			//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
		}
		tmpBoard.printTetromino();
		tmpBoard.moveTetrominoDown();
		tmpBoard.dropTetromino();
		tmpMove.setCurrentStep(index, C_DROP);
		//FORNOW
		//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
	}
	else // If the column number is equal to the minimum column of the shape DROP is done
	{
		tmpBoard.printTetromino();
		tmpBoard.moveTetrominoDown();
		tmpBoard.dropTetromino();
		tmpMove.setCurrentStep(index, C_DROP);
		//FORNOW
		//board.setupAllAndPrintBoard(GameConfig::FIRST_BOARD_X, GameConfig::FIRST_BOARD_Y);
		//tmpBoard.setupAllAndPrintBoard(GameConfig::SECOND_BOARD_X, GameConfig::SECOND_BOARD_Y);
	}

	setIsLineFull(tmpMove);
	setRows(tmpBoard.getCurrentTetromino(), tmpMove);
	setSpaceInRows(tmpBoard, tmpMove);//TODO

}

int ComputerPlayer::minX()
{
	int res = board.getCurrentTetromino().getXCoordinate(0);
	for (int i = 1; i < 4; i++)
	{
		if (res > board.getCurrentTetromino().getXCoordinate(i))
		{
			res = board.getCurrentTetromino().getXCoordinate(i);
		}
	}

	return res;
}

int ComputerPlayer::maxX()
{
	int res = board.getCurrentTetromino().getXCoordinate(0);
	for (int i = 1; i < 4; i++)
	{
		if (res < board.getCurrentTetromino().getXCoordinate(i))
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
	if (tmpMove.getIsLineFull() == true && move.getIsLineFull() == false){
		move = tmpMove;
		return;
	}
	else
	{
		int i = 3;
		while (tmpMove.getRow(i) == move.getRow(i) && i >= 0) 			//Is the lowest row equal?
		{
			//If the number of the row that the shape occupies is equal, 
			//the one that causes the row to have less spaces is chosen.
			if (tmpMove.getSpaceInRow(3) < move.getSpaceInRow(3)){
				move = tmpMove;
				return;
			}
			i--;
		}

		//Choose the form that causes the formation of as few spaces as possible
		if (tmpMove.sumOfSpaceInRaws() < move.sumOfSpaceInRaws()){
			move = tmpMove;
			return;
		}
		//If the sum of spaces is equal, we will choose the move that has the minimum number of spaces.
		else if (tmpMove.minNumOfSpaces() < move.minNumOfSpaces()){
			move = tmpMove;
			return;
		}
	}

	//FORNOW
	/*cout << " Move after: ";
	move.printMove();
	clearScreen();*/

}


void ComputerPlayer::updateKeysForPlayer2()
{
	int len = move.moveLen();
	int saver = move.getStep();
	for (int i = 0; i < len; i++)
	{
		switch (move.getCurrentStep())
		{
		case (C_LEFT):
			move.setCurrentStep(i, 'j');
			break;
		case C_RIGHT:
			move.setCurrentStep(i, 'l');
			break;
		case C_CLOCKWISE:
			move.setCurrentStep(i, 'k');
			break;
		case C_COUNTERCLOCKWISE:
			move.setCurrentStep(i, 'i');
			break;
		case C_DROP:
			move.setCurrentStep(i, 'm');
			break;
		default:
			break;
		}
		move.setStep(i + 1);
	}
	move.setStep(saver);
}

char ComputerPlayer::getKey()
{
	char res = move.getCurrentStep();
	move.setStep(move.getStep() + 1);
	return res;
}



