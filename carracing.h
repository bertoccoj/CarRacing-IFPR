#include <stdio.h>
#include <stdlib.h>
#include "display.h"

#define MENU_NEW_GAME 49
#define MENU_HIGH_SCORES 50
#define MENU_QUIT 51

#define SCREEN_CENTER 38

#define ROWS 25
#define COLUMS 15

#define ASTERISCO '*'
#define EMPTY_PIXEL ' '
#define PISTA 177

int gameMenu();
void printGameMatrix(char matrix[ROWS][COLUMS]);
void initMatrix(char matrix[ROWS][COLUMS]);
void drawPista(char matrix[ROWS][COLUMS], int speed);