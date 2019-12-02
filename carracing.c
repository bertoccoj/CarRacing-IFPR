#include "carracing.h"

// seta o jogo para o estado inicial;
// parametro gameState, ponteiro para o estado que deve ser alterado
// keepPlayer, se deve ou não manter o player
void setGameState(state *gameState, int keepPlayer) {
  gameState->gameOver           = false;
  gameState->quit               = false;
  gameState->currentStage       = 1;
  gameState->currentSpeed       = SPEED_NORMAL;
  gameState->cycles             = 0;

  // gameState->player.hasCollided = false;
  gameState->player.score       = 0;
  gameState->player.car.x       = LEFT_STREET_SIDE;
  gameState->player.car.y       = ROWS - 5;
  
  if(!keepPlayer) {
    gameState->player.car.color = COLOR_BLUE;
    strcpy(gameState->player.name, "");
  }
}

// Inicializa a matrix do jogo
void initMatrix(gamePixel matrix[ROWS][COLUMS]) {
  int y, x;

  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMS; x++) {
      matrix[y][x].simbolo = PIXEL;
      matrix[y][x].color   = COLOR_GRAY;
    }
  }
}

void drawBorder() {
  int x,y;
  int simbolo = PIXEL2;
  for (y = -1; y < ROWS + 1; y++) {
    for (x = -1; x < COLUMS + 1; x++) {
      printChar(
        ((SCALE/2) * x) + SCREEN_CENTER, // posição X
        ((SCALE/2) * y) + 5,             // posição Y
        &simbolo,           // caracteer do pixel
        COLOR_WHITE               // cor que vai printar
      ); 
    }
  }

}

void drawGameMatrix(gamePixel matrix[ROWS][COLUMS]) {
  int y, x;
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMS; x++) {
      printChar(
        ((SCALE/2) * x) + SCREEN_CENTER, // posição X
        ((SCALE/2) * y) + 5,             // posição Y
        &matrix[y][x].simbolo,           // caracteer do pixel
        matrix[y][x].color               // cor que vai printar
      ); 
    }
  }
}

int playerCollided(car playerCar, gamePixel matrix[ROWS][COLUMS]) {
  return matrix[playerCar.y - 1][playerCar.x].simbolo != PIXEL;
}

int playerCollidedSides(car player, gamePixel matrix[ROWS][COLUMS]) {
  switch (player.x) {
    case LEFT_STREET_SIDE: 
      return matrix[player.y - 1][LEFT_STREET_SIDE].simbolo != PIXEL || matrix[player.y + 3][LEFT_STREET_SIDE].simbolo != PIXEL;
    case RIGHT_STREET_SIDE: 
      return matrix[player.y - 1][RIGHT_STREET_SIDE].simbolo != PIXEL || matrix[player.y + 3][RIGHT_STREET_SIDE].simbolo != PIXEL;
    default: return 0;
  }
}

void drawCar(car car, gamePixel matrix[ROWS][COLUMS], int simbolo, int color) {
  gamePixel replacement = { simbolo, color };

  if (car.y + 2 > 0 && car.y < ROWS - 1) matrix[car.y][car.x]         = replacement;
  if (car.y + 3 > 0 && car.y < ROWS - 2) matrix[car.y + 1][car.x]     = replacement;
  if (car.y + 4 > 0 && car.y < ROWS - 3) matrix[car.y + 2][car.x]     = replacement;
  if (car.y + 3 > 0 && car.y < ROWS - 2) matrix[car.y + 1][car.x -1]  = replacement;
  if (car.y + 3 > 0 && car.y < ROWS - 2) matrix[car.y + 1][car.x + 1] = replacement;
  if (car.y + 5 > 0 && car.y < ROWS - 4) matrix[car.y + 3][car.x + 1] = replacement;
  if (car.y + 5 > 0 && car.y < ROWS - 4) matrix[car.y + 3][car.x - 1] = replacement;
}

