#include "saveload.h"
#include <stdio.h>

void saveGame(char *nomePaciencia, PilhaJogo pilhas[], int numPilhas, char *ficheiro) {
    int i, j;
    FILE *f = fopen(ficheiro, "w");
    if (f == NULL) {
        printf("Erro ao guardar jogo!\n");
        return;
    }

    fprintf(f, "%s\n", nomePaciencia);
    fprintf(f, "%d\n", numPilhas);

    for (i = 0; i < numPilhas; i++) {
        fprintf(f, "%d\n", pilhas[i].cartas.size);
        for (j = 0; j < pilhas[i].cartas.size; j++) {
            fprintf(f, "%d %d\n", pilhas[i].cartas.cards[j].value,
                                   pilhas[i].cartas.cards[j].suit);
        }
    }

    fclose(f);
    printf("Jogo guardado!\n");
}

void loadGame(PilhaJogo pilhas[], int numPilhas, char *ficheiro) {
    int i, j, size, valor, naipe;
    char nomePaciencia[50];
    int totalPilhas;
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL) {
        printf("Erro ao carregar jogo!\n");
        return;
    }

    fscanf(f, "%s", nomePaciencia);
    fscanf(f, "%d", &totalPilhas);

    for (i = 0; i < numPilhas; i++) {
        pileInit(&pilhas[i].cartas);
        fscanf(f, "%d", &size);
        for (j = 0; j < size; j++) {
            fscanf(f, "%d %d", &valor, &naipe);
            Card c = createCard(valor, (Suit)naipe);
            pilePush(&pilhas[i].cartas, c);
        }
    }

    fclose(f);
    printf("Jogo carregado!\n");
}