#include "General.h"
#include <windows.h>
#include <process.h> 
#include <conio.h>
#include <iostream>
using namespace std;

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void clearScreen()
{
	system("cls");
}

char getKeyFromUser() {
	char keyPressed = 0;

	while (true) {
		if (_kbhit()) {
			keyPressed = _getch();
			return keyPressed;
		}
	}
}