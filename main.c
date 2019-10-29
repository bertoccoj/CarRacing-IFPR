#include "carracing.h"

int main() {
  char gameMatrix[ROWS][COLUMS];

  int gameOver;
  ShowConsoleCursor(0);
  // while (!gameMenu());
  initMatrix(gameMatrix);
  drawPista(gameMatrix, 2);
  system("cls");
  while (!gameOver) {
    gotoxy(0,0);
    printGameMatrix(gameMatrix);
  }
  system("pause");
  return 0;
}