#include "display.h"

HANDLE out;

void gotoxy (int x, int y) {
  COORD coord = {0, 0};
  coord.X = x; coord.Y = y; // X and Y coordinates
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(int showFlag) {
  out = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO  cursorInfo;

  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = showFlag; // set the cursor visibility
  SetConsoleCursorInfo(out, &cursorInfo);
}  

void printChar(SHORT x, SHORT y, const int* symbol, int color) {
  CHAR_INFO consoleBuffer[SCALE];
  COORD characterBufferSize = {SCALE/2, SCALE/2};
  int i;
  for (i = 0; i < SCALE; i++) {
    consoleBuffer[i].Char.AsciiChar = *symbol;
    consoleBuffer[i].Attributes = color;
  }
  COORD characterPosition = {0, 0};
  SMALL_RECT consoleWriteArea = {x, y, x + SCALE/2, y + SCALE/2};

  WriteConsoleOutputA(out, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}
