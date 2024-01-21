#include <iostream>
#include "GameConfig.h"
#include "TetrisGame.h"
#include "Board.h"


int main() {
	srand(time(0));

	// Disable cursor Method
	GameConfig().showConsoleCursor(false);

	// Start Game
	TetrisGame().game();
}