#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

class GameConfig
{
public:
	enum class eShapes
	{
		Straight = 1, Square, TShaped, LShaped, SShaped, JShaped, ZShaped
	};
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int GAME_TIME = 1000;
	static constexpr char BOARD_BORDER_CHAR = '@';
	static constexpr char TETRINOM_CHAR = '#';
	static constexpr char FIRST_BOARD_X = 30;
	static constexpr char FIRST_BOARD_Y = 5;
	static constexpr char SECOND_BOARD_X = 60;
	static constexpr char SECOND_BOARD_Y = 5;
};
#endif