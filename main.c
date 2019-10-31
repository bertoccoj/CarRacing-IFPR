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
  car player = { COLUMS + 4, ROWS - 6 };
  playerX = player.x;
  playerY = player.y;

  int enemyX = COLUMS + 4;
  int enemyY = -5;

  // while (!gameMenu());

  system("cls");
  initMatrix(gameMatrix);
  drawCar(playerX, playerY, gameMatrix, PIXEL);
  drawCar(enemyX, enemyY, gameMatrix, PIXEL);
  initPista(gameMatrix);
  drawPista(gameMatrix, speed);

  while (!gameOver) {
    speed++;
    if (speed % 2 == 0) {
      drawPista(gameMatrix, speed);
      
      if (enemyY > ROWS - 2) {
        enemyX = rand() % 100 > 50 ? COLUMS + 4 : COLUMS + 8;
        enemyY = -5;
      }
      drawCar(enemyX, enemyY, gameMatrix, EMPTY_PIXEL);
      enemyY++;
      drawCar(enemyX, enemyY, gameMatrix, PIXEL);
    }

    if (kbhit()) {
      keyPressed = getch();
      drawCar(playerX, playerY, gameMatrix, EMPTY_PIXEL);
      switch (keyPressed) {
        case KEY_D:
        case KEY_SMALL_D:
          if (playerX != COLUMS + 8) { playerX += 4; }
          break;
        case KEY_A:
        case KEY_SMALL_A:
          if (playerX != COLUMS + 4) { playerX -= 4; }
          break;
      }
      drawCar(playerX, playerY, gameMatrix, PIXEL);
    }
    
    if (playerCollided(playerX, playerY, gameMatrix)) {
      gameOver = 1;
    }
    printGameMatrix(gameMatrix);
  }
  system("pause");
  return 0;
}