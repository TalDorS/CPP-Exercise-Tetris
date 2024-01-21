#include <iostream>
#include "General.h"
#include "TetrisGame.h"
#include "Board.h"


int main() {
	// Utility function for rand function
	srand(time(0));

	// Disable cursor Method
	showConsoleCursor(false);

	// Start Game
	TetrisGame().game();
}