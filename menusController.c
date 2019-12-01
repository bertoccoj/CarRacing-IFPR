#include "carracing.h"

// função que mostra o menu e controla a ação a ser tomada baseado na opção selecionada
void gameMenu(state *gameState) {
  system("cls");
  switch (gameMenuOptions()) {
    case MENU_NEW_GAME:
      askPlayerInfo(&gameState->player);
      break;
    case MENU_HIGH_SCORES:
      highScoresScreen(); 
      gameMenu(gameState);
      break;
    case MENU_QUIT: exit(false);
  }
}

void highScoresScreen() {
  system("cls");
  highScore scores[5];
  int registros = getHighScoreCount();

  if (registros == 0) {
    printf("não há high scores registrados");
  } else {
    readHighScoresFile(scores);
    int i;
    
    for(i = 0; i < registros; i++) {
      printf("\n%d -name: %s, score: %d\n\n", i + 1, scores[i].playerName, scores[i].score);
    }
  }
  system("pause");

}
