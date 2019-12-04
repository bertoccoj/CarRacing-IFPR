#include "carracing.h"

// lê o arquivo de high scores e grava no array recebido como parametro
void readHighScoresFile(highScore destination[5]) {
    int i;
    FILE *arquivo = fopen("highscores.bin", "rb");
    if (arquivo != NULL) {
        for (i = 0; i < 5; i++) {
            fread(&destination[i], sizeof(highScore), 1, arquivo);
            if(feof(arquivo)) { break; }
        }
    }
    fclose(arquivo);
}

// encontra e retorna a quantidade de registros que estão no arquivo
int getHighScoreCount() {
    int i = 0;
    highScore scores[5];

    FILE *arquivo = fopen("highscores.bin", "rb");
    if (arquivo != NULL) {
        for (i = 0; i < 5; i++) {
            fread(&scores[i], sizeof(highScore), 1, arquivo);
            if(feof(arquivo)) { break; }
        }
    } else {
        return 0;
    }
    fclose(arquivo);
    return i;
}

// faz a ordenação das pontuações em ordem decrescente
void sortHighScores(highScore scores[6], int registros) {
    int i,j;
    highScore temp;
    for (i = 0; i < registros; i++) {
        for (j = 0; j < registros; j++) {
            if (scores[i].score > scores[j].score) {
                temp = scores[j];
                scores[j] = scores[i];
                scores[i] = temp;
            }
        }
    }
}

// salva o score do jogador dentro do arquivo binario na posição adequada caso ele tenha 
// alcançado algum dos high scores
void saveScore(gamer jogador) {
    // score do player atual
    highScore score;
    score.score = jogador.score;
    strcpy(score.playerName, jogador.name);

    // lêndo registros no arquivo e criando um array com uma posição à mais
    int registros = getHighScoreCount();
    highScore scores[registros + 1];

    // lendo o arquivo e colocando o score do jogador em último no array
    readHighScoresFile(scores);
    scores[registros] = score;

    // ordena o array, se o player tiver ultrapassado alguma pontuação, será colocado 
    // na pocição referente
    sortHighScores(scores, registros > 0 ? registros + 1 :  1);

    FILE *arquivo = fopen("highscores.bin", "wb");

    if (arquivo != NULL) {
        fwrite(&scores, sizeof(highScore), registros > 0 ? registros + 1 :  1, arquivo);
    }
    fclose(arquivo);
}
