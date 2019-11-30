#include "carracing.h"

state getInitialGameState() {
  gamer player = {
    "",                                   // nome
    { COLUMS + 4, ROWS - 6, COLOR_BLUE }, // car
    false,                                // hasCollided
    0,                                    // score
  };                                      

  //--estado inicial
  state initialState = {
    false,      // gameOver
    false,      // quit
    1,          // currentStage
    2,          // currentSpeed
    0,          // cycles
    player,     // player
  };
  return initialState;
}

void initMatrix(gamePixel matrix[ROWS][COLUMS]) {
  int y, x;

  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMS; x++) {
      matrix[y][x].simbolo = PIXEL;
      matrix[y][x].color = COLOR_GRAY;
    }
  }
}

void printGameMatrix(gamePixel matrix[ROWS][COLUMS]) {
  int y, x;
  CHAR_INFO consoleBuffer[ROWS * COLUMS];

  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMS; x++) {
      printChar(
        ((SCALE/2) * x) + SCREEN_CENTER, // posição X
        ((SCALE/2) * y) + 5,             // posição Y
        &matrix[y][x].simbolo,           // caracteer do pixel
        matrix[y][x].color               // cor que vai printar
      );
    }
  }
}

int playerCollided(int x, int y, gamePixel matrix[ROWS][COLUMS]) {
  return matrix[y - 1][x].simbolo != PIXEL;
}

int playerCollidedSides(car player, gamePixel matrix[ROWS][COLUMS]) {
  switch (player.x) {
    case LEFT_STREET_SIDE: 
      return matrix[player.y - 1][LEFT_STREET_SIDE].simbolo != PIXEL || matrix[player.y + 3][LEFT_STREET_SIDE].simbolo != PIXEL;
    case RIGHT_STREET_SIDE: 
      return matrix[player.y - 1][RIGHT_STREET_SIDE].simbolo != PIXEL || matrix[player.y + 3][RIGHT_STREET_SIDE].simbolo != PIXEL;
    default: return 0;
  }
}

void drawCar(car car, gamePixel matrix[ROWS][COLUMS], int simbolo, int color) {
  gamePixel replacement = { simbolo, color };

  if (car.y + 2 > 0 && car.y < ROWS - 2) matrix[car.y][car.x] = replacement;
  if (car.y + 3 > 0 && car.y < ROWS - 3) matrix[car.y + 1][car.x] = replacement;
  if (car.y + 4 > 0 && car.y < ROWS - 4) matrix[car.y + 2][car.x] = replacement;
  if (car.y + 3 > 0 && car.y < ROWS - 3) matrix[car.y + 1][car.x -1] = replacement;
  if (car.y + 3 > 0 && car.y < ROWS - 3) matrix[car.y + 1][car.x + 1] = replacement;
  if (car.y + 5 > 0 && car.y < ROWS - 5) matrix[car.y + 3][car.x + 1] = replacement;
  if (car.y + 5 > 0 && car.y < ROWS - 5) matrix[car.y + 3][car.x - 1] = replacement;
}

void initEnemies(car enemies[ENEMY_NUMBER]){
  int t;
  for (t = 1; t <= ENEMY_NUMBER; t++) {
    car dummy = { 
      rand() % 100 > 50 ? COLUMS + 4 : COLUMS + 8,
      t * (ENEMY_DISTANCE),
      COLOR_GREEN
    };
    enemies[t - 1] = dummy;
  }
}

void drawEnemies(car enemies[ENEMY_NUMBER], gamePixel matrix[ROWS][COLUMS], int clear) {
  int i;
  for(i = 0; i < ENEMY_NUMBER; i++) {
    drawCar(enemies[i], matrix, clear ? PIXEL : PIXEL_SOLID, clear ? COLOR_GRAY : enemies[i].color);
  }
}

void initPista(gamePixel matrix[ROWS][COLUMS]) {
  gamePixel bordaOut = { PIXEL, COLOR_GREEN };
  gamePixel bottom = { PIXEL2, COLOR_YELLOW };
  int i, j;

  for (i = 0; i < ROWS; i++) {
    matrix[i][0] = bordaOut;
    matrix[i][COLUMS - 1] = bordaOut;
    for (j = 0; j < COLUMS; j++) {
      matrix[ROWS - 1][j] = bottom;
    }
  }
}

