#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

#include <windows.h>

class GameConfig
{
public:
	enum class eShapes
	{
		Straight = 1, Square, TShaped, LShaped, SShaped, JShaped, ZShaped
	};
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int GAME_TIME = 300;
	static constexpr char BOARD_BORDER_CHAR = '@';
	static constexpr char TETROMINO_CHAR = '#';
	static constexpr char FIRST_BOARD_X = 18;
	static constexpr char FIRST_BOARD_Y = 4;
	static constexpr char SECOND_BOARD_X = 48;
	static constexpr char SECOND_BOARD_Y = 4;
	static constexpr char TETRIS_MSG_X = 36;
	static constexpr char TETRIS_MSG_Y = 1;

	// This method disables the cursor to eliminate jittering
	void showConsoleCursor(bool showFlag);
};
#endif