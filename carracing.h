#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "display.h"

//----OPÇÕES DO MENU
#define MENU_NEW_GAME 1
#define MENU_HIGH_SCORES 2
#define MENU_QUIT 3

//----OPÇÕES DA TELA
#define SCREEN_CENTER 38
#define ROWS 25
#define COLUMS 13

#define LEFT_STREET_SIDE COLUMS + 4
#define RIGHT_STREET_SIDE COLUMS + 8

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
#define KEY_W 87
#define KEY_SMALL_W 119
#define KEY_A 65
#define KEY_SMALL_A 97
#define KEY_S 83
#define KEY_SMALL_S 115
#define KEY_D 68
#define KEY_SMALL_D 100
#define KEY_RETURN 13

//----CONDIÇÕES LÓGICAS
#define true 1
#define false 0

//----GAME-VARS
#define ENEMY_NUMBER 3
#define ENEMY_DISTANCE -13
#define SPEED_NORMAL 8
#define SPEED_FAST SPEED_NORMAL / 2
#define LV2_TRIGGER 800 * 2

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
    char name[100];
    car car;
    int score;
} gamer;

typedef struct {
    char playerName[100];
    int score;
} highScore;

typedef struct {
    int gameOver;
    int quit;
    int currentStage;
    int currentSpeed;
    int cycles;
    int keyPressed;
    gamer player;
} state;

// função de inicialização de estado
void setGameState(state *gameState, int keepPlayer);

// Funções dos menus/telas do jogo
void gameMenu(state *gameState);
void highScoresScreen();
void askPlayerInfo(gamer *player);
int gameMenuOptions();
int gameOverScreen(gamer player);

// funções do highScore
int getHighScoreCount();
void saveScore(gamer jogador);
void readHighScoresFile(highScore destination[5]);
void loadHighScores();
void sortHighScores(highScore scores[6], int registros);

// funções de colisão
int playerCollided(int x, int y, gamePixel matrix[ROWS][COLUMS]);
int playerCollidedSides(car player, gamePixel matrix[ROWS][COLUMS]);

// funções de inicialização dos componentes do jogo
void initMatrix(gamePixel matrix[ROWS][COLUMS]);
void initPista(gamePixel matrix[ROWS][COLUMS]);
void initEnemies(car enemies[ENEMY_NUMBER]);

// funções de desenho dos componentes do jogo
void drawGameMatrix(gamePixel matrix[ROWS][COLUMS]);
void drawPista(gamePixel matrix[ROWS][COLUMS]);
void drawCar(car car, gamePixel matrix[ROWS][COLUMS], int simbolo, int color);
void drawEnemies(car enemies[ENEMY_NUMBER], gamePixel matrix[ROWS][COLUMS], int clear);

void handleKeyPressed(state *gameState, gamePixel matrix[ROWS][COLUMS]);