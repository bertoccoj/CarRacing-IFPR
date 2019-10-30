#include <stdio.h>
#include <stdlib.h>
#include "display.h"

#define MENU_NEW_GAME 49
#define MENU_HIGH_SCORES 50
#define MENU_QUIT 51

#define SCREEN_CENTER 35

#define ROWS 25
#define COLUMS 12

#define ASTERISCO '*'
#define EMPTY_PIXEL 32
#define PIXEL 177

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE_BAR 32
#define ESCAPE 27
#define KEY_A 65
#define KEY_SMALL_A 97
#define KEY_D 83
#define KEY_SMALL_D 100

int gameMenu();
void printGameMatrix(char matrix[ROWS][COLUMS]);
void initMatrix(char matrix[ROWS][COLUMS]);
void drawPista(char matrix[ROWS][COLUMS], int speed);
void drawCar(int x, int y, char matrix[ROWS][COLUMS], int simbolo);