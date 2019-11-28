#include "carracing.h"

int main() {
  // altera configurações do console
  SetConsoleTitle("CAR RACING - IFPR");
  setConsoleInfo();
  SMALL_RECT windowSize = {0, 0, 101, 80};
  COORD bufferSize = {101, 57};
  SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
  SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
  
  // system("mode con: cols=101 lines=70");
  system("cls");
  ShowConsoleCursor(0);
  gamePixel gameMatrix[ROWS][COLUMS];
  int gameOver = 0;
  int keyPressed;
  int refreshRate = 4;
  int currentStage = 1;
  int speedModifier = 2;
  int cycles = 0;
  int collided = 0;

  // inicialização do player
  gamer player;
  car playerCar = { COLUMS + 4, ROWS - 6, COLOR_BLUE };

  // menu do jogo
  
  // switch (gameMenu()) {
  //   case MENU_NEW_GAME: 
  //     askPlayerName(&player);
  //     break;
  //   case MENU_HIGH_SCORES: break;
  //   case MENU_QUIT: exit(0);
  // }

  // inicialização dos inimigos
  car adversarios[ENEMY_NUMBER];
  int t;
  initEnemies(adversarios);

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
  system("cls");        
  initMatrix(gameMatrix);
  drawCar(playerCar.x, playerCar.y, gameMatrix, PIXEL_SOLID, playerCar.color);
  drawEnemies(adversarios, gameMatrix, false);
  initPista(gameMatrix);
  drawPista(gameMatrix);

  while (!gameOver) {
    gotoxy(0,0);
    #if DEBUG == 1
      printf("playerCar X: %d \nplayerCar Y: %d\n", playerCar.x, playerCar.y);
      printf("\nSpeedModifier: %d", speedModifier);
      printf("\nRIGHT_STREET_SIDE: %d", RIGHT_STREET_SIDE);
      printf("\nLEFT_STREET_SIDE: %d", LEFT_STREET_SIDE);
      printf("\nciclps: %d", cycles);
      printf("\ngameOver: %d", gameOver);
      printf("\ncollided: %d", collided);
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
      // Sleep(0);
      drawPista(gameMatrix);

      int w;
      drawEnemies(adversarios, gameMatrix, true);
      for (w = 0; w < ENEMY_NUMBER; w++) {
        adversarios[w].y++;
      }
      drawEnemies(adversarios, gameMatrix, false);

      // verifica se cada inimigo desapareceu da tela
      for (w = 0; w < ENEMY_NUMBER; w++) {
        if (adversarios[w].y == ROWS - 1) {
          player.score += 50;
        }
      }

      // reseta inimigos quando todos desapareceram
      if (adversarios[ENEMY_NUMBER - 1].y >= ROWS - 1) {
        initEnemies(adversarios);
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
          playerCar.x = RIGHT_STREET_SIDE;
          // if (playerCar.x != COLUMS + 8) { playerCar.x ++; }
          break;
        case KEY_A:
        case KEY_SMALL_A:
        case KEY_LEFT:
          playerCar.x = LEFT_STREET_SIDE;
          // if (playerCar.x != COLUMS + 4) { playerCar.x --; }
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

    // collided = playerCollided(playerCar.x, playerCar.y, gameMatrix) || playerCollidedSides(playerCar, gameMatrix);
    // if (collided) {
    //   gameOver = true;
    // }
    printGameMatrix(gameMatrix);
  }
  if (gameOver) {
    system("pause");
    gameOverScreen(player);
  }
  system("pause");
  return 0;
}
