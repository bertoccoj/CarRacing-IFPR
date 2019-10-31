#include "carracing.h"

int main() {
  SetConsoleTitle("CAR RACING - IFPR");
  system("mode con: cols=101 lines=60");
  system("cls");  
  ShowConsoleCursor(0);
  char gameMatrix[ROWS][COLUMS];
  int gameOver = 0;
  int keyPressed;
  int playerX, playerY;
  int speed = 2;

  //posição inicial
  playerX = COLUMS + 4;
  playerY = ROWS - 6;

  // while (!gameMenu());
  system("cls");
  initMatrix(gameMatrix);
  drawCar(playerX, playerY, gameMatrix, PIXEL);
  initPista(gameMatrix);
  drawPista(gameMatrix, speed);

  while (!gameOver) {
    speed++;
    if (speed % 5 == 0) {
      drawPista(gameMatrix, speed);
    }

    if (kbhit()) {
      keyPressed = getch();
      switch (keyPressed) {
        case KEY_D:
        case KEY_SMALL_D:
          drawCar(playerX, playerY, gameMatrix, EMPTY_PIXEL);
          drawCar(playerX + 3, playerY, gameMatrix, PIXEL);
          break;
        case KEY_A:
        case KEY_SMALL_A:
          drawCar(playerX + 3, playerY, gameMatrix, EMPTY_PIXEL);
          drawCar(playerX, playerY, gameMatrix, PIXEL);
          break;
      }
    }
    printGameMatrix(gameMatrix);
  }
  system("pause");
  return 0;
}