#include "carracing.h"

void initMatrix(gamePixel matrix[ROWS][COLUMS]) {
  int y, x;

  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMS; x++) {
      matrix[y][x].simbolo = PIXEL;
      matrix[y][x].color = COLOR_GRAY;
    }
  }
}

void printGameMatrix(gamePixel matrix[ROWS][COLUMS]) {
  int y, x;

  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMS; x++) {
      printChar(2 * x + SCREEN_CENTER, 2 * y + 5, &matrix[y][x].simbolo, matrix[y][x].color);
    }
  }
}

int playerCollided(int x, int y, gamePixel matrix[ROWS][COLUMS]) {
  return matrix[y - 1][x].simbolo != PIXEL
      || matrix[y - 1][x + 1].simbolo != PIXEL
      || matrix[y - 1][x - 1].simbolo != PIXEL
        ? 1 : 0;
}

void drawCar(int x, int y, gamePixel matrix[ROWS][COLUMS], int simbolo, int color) {
  gamePixel replacement = { simbolo, color };

  if (y + 2 > 0 && y < ROWS - 2) matrix[y][x] = replacement;
  if (y + 3 > 0 && y < ROWS - 3) matrix[y + 1][x] = replacement;
  if (y + 4 > 0 && y < ROWS - 4) matrix[y + 2][x] = replacement;
  if (y + 3 > 0 && y < ROWS - 3) matrix[y + 1][x -1] = replacement;
  if (y + 3 > 0 && y < ROWS - 3) matrix[y + 1][x + 1] = replacement;
  if (y + 5 > 0 && y < ROWS - 5) matrix[y + 3][x + 1] = replacement;
  if (y + 5 > 0 && y < ROWS - 5) matrix[y + 3][x - 1] = replacement;
}

void initEnemies(car enemies[ENEMY_NUMBER]){
  int t;
  for (t = 1; t <= ENEMY_NUMBER; t++) {
    car dummy = { 
      rand() % 100 > 50 ? COLUMS + 4 : COLUMS + 8,
      t * (ENEMY_DISTANCE),
      COLOR_GREEN
    };
    enemies[t - 1] = dummy;
  }
}

void drawEnemies(car enemies[ENEMY_NUMBER], gamePixel matrix[ROWS][COLUMS], int clear) {
  int i;
  for(i = 0; i < ENEMY_NUMBER; i++) {
    drawCar(enemies[i].x, enemies[i].y, matrix, clear ? PIXEL : PIXEL_SOLID, clear ? COLOR_GRAY : enemies[i].color);
  }
}

void initPista(gamePixel matrix[ROWS][COLUMS]) {
  gamePixel bordaOut = { PIXEL, COLOR_GREEN };
  gamePixel bottom = { PIXEL2, COLOR_YELLOW };
  int i, j;

  for (i = 0; i < ROWS; i++) {
    matrix[i][0] = bordaOut;
    matrix[i][COLUMS - 1] = bordaOut;
    for (j = 0; j < COLUMS; j++) {
      matrix[ROWS - 1][j] = bottom;
    }
  }
}

void clearPista(gamePixel matrix[ROWS][COLUMS]) {
  int i;
  for (i = 0; i < ROWS - 1; i++) {
    matrix[i][1].simbolo = EMPTY_PIXEL;
    matrix[i][1].color = COLOR_BLACK;
    matrix[i][COLUMS - 2].simbolo = EMPTY_PIXEL;
    matrix[i][COLUMS - 2].color = COLOR_BLACK;
    matrix[i][COLUMS / 2].simbolo = PIXEL;
    matrix[i][COLUMS / 2].color = COLOR_GRAY;
  }
}

void drawPista(gamePixel matrix[ROWS][COLUMS]) {
  gamePixel bordain;
  gamePixel center = { PIXEL, COLOR_LIGHT_YELLOW };
  int i, j;

  bordain.simbolo = PIXEL_SOLID;

  if (matrix[0][1].color != COLOR_WHITE) {
    clearPista(matrix);
    for (i = 0; i < ROWS - 1; i++) {
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
    for (i = 0; i < ROWS - 1; i++) {
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

int gameMenu() {
  int selectedOption = 1;
  int i;
  int lineWidth = 85;

  while(1) {
    gotoxy(0,0);
    

    printf("\n\n\n\n\t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("\xDB");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_BLUE);
    printf("\n\t\t\t\t\t     Car Racing\n");
    printf("\t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("_");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_GREEN);
    printf("\n\n\t\t\t\t        Selecione uma opcao\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selectedOption == 1 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t 1 - Novo Jogo    ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selectedOption == 2 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t 2 - High Scores  ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selectedOption == 3 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t 3 - Sair         \n");

    printf("\n\t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("_");
    }
    if (kbhit()) { 
      switch (getch()) {
        case KEY_UP:
          if (selectedOption > 1) {
            selectedOption--;
          }
          break;
        case KEY_DOWN:
          if (selectedOption < 3) {
            selectedOption++; 
          }
          break;
        case KEY_SPACE_BAR:
          return selectedOption;
      }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("\n\n\t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("\xDB");
    }
  }
}