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

void printChar(SHORT x, SHORT y, const char* symbol, WORD color) {
    out = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};

    WORD attribute = color;
    DWORD written;
	SMALL_RECT m_rectWindow;

    // WriteConsoleOutputAttribute(out, &attribute, 1, coord, &written);
    WriteConsoleOutputCharacterA(out, symbol, 1, coord, &written);
}