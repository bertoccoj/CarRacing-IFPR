#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "display.h"
//----OPÇÕES DO MENU
#define MENU_NEW_GAME 49
#define MENU_HIGH_SCORES 50
#define MENU_QUIT 51

//----OPÇÕES DA TELA
#define SCREEN_CENTER 38
#define ROWS 25
#define COLUMS 13

//----CORES
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_AQUA 3
#define COLOR_RED 4
#define COLOR_PURPLE 5
#define COLOR_YELLOW 6
#define COLOR_WHITE 7
#define COLOR_GRAY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 0xA
#define COLOR_LIGHT_AQUA 0xB
#define COLOR_LIGHT_RED 0xC
#define COLOR_LIGHT_PURPLE 0xD
#define COLOR_LIGHT_YELLOW 0xE
#define COLOR_BRIGHT_WHITE 0xF

//----SIMBOLOS
#define ASTERISCO 42
#define EMPTY_PIXEL 32
#define PIXEL 176
#define PIXEL2 177
#define PIXEL3 178
#define PIXEL_SOLID 219

//----TECLAS
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE_BAR 32
#define KEY_ESCAPE 27
#define KEY_A 65
#define KEY_SMALL_A 97
#define KEY_D 83
#define KEY_SMALL_D 100
#define KEY_W 119
#define KEY_SMALL_W 87

//----CONDIÇÕES LÓGICAS
#define true 1
#define false 0

//----GAME-VARS
#define ENEMY_NUMBER 10
#define ENEMY_DISTANCE -11

typedef struct {
    int x;
    int y;
    int color;
} car;

typedef struct {
    int simbolo;
    int color;
} gamePixel;

typedef struct {
    char nome[100];
    int pontos;
} gamer;

int gameMenu();
void printGameMatrix(gamePixel matrix[ROWS][COLUMS]);
void initMatrix(gamePixel matrix[ROWS][COLUMS]);
void drawPista(gamePixel matrix[ROWS][COLUMS]);
void drawCar(int x, int y, gamePixel matrix[ROWS][COLUMS], int simbolo, int color);
void initPista(gamePixel matrix[ROWS][COLUMS]);
int playerCollided(int x, int y, gamePixel matrix[ROWS][COLUMS]);
void initEnemies(car enemies[ENEMY_NUMBER]);
void drawEnemies(car enemies[ENEMY_NUMBER], gamePixel matrix[ROWS][COLUMS], int clear);