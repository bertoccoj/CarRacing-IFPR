#include "carracing.h"

int main() {
  SetConsoleTitle("CAR RACING - IFPR");
  system("mode con: cols=101 lines=60");
  system("cls");
  ShowConsoleCursor(0);
  gamePixel gameMatrix[ROWS][COLUMS];
  int gameOver = 0;
  int keyPressed;
  int refreshRate = 4;
  int currentStage = 1;
  int speedModifyer = 2;
  int cycles = 0;
  int score = 0;

  //inicialização do player
  car player = { COLUMS + 4, ROWS - 6, COLOR_BLUE };

  //inicialização dos inimigos
  car enemies[ENEMY_NUMBER];
  int t;
  initEnemies(enemies);
  // int opcaoMenu = gameMenu();

  // system("cls");
  initMatrix(gameMatrix);
  drawCar(player.x, player.y, gameMatrix, PIXEL_SOLID, player.color);
  drawEnemies(enemies, gameMatrix, false);
  initPista(gameMatrix);
  drawPista(gameMatrix);

  while (!gameOver) {
    gotoxy(0,0);
    #if DEBUG == 1
      printf("Player X: %d \nPlayer Y: %d\n", player.x, player.y);
      printf("\nSpeedModifier: %d", speedModifyer);
      printf("\nciclps: %d", cycles);
      printf("\ngameOver: %d", gameOver);
    #endif
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\tScore: %d", score);
    printf("\n\t\t\t\t\t\t\t\t\tFase: %d", currentStage);

    cycles++;
    if (cycles >= 800) {
      speedModifyer = 1;
      currentStage = 2;
    }

    if (cycles % speedModifyer == 0) {
      drawPista(gameMatrix);
      
      int w;
      drawEnemies(enemies, gameMatrix, true);
      for (w = 0; w < ENEMY_NUMBER; w++) {
        enemies[w].y++;
      }
      drawEnemies(enemies, gameMatrix, false);

      // verifica se cada inimigo desapareceu da tela
      for (w = 0; w < ENEMY_NUMBER; w++) {
        if (enemies[w].y == ROWS - 1) {
          score += 50;
        }
      }

      // reseta inimigos quando todos desapareceram
      if (enemies[ENEMY_NUMBER - 1].y >= ROWS - 1) {
        initEnemies(enemies);
      }
    }
    drawCar(player.x, player.y, gameMatrix, PIXEL_SOLID, player.color);

//--Key events
    if (kbhit()) {
      keyPressed = getch();
      drawCar(player.x, player.y, gameMatrix, PIXEL, COLOR_GRAY);
      switch (keyPressed) {
        case KEY_D:
        case KEY_SMALL_D:
        case KEY_RIGHT:
          if (player.x != COLUMS + 8) { player.x ++; }
          break;
        case KEY_A:
        case KEY_SMALL_A:
        case KEY_LEFT:
          if (player.x != COLUMS + 4) { player.x --; }
          break;
        case KEY_SPACE_BAR:
          if (cycles >= 800) {
            speedModifyer = 1;
          } else {
            speedModifyer = speedModifyer == 1 && cycles < 800 ? 2 : 1;
          }
          break;
      }
      drawCar(player.x, player.y, gameMatrix, PIXEL_SOLID, player.color);
    }

    if (playerCollided(player.x, player.y, gameMatrix)) {
      gameOver = 1;
    }
    printGameMatrix(gameMatrix);
  }
  system("pause");
  return 0;
}