#include "GameConfig.h"
#include <Windows.h>

#define YELLOW 96
#define PURPLE 95
#define BLUE 48
#define GRAY 143
#define WHITE 120
#define TURQUISE 176
#define RED 64
#define GREEN 32


#define TURQUISE 176
const int GameConfig::COLORS[] = { FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,YELLOW,PURPLE,BLUE,WHITE,RED,TURQUISE,GREEN};
const int GameConfig::NUM_OF_COLOR = sizeof(COLORS) / sizeof(COLORS[1]);



void GameConfig::showConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(out, &cursorInfo);
}

