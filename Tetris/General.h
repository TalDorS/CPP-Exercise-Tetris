#ifndef __GENERAL_H
#define __GENERAL_H

void gotoxy(int, int);
char getKeyFromUser();
void clearScreen();
void showConsoleCursor(bool showFlag);
void swap(int* a, int* b);
void bubbleSort(int arr[], int n);

#endif // __GENERAL_H