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
#define C_MOVE_DOWN 'h'
#define EMPTY_CHAR ' '
#define PLAYER1 0
#define PLAYER2 1
#define BEST 0
#define GOOD 40
#define NOVICE 10
#define MIN_COL 1
#define FIRST_COL 1
#define SIZE_OF_TETROMINO 4
#define SIZE_OF_ROWS 4
#define FIRST_STEP 0
#define FIRST_INDEX 0
#define NUM_OF_ROWS 4
#define FIRST_APPEARANCE 0

Board& ComputerPlayer::getBoard() {
	return this->board;
}

void ComputerPlayer::setMove()
{
	//make empty move
	move.initMove(); 

	//if the computer is not in level BEST he has some miss move acording to is level.
	if ((int)level != BEST)
	{    
		if (isMissMove())
		{
			createMissMove();
			return;
		}
	}
	// if level == BEST or it's not a miss move create the right move
	createMove();
}

void ComputerPlayer::createMove()
{
	//first create the first possible move that will be also the difult move
	createFirstMove();

	//We will create all possible moves in a temporary variable,
	//and choose the best compare to current chosen move
	createMovesAndChooseTheBest();

	//make the move to be ready to rum from the first step
	move.setStep(FIRST_STEP);
}

void ComputerPlayer::createFirstMove()
{
	// copy the board to the tmp board so that all the changes made to it in order to create the move will not be saved in the "real" board
	Board tmpBoard = board;

	int step = FIRST_STEP;

	// minVal = the lowest the minimum X value among the X values of the shape when it enters the board
	int minXVal = minX();

	// As long as the minimum X value is not equal to the minimum row in the board (1) a step to the left can be made
	while ((minXVal != MIN_COL) && (tmpBoard.spaceBelowTetromino(true) == true))
	{
		//Taking a step to the left 
		leftStep(tmpBoard, move, step);

		//Update step one step forward
		step++;

		//Because we did step left ,the minimum X value of the shape is automatically decreased by 1.
		minXVal--;
	}

	//when the shape finished to do steps to the left we will keep do steps down.
	moveDown(tmpBoard, move, step);

	//if the current shape is is bomb we will update the values that help us choose the best move for the bomb
	if (board.isCurrentShapeBomb()){
		setnumOfExplodedCubs(tmpBoard, move);
	}
	else { //if the current shape is tetromino we will update the values that help us choose the best move for the tetromino
		setIsLineFull_Rows_setSpaceInRows(tmpBoard, move);
	}

}

void ComputerPlayer::setIsLineFull(Move& move)
{
	size_t numOfCoordinates = board.getCurrentTetrominoVecSize();

	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++) {
		// if one of the row of the tetromino is full in the board
		if (board.isLineFull(board.getCurrentTetromino().getYCoordinate(i)))
		{
			//update data member of move "isLineFull" to be true.
			move.setIsLineFull(true);
			return;
		}
	}
	// if none of the full update data member of move "isLineFull" to be false.
	move.setIsLineFull(false);
}

void ComputerPlayer::setRows(Board& curBoard, Move& curMove)
{
	size_t numOfCoordinates = board.getCurrentTetrominoVecSize();

	// update all the row that the shape contain and update them in the arry
	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++)
	{
		int row = curBoard.getCurrentTetromino().getYCoordinate(i);
		curMove.setRow(i, row);

	}
	// sort rows array so the highest line will be first and the lowest line will be last
	bubbleSort(curMove.getRowsAddress(), numOfCoordinates);
}

void ComputerPlayer::setSpaceInRows(Board& curBoard, Move& curMove)
{
	size_t numOfCoordinates = board.getCurrentTetrominoVecSize();

	// update the spaces in each row the the shape contain
	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++)
	{
		// get the number of spaces in the row and update it in spaceInRow array
		int numOfSpaces = curBoard.getNumOfSpaceInLine(curMove.getRow(i));
		curMove.setSpaceInRow(i, numOfSpaces);

		// if num of row equal to the next row the number of spaces equal. (can be only in tetromino shape)
		while (curMove.getRow(i) == curMove.getRow(i + 1) && i < NUM_OF_ROWS)
		{
			curMove.setSpaceInRow(i + 1, numOfSpaces);
			i++;
		}
	}

}