void clearPista(gamePixel matrix[ROWS][COLUMS]) {
  int i;
  for (i = 0; i < ROWS - 1; i++) {
    matrix[i][1].simbolo = EMPTY_PIXEL;
    matrix[i][1].color = COLOR_BLACK;
    matrix[i][COLUMS - 2].simbolo = EMPTY_PIXEL;
    matrix[i][COLUMS - 2].color = COLOR_BLACK;
    matrix[i][COLUMS / 2].simbolo = PIXEL;
    matrix[i][COLUMS / 2].color = COLOR_GRAY;
  }
}

void drawPista(gamePixel matrix[ROWS][COLUMS]) {
  gamePixel bordain;
  gamePixel center = { PIXEL, COLOR_LIGHT_YELLOW };
  int i, j;

  bordain.simbolo = PIXEL_SOLID;

  if (matrix[0][1].color != COLOR_WHITE) {
    clearPista(matrix);
    for (i = 0; i < ROWS - 1; i++) {
      if (i % 2 != 0) {
        bordain.color = COLOR_RED;
      } else {
        matrix[i][COLUMS / 2] = center;
        bordain.color = COLOR_WHITE;
      }
      matrix[i][1] = bordain;
      matrix[i][COLUMS - 2] = bordain;
    }
  } else {
    clearPista(matrix);
    for (i = 0; i < ROWS - 1; i++) {
      if (i % 2 == 0) {
        bordain.color = COLOR_RED;
      } else {
        matrix[i][COLUMS / 2] = center;
        bordain.color = COLOR_WHITE;
      }
      matrix[i][1] = bordain;
      matrix[i][COLUMS - 2] = bordain;
    }
  }
}

void askPlayerName(gamer *player) {
  system("cls");
  printf("Digite seu nome: ");
  scanf("%[a-z A-Z]", player->name);
}

int gameOverScreen(gamer player) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  int selectedOption = 1;
  int i;
  int lineWidth = 85;

  system("cls");
  while(1) {
    gotoxy(0,0);

    printf("\n\n\n\n\t");
    SetConsoleTextAttribute(out, COLOR_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("\xDB");
    }
    SetConsoleTextAttribute(out, COLOR_RED);
    printf("\n\n\t\t\t\t\t\tGAME OVER\n");
    SetConsoleTextAttribute(out, COLOR_GREEN);
    printf("\n\t\t\t\t\t%s -- %d pontos\n", player.name, player.score);
    printf("\t");
    SetConsoleTextAttribute(out, COLOR_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("_");
    }
    SetConsoleTextAttribute(out, COLOR_GREEN);
    printf("\n\n\t\t\t\t        Deseja tentar novamente?\n");
    SetConsoleTextAttribute(out, selectedOption == 1 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t\t    SIM    ");
    SetConsoleTextAttribute(out, selectedOption == 2 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t\t    NAO    ");

    printf("\n\t");
    SetConsoleTextAttribute(out, FOREGROUND_RED);
    for (i = 0; i < lineWidth; i++) {
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
    SetConsoleTextAttribute(out, FOREGROUND_GREEN);
    printf("\n\n\t");
    SetConsoleTextAttribute(out, FOREGROUND_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("\xDB");
    }
  }
}

int gameMenu() {
  int selectedOption = 1;
  int i;
  int lineWidth = 85;
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  while(1) {
    gotoxy(0,0);

    printf("\n\n\n\n\t");
    SetConsoleTextAttribute(out, COLOR_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("\xDB");
    }
    SetConsoleTextAttribute(out, COLOR_BLUE);
    printf("\n\t\t\t\t\t     Car Racing\n");
    printf("\t");
    SetConsoleTextAttribute(out, COLOR_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("_");
    }
    SetConsoleTextAttribute(out, COLOR_GREEN);
    printf("\n\n\t\t\t\t        Selecione uma opcao\n");
    SetConsoleTextAttribute(out, selectedOption == 1 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t 1 - Novo Jogo    ");
    SetConsoleTextAttribute(out, selectedOption == 2 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t 2 - High Scores  ");
    SetConsoleTextAttribute(out, selectedOption == 3 ? BACKGROUND_RED : 1);
    printf("\n\t\t\t\t\t 3 - Sair         \n");

    printf("\n\t");
    SetConsoleTextAttribute(out, FOREGROUND_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("_");
    }
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
        case KEY_SPACE_BAR:
        case KEY_RETURN:
          return selectedOption;
      }
    }
    SetConsoleTextAttribute(out, FOREGROUND_GREEN);
    printf("\n\n\t");
    SetConsoleTextAttribute(out, FOREGROUND_RED);
    for (i = 0; i < lineWidth; i++) {
      printf("\xDB");
    }
  }
}