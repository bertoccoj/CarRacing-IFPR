#include "carracing.h"
void drawLine(char symbol, int color) {
  int i;
  printf("\n\t");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
  for (i = 0; i < (MENU_LINE_LENGTH / 2) - 50; i++) {
  // for (i = 0; i < (MENU_LINE_LENGTH / 2) - 50; i++) {
    printf(" ");
  }
  for (i = 0; i < MENU_LINE_LENGTH; i++) {
    printf("%c", symbol);
  }
}

void printTextCenter(char *text, int lineBreak, int color) {
  int i;
  for (i = 0; i < lineBreak; i++) {
    printf("\n");
  }
  for (i = 0; i < 50 - (strlen(text) / 2); i++) {
    printf(" ");
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
  printf(text);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
}

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

void askPlayerInfo(gamer *player) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  system("cls");
  printf("%s", player);
  printTextCenter("DIGITE SEU NOME: ", 5, COLOR_WHITE);

  SetConsoleTextAttribute(out, COLOR_GREEN);
  scanf("%[a-z A-Z]%*c", player->name); 
  
  system("cls");
  printTextCenter(player->name, 3, COLOR_GREEN);
  printTextCenter("ESCOLHA A COR DO SEU CARRO:\n", 5, COLOR_WHITE);
  int x, y, selectedColor = 1;
  int h = 17, w = 16;

  gamePixel carMenu[h][w];

  while(true) {
    car car = { 9, 6, COLOR_RED };
    gamePixel replacement = { PIXEL_SOLID, selectedColor };
    for (y = 0; y < h; y++) {
      for (x = 0; x < w; x++) {
        carMenu[y][x].simbolo = PIXEL;
        if (selectedColor == y && x == 3) {
          carMenu[y][x - 1].simbolo = '>';
          carMenu[y][x - 1].color = COLOR_WHITE;
        }

        if (y == 0 || y == h - 1 || x == 0 || x == w - 1) {
          carMenu[y][x].color   = COLOR_WHITE;
        } else if (x == 4) {
          carMenu[y][x].color   = y;
          carMenu[y][x].simbolo = PIXEL_SOLID;
        } else {
          carMenu[y][x].color   = COLOR_BLACK;
        }
      }
    }

    carMenu[car.y][car.x]         = replacement;
    carMenu[car.y + 1][car.x]     = replacement;
    carMenu[car.y + 2][car.x]     = replacement;
    carMenu[car.y + 1][car.x -1]  = replacement;
    carMenu[car.y + 1][car.x + 1] = replacement;
    carMenu[car.y + 3][car.x + 1] = replacement;
    carMenu[car.y + 3][car.x - 1] = replacement;

    for (y = 0; y < h; y++) {
      for (x = 0; x < w; x++) {
        printChar(
          ((SCALE/2) * x + SCREEN_CENTER - 5),
          ((SCALE/2) * y) + 15,
          &carMenu[y][x].simbolo,
          carMenu[y][x].color
        );
      }
    }

    if (kbhit()) { 
      switch (getch()) {
        case KEY_UP:
          if (selectedColor > 1) {
            selectedColor--;
          }
          break;
        case KEY_DOWN:
          if (selectedColor < h - 2) {
            selectedColor++;
          }
          break;
        case KEY_RETURN:
          player->car.color = selectedColor;
          return;
          break;
      }
    }
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
      gotoxy(i,i);
      printf("\n%d -name: %s, score: %d\n\n", i + 1, scores[i].playerName, scores[i].score);
    }
  }
  system("pause");

}

int gameOverScreen(gamer player) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  int selectedOption = 1;
  int i;
  system("cls");
  while(true) {
    gotoxy(0,0);

    printTextCenter("",5,1);
    drawLine('\xDB', COLOR_RED);
    printTextCenter("GAME OVER", 2, COLOR_RED);
    SetConsoleTextAttribute(out, COLOR_GREEN);
    printf("\n\t\t\t\t\t%s -- %d pontos\n", player.name, player.score);
    printf("\t");
    drawLine('_', COLOR_RED);
    SetConsoleTextAttribute(out, COLOR_GREEN);
    printf("\n\n\t\t\t\t        Deseja tentar novamente?\n");
    SetConsoleTextAttribute(out, selectedOption == 1 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t\t    SIM    ");
    SetConsoleTextAttribute(out, selectedOption == 2 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t\t    NAO    ");

    printf("\n\t");
    SetConsoleTextAttribute(out, COLOR_RED);
    for (i = 0; i < MENU_LINE_LENGTH; i++) {
      printf("_");
    }
    if (kbhit()) { 
      switch (getch()) {
        case KEY_UP:
          if (selectedOption > 1) {
            selectedOption--;
          }
          break;
        case KEY_DOWN:
          if (selectedOption < 2) {
            selectedOption++;
          }
          break;
        case KEY_SPACE_BAR:
        case KEY_RETURN:
          return selectedOption;
      }
    }
    drawLine('\xDB',  FOREGROUND_RED);
  }
}

int gameMenuOptions() {
  int selectedOption = 1;
  int i;
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  while(1) {
    gotoxy(0,0);
    printTextCenter("",5,1);
    SetConsoleTextAttribute(out, COLOR_RED);
    drawLine('\xDB', COLOR_RED);
    printTextCenter("Car Racing\n",1,COLOR_BLUE);
    drawLine('_', COLOR_RED);

    printTextCenter("Selecione uma opcao\n",1, COLOR_BLUE);
    printTextCenter("  Novo Jogo  \n", 0, selectedOption == 1 ? BACKGROUND_RED : COLOR_WHITE);
    printTextCenter("  High Scores  \n", 0, selectedOption == 2 ? BACKGROUND_RED : COLOR_WHITE);
    printTextCenter("  sair  \n", 0, selectedOption == 3 ? BACKGROUND_RED : COLOR_WHITE);

    drawLine('_', COLOR_RED);
    if (kbhit()) { 
      switch (getch()) {
        case KEY_W:
        case KEY_SMALL_W:
        case KEY_UP:
          if (selectedOption > 1) {
            selectedOption--;
          }
          break;
        case KEY_S:
        case KEY_DOWN:
          if (selectedOption < 3) {
            selectedOption++; 
          }
          break;
        case KEY_RETURN:
          return selectedOption;
      }
    }
    drawLine('_', COLOR_WHITE);
    drawLine('\xDB', FOREGROUND_RED);
  }
}