void ComputerPlayer::createMovesAndChooseTheBest()
{
	// save the current next move and compare it to the object's move

	//numOfMutations = number of appearances that one shape can appear on the board
	int numOfMutations = getNumOfMutations();


	// for each such performance we will build all the possible moves on the board
	for (int appearance = FIRST_APPEARANCE; appearance < numOfMutations; appearance++)
	{
		//for each col we build a move
		for (int col = FIRST_COL; col < GameConfig::GAME_WIDTH - 2; col++)
		{
			// create tmp move so the current move will not change
			Move tmpMove;

			// copy the board to the tmp board so that all the changes made to it in order to create the move will not be saved in the "real" board
			Board tmpBoard = board;

			// make share the move is empty
			tmpMove.initMove(); 

			//if it's a move if a shape that can do a clockwise step ans change is performance
			// so according to index "i" we will update the step that need to be done to "change" the performance of the shape
			createFirstsStepByTheShape(appearance, tmpMove, tmpBoard);
			
			//create the next move according the current col;
			createTheNextSteps(col, tmpMove, tmpBoard);
			
			// after we create tmpMove if he better move that the current move make the tmpMove to be the move
			chooseTheBestMove(tmpMove);

		}
	}
}

int ComputerPlayer::getNumOfMutations() const
{
	if (board.getCurrentTetromino().getShape() == (int)GameConfig::eShapes::Square || board.getCurrentTetromino().getShape() == (int)GameConfig::eShapes::Bomb)
	{
		return 1;
	}
	else if (board.getCurrentTetromino().getShape() == (int)GameConfig::eShapes::Straight || board.getCurrentTetromino().getShape() == (int)GameConfig::eShapes::SShaped || board.getCurrentTetromino().getShape() == (int)GameConfig::eShapes::ZShaped)
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
	int step = 0;
	tmpMove.setStep(0);// make sure we are in move[0]

	if (tmpBoard.spaceBelowTetromino(true) == true)
	{
		switch (i)
		{
		case (1):
			//first step - one time CLOCKWISE
			clockWiseStep(tmpBoard,tmpMove,step);
			tmpMove.setStep(step + 1);
			break;
		case (2):
			//first two step - twice CLOCKWISE
			clockWiseStep(tmpBoard, tmpMove, step);
			tmpMove.setStep(step + 1);
			if (tmpBoard.spaceBelowTetromino(true) == true)
			{
				step++;
				clockWiseStep(tmpBoard, tmpMove, step);
				tmpMove.setStep(step + 1);
			}
			break;
		case (3):
			//first step - one time COUNTERCLOCKWISE
			counterClockWiseStep(tmpBoard, tmpMove, step);
			tmpMove.setStep(step + 1);
		default:
			break;
		}
	}
}

