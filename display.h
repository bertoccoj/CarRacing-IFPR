#include <Windows.h>
#include <stdio.h>

#define SCALE 4 // deve ser um múltiplo de 2

void gotoxy (int x, int y);
void ShowConsoleCursor(int showFlag);
void printChar(SHORT x, SHORT y, const int* symbol, int color);
void printTeste(CHAR_INFO consoleBuffer[325]);
