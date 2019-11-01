#include "carracing.h"

void initMatrix(char matrix[ROWS][COLUMS]) {
  int i, j;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLUMS; j++) {
      matrix[i][j] = ' ';
    }
  }
}

int playerCollided(int x, int y, char matrix[ROWS][COLUMS]) {
  if (
    matrix[y - 1][x] != EMPTY_PIXEL
    || matrix[y - 1][x + 1] != EMPTY_PIXEL
    || matrix[y - 1][x - 1] != EMPTY_PIXEL
    ){
      return 1;
    } else { 
      return 0;
    }
}

void drawCar(int x, int y, char matrix[ROWS][COLUMS], int simbolo) {
  if (y + 2 >= 0 && y < ROWS - 2) matrix[y][x] = simbolo;
  if (y + 3 >= 0 && y < ROWS - 3) matrix[y + 1][x] = simbolo;
  if (y + 3 >= 0 && y < ROWS - 4) matrix[y + 2][x] = simbolo;
  if (y + 3 >= 0 && y < ROWS - 3) matrix[y + 1][x -1] = simbolo;
  if (y + 3 >= 0 && y < ROWS - 3) matrix[y + 1][x + 1] = simbolo;
  if (y + 5 >= 0 && y < ROWS - 5) matrix[y + 3][x + 1] = simbolo;
  if (y + 5 >= 0 && y < ROWS - 5) matrix[y + 3][x - 1] = simbolo;
}

void initPista(char matrix[ROWS][COLUMS]) {
  int i, j;
  for (i = 0; i < ROWS; i++) {
    matrix[i][0] = ASTERISCO;
    matrix[i][COLUMS - 1] = ASTERISCO;
    for (j = 0; j < COLUMS; j++) {
      matrix[ROWS - 1][j] = '.';
    }
  }
}

void clearPista(char matrix[ROWS][COLUMS]) {
  int i;
  for (i = 0; i < ROWS - 1; i++) {
    matrix[i][1] = EMPTY_PIXEL;
    matrix[i][COLUMS - 2] = EMPTY_PIXEL;
  }
}

void drawPista(char matrix[ROWS][COLUMS], int speed) {
  int i, j;

  if (matrix[0][1] == EMPTY_PIXEL) {
    clearPista(matrix);
    for (i = 0; i < ROWS - 1; i++) {
      if (i % 2 == 0) {
        matrix[i][1] = PIXEL;
        matrix[i][COLUMS - 2] = PIXEL;
      }
    }
  } else {
    clearPista(matrix);    
    for (i = 0; i < ROWS - 1; i++) {
      if (i % 2 != 0) {
        matrix[i][1] = PIXEL;
        matrix[i][COLUMS - 2] = PIXEL;
      }
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
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    for (i = 0; i < lineWidth; i++) {
    printf("\xDB");
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    printf("\n\t\t\t\t\t     Car Racing\n");
    printf("\t");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    for (i = 0; i < lineWidth; i++) {
    printf("_");
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
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