void ComputerPlayer::createTheNextSteps(int col, Move& tmpMove, Board& tmpBoard)
{
	// minXVal = the lowest the minimum X value among the X values of the shape when it enters the board
	int minXVal = minX();

	// because the first steps could be alrey done we wont to get the current step
	int step = tmpMove.getStep();

	//If the col number is less than the minimum number of columns of the shape,
	if (minXVal > col)
	{
		//we will create a move to the left until we reach a column
		while ((minXVal > col) && (tmpBoard.spaceBelowTetromino(true) == true))
		{
			//Taking a step to the left 
			leftStep(tmpBoard, tmpMove,step);
			
			//Update step one step forward
			step++;
			
			//Because we did step left ,the minimum X value of the shape is automatically decreased by 1.
			minXVal--;
		}
		
	}
	// If the number of the column is greater than the minimum number of columns of the shape, 
	else if (minXVal < col)
	{
		//we will create a move to the right until we reach a column
		while ((minXVal < col) && (tmpBoard.spaceBelowTetromino(true) == true))
		{
			//Taking a step to the right
			rightStep(tmpBoard, tmpMove,step);

			//Update step one step forward
			step++;
			//Because we did step right ,the minimum X value of the shape is automatically up by 1.
			minXVal++;
		}
	}
	
	//when the shape reached the column, we will continue and take steps down until the shape stops.
	moveDown(tmpBoard, tmpMove, step);
	
	//if the current shape is is bomb we will update the values that help us choose the best move for the bomb
	if (board.isCurrentShapeBomb())
	{
		setnumOfExplodedCubs(tmpBoard, tmpMove);
	}
	else {//if the current shape is tetromino we will update the values that help us choose the best move for the tetromino
		setIsLineFull_Rows_setSpaceInRows(tmpBoard, tmpMove);
	}
}

int ComputerPlayer::minX() const
{
	size_t numOfCoordinates = board.getCurrentTetrominoVecSize();

	int res = board.getCurrentTetromino().getXCoordinate(FIRST_INDEX);

	for (int i = DEFAULT_VALUE; i < numOfCoordinates; i++)
	{
		//int res > next X value 
		if (res > board.getCurrentTetromino().getXCoordinate(i))
		{
			//update res
			res = board.getCurrentTetromino().getXCoordinate(i);
		}
	}

	return res;
}

void ComputerPlayer::chooseTheBestMove(Move& tmpMove)
{
	// if the current shape is bomb 
	if (board.isCurrentShapeBomb())
	{
		//compare tmp move to move and choose the best move to the bomb
		chooseMoveForBomb(tmpMove);
	}
	else // the cuttent shape is tetromino
	{
		//compare tmp move to move and choose the best move to the tetromino
		chooseMoveForTetromino(tmpMove);
	}
}

void ComputerPlayer::chooseMoveForBomb(Move& tmpMove)
{
	//If the number of cubes exploded of tmpMove is bigger than move
	// we will update the tmpMove to be the move
	if (tmpMove.getnumOfExplodedCubs() > move.getnumOfExplodedCubs())
		move = tmpMove;
}

void ComputerPlayer::chooseMoveForTetromino(Move& tmpMove)
{
	// If the tmpmove has a full line and there is not in move, we will update the tmpMove to be the move;
	if (tmpMove.getIsLineFull() == true && move.getIsLineFull() == false) {
		//update move to be tmpMove
		move = tmpMove;
		return;
	}
	else
	{
		int row = SIZE_OF_ROWS - 1;
		if (tmpMove.getRow(row) == move.getRow(row))
		{
			while (tmpMove.getRow(row) == move.getRow(row) && row >= 0) //Is the lowest row equal?
			{
				//If the number of the row that the shape occupies is equal, 
				//the one that causes the row to have less spaces is chosen.
				if (tmpMove.getSpaceInRow(row) < move.getSpaceInRow(row)) {
					//update move to be tmpMove
					move = tmpMove;
					return;
				}
				row--;
			}
		}
		else {
			//Choose the form that causes the formation of as few spaces as possible
			if (tmpMove.sumOfSpaceInRaws() < move.sumOfSpaceInRaws()) {
				//update move to be tmpMove
				move = tmpMove;
				return;
			}
			//If the sum of spaces is equal, we will choose the move that has the minimum number of spaces.
			else if (tmpMove.minNumOfSpaces() < move.minNumOfSpaces()) {
				//update move to be tmpMove
				move = tmpMove;
				return;
			}
		}

	}
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
	default: // means that res doesn't need to be changed
		return res;
		break;
	}
}

