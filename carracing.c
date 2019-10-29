#include "carracing.h"

void initMatrix(char matrix[ROWS][COLUMS]) {
  int i, j;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLUMS; j++) {
      matrix[i][j] = ' ';
    }
  }
}

void drawPista(char matrix[ROWS][COLUMS], int speed) {
  int i, j;

  for (i = 0; i < ROWS; i++) {
    matrix[i][0] = ASTERISCO;
    matrix[i][COLUMS - 1] = ASTERISCO;
    if (i % 2 != 0) {
      matrix[i][1] = PISTA;
      matrix[i][COLUMS - 2] = PISTA;
    }
    for (j = 0; j < COLUMS; j++) {
      matrix[ROWS - 1][j] = '.';
    }
  }
}

int gameMenu() {
  int selectedOption;
  int i;

  gotoxy(0,0);
  
  printf("\n\n\n\n\t\t\t");
  for (i = 0; i < 50; i++) {
    printf("\xDB");
  }
  printf("\n\t\t\t\t\tCar Racing\n");
  printf("\n\n\n\n\t\t\t");
  for (i = 0; i < 50; i++) {
    printf("_");
  }
  printf("\n\t\t\t\t\t1 - Novo Jogo");
  printf("\n\t\t\t\t\t2 - High Scores");
  printf("\n\t\t\t\t\t3 - Sair\n");

  printf("\n\n\n\n\t\t\t");
  for (i = 0; i < 50; i++) {
    printf("_");
  }
  if (kbhit()) { selectedOption = getch(); }
  printf("\n\t\t\t\tEntre com a opcao desejada %d\n", selectedOption);
  printf("\n\n\n\n\t\t\t");
  for (i = 0; i < 50; i++) {
    printf("\xDB");
  }
  return selectedOption == MENU_NEW_GAME || selectedOption == MENU_HIGH_SCORES || selectedOption == MENU_QUIT;
}

void printGameMatrix(char matrix[ROWS][COLUMS]) {
  int i, j;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLUMS; j++) {
      printChar(j + SCREEN_CENTER, i + 5, &matrix[i][j], FOREGROUND_BLUE);
    }
  }
}
