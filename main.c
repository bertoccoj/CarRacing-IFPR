#include "carracing.h"

int main() {
  // altera configurações do console
  ShowConsoleCursor(false);              // esconde o cursor
  SetConsoleTitle("CAR RACING - IFPR");  // titulo da janela
  system("mode con: cols=100 lines=70"); // tamanho da janela
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

    // reseta a fonte para branco
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);

    // limpa a tela e desenha a borda do jogo
    system("cls");
    drawBorder(COLOR_WHITE);
    initMatrix(gameMatrix);
    drawCar(gameState.player.car, gameMatrix, PIXEL_SOLID, gameState.player.car.color);
    drawEnemies(adversarios, gameMatrix, false);
    initPista(gameMatrix, COLOR_GREEN);
    drawPista(gameMatrix);
    while (!gameState.gameOver) {
      gotoxy(0,0);
      #if DEBUG == 1
        printf("playerCar X: %d \nplayerCar Y: %d\n", gameState.player.car.x, gameState.player.car.y);
        printf("\ngameState.currentSpeed: %d", gameState.currentSpeed);
        printf("\nRIGHT_STREET_SIDE: %d", RIGHT_STREET_SIDE);
        printf("\nLEFT_STREET_SIDE: %d", LEFT_STREET_SIDE);
        printf("\ngameState.cycles: %d", gameState.cycles);
        printf("\ngameState.gameOver: %d", gameState.gameOver);
      #endif
      printScore(gameState.player, gameState.currentStage);

      gameState.cycles++;
      if (gameState.cycles == LV2_TRIGGER) {
        drawBorder(COLOR_YELLOW);
        gameState.currentSpeed = SPEED_FAST;
        gameState.currentStage = 2;
      }

      if (gameState.cycles % gameState.currentSpeed == 0) {
        drawPista(gameMatrix);

        int enemy;
        drawEnemies(adversarios, gameMatrix, true);
        updateHighScore(adversarios, &gameState.player.score);
        drawEnemies(adversarios, gameMatrix, false);

        // verifica se cada inimigo desapareceu da tela
        // reinicializa inimigos quando todos desapareceram da tela
        if (adversarios[ENEMY_NUMBER - 1].y >= ROWS - 1) {
          initEnemies(adversarios);
        }
      }

      // Key events
      drawCar(gameState.player.car, gameMatrix, PIXEL, COLOR_GRAY);
      if (kbhit()) handleKeyPressed(&gameState, gameMatrix);
      drawCar(gameState.player.car, gameMatrix, PIXEL_SOLID, gameState.player.car.color);

      if (playerCollided(gameState.player.car, gameMatrix) || playerCollidedSides(gameState.player.car, gameMatrix)) {
        initPista(gameMatrix, COLOR_RED);
        drawBorder(COLOR_RED);
        gameState.gameOver = true;
      }
      drawGameMatrix(gameMatrix);
    }
    if (gameState.gameOver) {
      Sleep(500);
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