void ComputerPlayer::getKeyAndPerformAction(int player, char keyPressed)
{
	//get the current step from move array
	keyPressed = move.getCurrentStep();
	//update the step one step forward
	move.setStep(move.getStep() + 1);
	
	//if the computer is player 2 update the keyPress to the keyPress for player 2
	if (player == PLAYER2)
	{
		keyPressed = updateKeysForPlayer2(keyPressed);
	}

	//if the shape is not moving preform action
	if (board.isTetrominoMoving())
	{
		board.performAction(keyPressed, player);
	}


}

void ComputerPlayer::leftStep(Board& tmpBoard, Move& curMove, int step)
{
	//Taking a step to the left on our tmpBoard
	tmpBoard.printTetromino();
	tmpBoard.moveTetrominoDown();
	tmpBoard.turnTetrominoLeftOrRight(LEFT);
	//update the current step to be a left step in move array
	curMove.setCurrentStep(step, C_LEFT);
	
}

void ComputerPlayer::rightStep(Board& tmpBoard, Move& curMove ,int step)
{
	//Taking a step to the right on our tmpBoard
	tmpBoard.printTetromino();
	tmpBoard.moveTetrominoDown();
	tmpBoard.turnTetrominoLeftOrRight(RIGHT);
	//update the current step to ne a right step in move array
	curMove.setCurrentStep(step, C_RIGHT);
}

void ComputerPlayer::moveDown(Board& tmpBoard, Move& curMove, int step)
{
	//as long as there is space for the shape to move down we will take a step down
	while (tmpBoard.spaceBelowTetromino(true))
	{
		tmpBoard.printTetromino();
		tmpBoard.moveTetrominoDown();
		//update the current step to be a move down step in move array
		curMove.setCurrentStep(step, C_MOVE_DOWN);
		//Update step one step forward
		step++;
	}
}

void ComputerPlayer::clockWiseStep(Board& tmpBoard, Move &curMove, int step)
{
	//Taking a clockwise step on our tmpBoard
	tmpBoard.printTetromino();
	tmpBoard.moveTetrominoDown();
	tmpBoard.turnTetrominoClockwise(CLOCKWISE);
	//update the current step to be a clockwise step in move array
	curMove.setCurrentStep(step, C_CLOCKWISE);

}

void ComputerPlayer::counterClockWiseStep(Board& tmpBoard, Move& curMove, int step)
{
	//Taking a counter clockwise step on our tmpBoard
	tmpBoard.printTetromino();
	tmpBoard.moveTetrominoDown();
	tmpBoard.turnTetrominoClockwise(COUNTERCLOCKWISE);
	//update the current step to be a counter clockwise step in move array
	curMove.setCurrentStep(step, C_COUNTERCLOCKWISE);
}

void ComputerPlayer::setIsLineFull_Rows_setSpaceInRows(Board& tmpBoard, Move& tmpMove)
{
	// set all the value that help us to choose the best move for tetromino
	setIsLineFull(tmpMove);
	setRows(tmpBoard, tmpMove);
	setSpaceInRows(tmpBoard, tmpMove);
}

bool ComputerPlayer::isMissMove() const
{
	int num = (rand() % (int)level + 1);
	if (num == (int)level)
	{
		return true;
	}
	return false;
}

void ComputerPlayer::createMissMove()
{
	Board tmpBoard = board;
	move.initMove();// make emty move
	int step = FIRST_STEP;

	while (tmpBoard.spaceBelowTetromino(true) == true)
	{
		int num = (rand() % 2 + 1);

		if (num == 1)
		{
			leftStep(tmpBoard, move,step);
			//move.setCurrentStep(step, C_LEFT);
			step++;
			move.setStep(step);
		}
		else
		{
			rightStep(tmpBoard,move,step);
			//move.setCurrentStep(step, C_RIGHT);
			step++;
			move.setStep(step);
		}
	}
	//make the move to be ready to rum from the first step
	move.setStep(FIRST_STEP);
}

void ComputerPlayer::setnumOfExplodedCubs(Board& curBoard, Move& curMove)
{
	int numOfExplodedCubs = curBoard.numOfExplodedCubs();
	curMove.setnumOfExplodedCubs(numOfExplodedCubs);
}

