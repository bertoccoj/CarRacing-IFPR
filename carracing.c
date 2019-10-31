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
  int selectedOption;
  int i;

  gotoxy(0,0);
  
  printf("\n\n\n\n\t\t\t");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
  for (i = 0; i < 50; i++) {
    printf("\xDB");
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
  printf("\n\t\t\t\t\tCar Racing\n");
  printf("\n\n\n\n\t\t\t");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
  for (i = 0; i < 50; i++) {
    printf("_");
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
  printf("\n\t\t\t\t\t1 - Novo Jogo");
  printf("\n\t\t\t\t\t2 - High Scores");
  printf("\n\t\t\t\t\t3 - Sair\n");

  printf("\n\n\n\n\t\t\t");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
  for (i = 0; i < 50; i++) {
    printf("_");
  }
  if (kbhit()) { selectedOption = getch(); }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
  printf("\n\t\t\t\tEntre com a opcao desejada %d\n", selectedOption);
  printf("\n\n\n\n\t\t\t");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
  for (i = 0; i < 50; i++) {
    printf("\xDB");
  }
  return selectedOption == MENU_NEW_GAME || selectedOption == MENU_HIGH_SCORES || selectedOption == MENU_QUIT;
}

void printGameMatrix(char matrix[ROWS][COLUMS]) {
  int y, x;

  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMS; x++) {
      printChar(2 * x + SCREEN_CENTER, 2 * y + 5, &matrix[y][x], FOREGROUND_BLUE);
      // printChar(j + SCREEN_CENTER, i + 5, &matrix[i][j], FOREGROUND_BLUE);
    }
  }
}
