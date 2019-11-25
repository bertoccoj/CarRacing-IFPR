#include "carracing.h"

int main() {
  // altera configurações do console
  SetConsoleTitle("CAR RACING - IFPR");
  system("mode con: cols=101 lines=70");
  system("cls");
  ShowConsoleCursor(0);
  gamePixel gameMatrix[ROWS][COLUMS];
  int gameOver = 0;
  int keyPressed;
  int refreshRate = 4;
  int currentStage = 1;
  int speedModifier = 2;
  int cycles = 0;

  // inicialização do player
  gamer player;
  car playerCar = { COLUMS + 4, ROWS - 6, COLOR_BLUE };

  // menu do jogo
  
  switch (gameMenu()) {
    case MENU_NEW_GAME: 
      askPlayerName(&player);
      break;
    case MENU_HIGH_SCORES: break;
    case MENU_QUIT: exit(0);
  }

  // inicialização dos inimigos
  car enemies[ENEMY_NUMBER];
  int t;
  initEnemies(enemies);

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
  system("cls");        
  initMatrix(gameMatrix);
  drawCar(playerCar.x, playerCar.y, gameMatrix, PIXEL_SOLID, playerCar.color);
  drawEnemies(enemies, gameMatrix, false);
  initPista(gameMatrix);
  drawPista(gameMatrix);

  while (!gameOver) {
    gotoxy(0,0);
    #if DEBUG == 1
      printf("playerCar X: %d \nplayerCar Y: %d\n", playerCar.x, playerCar.y);
      printf("\nSpeedModifier: %d", speedModifier);
      printf("\nciclps: %d", cycles);
      printf("\ngameOver: %d", gameOver);
    #endif
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\t%s - Score: %d", player.name, player.score);
    printf("\n\t\t\t\t\t\t\t\t\tFase: %d", currentStage);

    if (cycles < 800) {
      cycles++;
    } else {
      speedModifier = 1;
      currentStage = 2;
    }

    if (cycles % speedModifier == 0) {
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
          player.score += 50;
        }
      }

      // reseta inimigos quando todos desapareceram
      if (enemies[ENEMY_NUMBER - 1].y >= ROWS - 1) {
        initEnemies(enemies);
      }
    }
    drawCar(playerCar.x, playerCar.y, gameMatrix, PIXEL_SOLID, playerCar.color);

    // Key events
    if (kbhit()) {
      keyPressed = getch();
      drawCar(playerCar.x, playerCar.y, gameMatrix, PIXEL, COLOR_GRAY);
      switch (keyPressed) {
        case KEY_D:
        case KEY_SMALL_D:
        case KEY_RIGHT:
          if (playerCar.x != COLUMS + 8) { playerCar.x ++; }
          break;
        case KEY_A:
        case KEY_SMALL_A:
        case KEY_LEFT:
          if (playerCar.x != COLUMS + 4) { playerCar.x --; }
          break;
        case KEY_SPACE_BAR:
          if (cycles >= 800) {
            speedModifier = 1;
          } else {
            speedModifier = speedModifier == 1 ? 2 : 1;
          }
          break;
      }
      drawCar(playerCar.x, playerCar.y, gameMatrix, PIXEL_SOLID, playerCar.color);
    }

    if (playerCollided(playerCar.x, playerCar.y, gameMatrix)) {
      gameOver = 1;
    }
    printGameMatrix(gameMatrix);
  }
  if (gameOver) {
    gameOverScreen(player);
  }
  system("pause");
  return 0;
}
