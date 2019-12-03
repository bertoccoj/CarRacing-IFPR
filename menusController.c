#include "carracing.h"
void drawLine(char symbol, int color, int size) {
  int i;
  printf("\n\t");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
  for (i = 0; i < (size / 2) - 50; i++) {
    printf(" ");
  }
  for (i = 0; i < size; i++) {
    printf("%c", symbol);
  }
}

void printTextCenter(char *text, int lineBreakbefore, int color){
  int i;
  for (i = 0; i < lineBreakbefore; i++) {
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
      highScoresScreen(false); 
      gameMenu(gameState);
      break;
    case MENU_QUIT: exit(false);
  }
}

void highScoresScreen(int isGameOverScreen) {
  if (!isGameOverScreen) {
    system("cls");
  }
  highScore scores[5];
  int registros = getHighScoreCount();

  if (registros == 0) {
    drawLine(PIXEL, COLOR_LIGHT_BLUE, MENU_LINE_LENGTH);
    printTextCenter("AINDA NAO EXISTE NENHUM HIGH STORE REGISTRADO!!", 1, COLOR_LIGHT_PURPLE);
    drawLine(PIXEL, COLOR_LIGHT_BLUE, MENU_LINE_LENGTH);
  } else {
    int i, height = isGameOverScreen ? 25 : 13;
    readHighScoresFile(scores);
    gotoxy(0, isGameOverScreen ? 18 : 7);
    printTextCenter("HIGH SCORES\n", 2, COLOR_WHITE);
    drawLine(PIXEL, COLOR_LIGHT_BLUE, MENU_LINE_LENGTH);
    int colors[5] = { COLOR_LIGHT_YELLOW, COLOR_YELLOW, COLOR_GREEN, COLOR_BLUE, COLOR_PURPLE };
    for(i = 0; i < registros; i++) {
      gotoxy(SCREEN_CENTER - 10, (i * 3) + height);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHT_BLUE);
      printf("%d NOME:", i + 1);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[i]);
      printf(" %s ", scores[i].playerName);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
      gotoxy(SCREEN_CENTER + 20, (i * 3) + height);
      printf("---");
      gotoxy(SCREEN_CENTER + 30, (i * 3) + height);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[i]);
      printf(" %d\n\n", scores[i].score);
    }
    drawLine(PIXEL, COLOR_LIGHT_BLUE, MENU_LINE_LENGTH);
  }
  if (!isGameOverScreen) {
    printTextCenter("                 ", 2, BACKGROUND_RED);
    printTextCenter("    <- voltar    ", 1, BACKGROUND_RED);
    printTextCenter("                 ", 1, BACKGROUND_RED);
    getch();
  }
  
}

int gameOverScreen(gamer player) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  int selectedOption = 1;
  int i;
  char text[100];
  sprintf(text, "%s -- %d pontos", player.name, player.score);

  system("cls");
  while(true) {
    gotoxy(0,0);

    printf("\n\n\n\n\n");
    drawLine('\xDB', COLOR_RED, MENU_LINE_LENGTH);
    printTextCenter("GAME OVER", 2, COLOR_RED);

    printTextCenter(text, 2, COLOR_GREEN);
    drawLine('_', COLOR_RED, MENU_LINE_LENGTH);
    printTextCenter("Deseja tentar novamente?", 2, COLOR_GREEN);
    printTextCenter("    SIM    ", 2, selectedOption == 1 ? BACKGROUND_RED : 1);
    printTextCenter("    NAO    ", 2, selectedOption == 2 ? BACKGROUND_RED : 1);

    drawLine('_', COLOR_RED, MENU_LINE_LENGTH);

    highScoresScreen(true);
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
    drawLine('\xDB',  FOREGROUND_RED, MENU_LINE_LENGTH);
  }
}

int gameMenuOptions() {
  int selectedOption = 1;
  int i;
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  while(1) {

    gotoxy(0,0);
    printf("\n\n\n\n\n");
    drawLine('\xDB', COLOR_RED, MENU_LINE_LENGTH);
    printTextCenter("Car Racing", 1, COLOR_LIGHT_AQUA);
    drawLine('_', COLOR_RED, MENU_LINE_LENGTH);

    printTextCenter("Selecione uma opcao", 1, COLOR_LIGHT_AQUA);
    printTextCenter("  Novo Jogo  ", 3, selectedOption == 1 ? BACKGROUND_RED : COLOR_WHITE);
    printTextCenter("  High Scores  ", 1, selectedOption == 2 ? BACKGROUND_RED : COLOR_WHITE);
    printTextCenter("  sair  ", 1, selectedOption == 3 ? BACKGROUND_RED : COLOR_WHITE);

    drawLine('_', COLOR_RED, MENU_LINE_LENGTH);
    if (kbhit()) { 
      switch (getch()) {
        case KEY_UP:
          if (selectedOption > 1) {
            selectedOption--;
          }
          break;
        case KEY_DOWN:
          if (selectedOption < 3) {
            selectedOption++; 
          }
          break;
        case KEY_RETURN:
          return selectedOption;
      }
    }
    drawLine('_', COLOR_WHITE, MENU_LINE_LENGTH);
    drawLine('\xDB', FOREGROUND_RED, MENU_LINE_LENGTH);
  }
}

void askPlayerInfo(gamer *player) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  int isNameValid = false, i;

  do {
    system("cls");
    printTextCenter("Escolha Seu nome", 2, COLOR_WHITE);
    printTextCenter("Deve possuir: min 3 - max 10(caracteres)", 2, COLOR_WHITE);
    printTextCenter("\b\b\b\bDIGITE SEU NOME: ", 5, COLOR_WHITE);
    SetConsoleTextAttribute(out, COLOR_GREEN);

    fflush(stdin);
    scanf("%[a-z A-Z]%*c", player->name);
  
    if (strlen(player->name) > 10 || strlen(player->name) < 3) {
      strcpy(player->name, "  ");
      isNameValid = false;
      printTextCenter("NOME INVALIDO", 2, COLOR_RED);
      getch();
    } else {
      isNameValid = true;
    }

  } while (!isNameValid);
  
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