void initEnemies(car enemies[ENEMY_NUMBER]) {
  int i;
  for (i = 0; i < ENEMY_NUMBER; i++) {
    enemies[i].color = COLOR_GREEN;
    enemies[i].x     = rand() % 100 > 50 ? LEFT_STREET_SIDE : RIGHT_STREET_SIDE;
    enemies[i].y     = (i + 1) * ENEMY_DISTANCE;
  }
}

void drawEnemies(car enemies[ENEMY_NUMBER], gamePixel matrix[ROWS][COLUMS], int clear) {
  int i;
  for(i = 0; i < ENEMY_NUMBER; i++) {
    drawCar(enemies[i], matrix, clear ? PIXEL : PIXEL_SOLID, clear ? COLOR_GRAY : enemies[i].color);
  }
}

void initPista(gamePixel matrix[ROWS][COLUMS], int color) {
  gamePixel bordaOut = { PIXEL, color };
  int i, j;

  for (i = 0; i < ROWS; i++) {
    matrix[i][0] = bordaOut;
    matrix[i][COLUMS - 1] = bordaOut;
  }
}

void clearPista(gamePixel matrix[ROWS][COLUMS]) {
  int i;
  for (i = 0; i < ROWS; i++) {
    matrix[i][1].simbolo          = EMPTY_PIXEL;
    matrix[i][1].color            = COLOR_BLACK;
    matrix[i][COLUMS - 2].simbolo = EMPTY_PIXEL;
    matrix[i][COLUMS - 2].color   = COLOR_BLACK;
    matrix[i][COLUMS / 2].simbolo = PIXEL;
    matrix[i][COLUMS / 2].color   = COLOR_GRAY;
  }
}

void drawPista(gamePixel matrix[ROWS][COLUMS]) {
  gamePixel bordain;
  gamePixel center = { PIXEL, COLOR_LIGHT_YELLOW };
  int i, j;

  bordain.simbolo = PIXEL_SOLID;

  if (matrix[0][1].color != COLOR_WHITE) {
    clearPista(matrix);
    for (i = 0; i < ROWS; i++) {
      if (i % 2 != 0) {
        bordain.color = COLOR_RED;
      } else {
        matrix[i][COLUMS / 2] = center;
        bordain.color = COLOR_WHITE;
      }
      matrix[i][1] = bordain;
      matrix[i][COLUMS - 2] = bordain;
    }
  } else {
    clearPista(matrix);
    for (i = 0; i < ROWS; i++) {
      if (i % 2 == 0) {
        bordain.color = COLOR_RED;
      } else {
        matrix[i][COLUMS / 2] = center;
        bordain.color = COLOR_WHITE;
      }
      matrix[i][1] = bordain;
      matrix[i][COLUMS - 2] = bordain;
    }
  }
}

void handleKeyPressed(state *gameState, gamePixel matrix[ROWS][COLUMS]) {
  gameState->keyPressed = getch();
  switch (gameState->keyPressed) {
    case KEY_D:
    case KEY_SMALL_D:
    case KEY_RIGHT:
      gameState->player.car.x = RIGHT_STREET_SIDE;
      break;
    case KEY_A:
    case KEY_SMALL_A:
    case KEY_LEFT:
      gameState->player.car.x = LEFT_STREET_SIDE;
      break;
    case KEY_ESCAPE: exit(0);
    case KEY_SPACE_BAR:
      if (gameState->cycles >= LV2_TRIGGER) {
        gameState->currentSpeed = SPEED_FAST;
      } else {
        gameState->currentSpeed = gameState->currentSpeed == SPEED_FAST ? SPEED_NORMAL : SPEED_FAST;
      }
      break;
  }
}

void updateHighScore(car enemies[ENEMY_NUMBER], int *score) {
  int enemy;
  for (enemy = 0; enemy < ENEMY_NUMBER; enemy++) {
    enemies[enemy].y++;
    if (enemies[enemy].y == ROWS - 1) {
      *score += 50;
    }
  }
}