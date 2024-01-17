#include <iostream>
#include "GameConfig.h"
#include "TetrisGame.h"
#include "Board.h"

int main() {
	// Disable cursor Method
	GameConfig().showConsoleCursor(false);

	// Start Game
	TetrisGame().game();
}