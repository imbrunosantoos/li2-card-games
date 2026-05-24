#include "saveload.h"
#include <stdio.h>

/* guarda o estado do jogo em ficheiro */
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

/* carrega uma pilha do ficheiro */
static void carregarPilha(FILE *f, PilhaJogo *pilha) {
    int j, size, valor, naipe;
    pileInit(&pilha->cartas);
    fscanf(f, "%d", &size);
    for (j = 0; j < size; j++) {
        fscanf(f, "%d %d", &valor, &naipe);
        Card c = createCard(valor, (Suit)naipe);
        pilePush(&pilha->cartas, c);
    }
}

/* carrega um jogo guardado a partir de ficheiro */
void loadGame(PilhaJogo pilhas[], int numPilhas, char *ficheiro) {
    int i;
    char nomePaciencia[50];
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL) {
        printf("Erro ao carregar jogo!\n");
        return;
    }
    fscanf(f, "%49s", nomePaciencia);
    fscanf(f, "%*d");
    for (i = 0; i < numPilhas; i++)
        carregarPilha(f, &pilhas[i]);
    fclose(f);
    printf("Jogo carregado!\n");
}
