#include "display.h"

HANDLE out;

void setConsoleInfo() {
  COLORREF palette[16] = 
  {
    0x00000000, 0x00800000, 0x00008000, 0x00808000,
    0x00000080, 0x00800080, 0x00008080, 0x00c0c0c0,
    0x00808080, 0x00ff0000, 0x0000ff00, 0x00ffff00,
    0x000000ff, 0x00ff00ff, 0x0000ffff, 0x00ffffff
  };
  SetConsolePalette(palette, 8, 8, L"Fontes de varredura");
  // printf("More of a normal Lucidas size.\n");
}

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
  int scale = 4;
  CHAR_INFO consoleBuffer[scale];
  COORD characterBufferSize = {scale/2, scale/2};
  int i;
  for (i = 0; i < scale; i++) {
    consoleBuffer[i].Char.AsciiChar = *symbol;
    consoleBuffer[i].Attributes = color;
  }
  COORD characterPosition = {0, 0};
  SMALL_RECT consoleWriteArea = {x, y, x + scale/2, y + scale/2};

  WriteConsoleOutputA(out, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void printTeste(CHAR_INFO consoleBuffer[325]) {
  COORD characterBufferSize = {13, 25};
  COORD characterPosition = {0, 0};
  SMALL_RECT consoleWriteArea = {38, 10, 100, 60};
  WriteConsoleOutputA(out, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}
