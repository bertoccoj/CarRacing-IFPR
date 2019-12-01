#include "carracing.h"

int main() {
  // altera configurações do console
  ShowConsoleCursor(false);              // esconde o cursor
  SetConsoleTitle("CAR RACING - IFPR");  // titulo da janela
  system("mode con: cols=101 lines=70"); // tamanho da janela
  system("CHCP 850");                    // pagina de codigo ascii
  system("cls");

  // estado do jogo
  state gameState;
  setGameState(&gameState, false);

  // matrix de pixels
  gamePixel gameMatrix[ROWS][COLUMS];

  // menu do jogo
  gameMenu(&gameState);

  while(!gameState.quit) {
  // inicialização dos inimigos
  car adversarios[ENEMY_NUMBER];
  initEnemies(adversarios);

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
  system("cls");        
  initMatrix(gameMatrix);
  drawCar(gameState.player.car, gameMatrix, PIXEL_SOLID, gameState.player.car.color);
  drawEnemies(adversarios, gameMatrix, false);
  initPista(gameMatrix);
  drawPista(gameMatrix);

  while(!gameState.quit) {
    while (!gameState.gameOver) {
      gotoxy(0,0);
      // #if DEBUG == 1
      //   printf("playerCar X: %d \nplayerCar Y: %d\n", player.car.x, player.car.y);
      //   printf("\ngameState.currentSpeed: %d", gameState.currentSpeed);
      //   printf("\nRIGHT_STREET_SIDE: %d", RIGHT_STREET_SIDE);
      //   printf("\nLEFT_STREET_SIDE: %d", LEFT_STREET_SIDE);
      //   printf("\ngameState.cycles: %d", gameState.cycles);
      //   printf("\ngameState.gameOver: %d", gameState.gameOver);
      //   printf("\ncollided: %d", collided);
      // #endif
      printf("\n\n\n\n\t\t\t\t\t\t\t\t\t%s - Score: %d", gameState.player.name, gameState.player.score);
      printf("\n\t\t\t\t\t\t\t\t\tFase: %d", gameState.currentStage);

      if (gameState.cycles < 800) {
        gameState.cycles++;
      } else {
        gameState.currentSpeed = 1;
        gameState.currentStage = 2;
      }

      if (gameState.cycles % gameState.currentSpeed == 0) {
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
            gameState.player.score += 50;
          }
        }

        // reseta inimigos quando todos desapareceram
        if (adversarios[ENEMY_NUMBER - 1].y >= ROWS - 1) {
          initEnemies(adversarios);
        }
      }
      drawCar(gameState.player.car, gameMatrix, PIXEL_SOLID, gameState.player.car.color);

      // Key events
      if (kbhit()) {
        keyPressed = getch();
        drawCar(gameState.player.car, gameMatrix, PIXEL, COLOR_GRAY);
        switch (keyPressed) {
          case KEY_D:
          case KEY_SMALL_D:
          case KEY_RIGHT:
            gameState.player.car.x = RIGHT_STREET_SIDE;
            // if (playerCar.x != COLUMS + 8) { playerCar.x ++; }
            break;
          case KEY_A:
          case KEY_SMALL_A:
          case KEY_LEFT:
            gameState.player.car.x = LEFT_STREET_SIDE;
            // if (playerCar.x != COLUMS + 4) { playerCar.x --; }
            break;
          case KEY_SPACE_BAR:
            if (gameState.cycles >= 800) {
              gameState.currentSpeed = 1;
            } else {
              gameState.currentSpeed = gameState.currentSpeed == 1 ? 2 : 1;
            }
            break;
        }
        drawCar(gameState.player.car, gameMatrix, PIXEL_SOLID, gameState.player.car.color);
      }

      gameState.gameOver = playerCollided(gameState.player.car.x, gameState.player.car.y, gameMatrix) || playerCollidedSides(gameState.player.car, gameMatrix);
      drawGameMatrix(gameMatrix);
    }
    if (gameState.gameOver) {
      saveScore(gameState.player);
      switch(gameOverScreen(gameState.player)) {
        case 1: // Tentar novamente, mantendo o jogador
          setGameState(&gameState, true);
          break;
        case 2: // Retorna ao menu e reinicia o estado
          setGameState(&gameState, false);
          gameMenu(&gameState);
          break;
      }
    }
  }


  system("pause");
  return 0;
}
