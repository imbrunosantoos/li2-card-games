#include "saveload.h"
#include <stdio.h>

/* escreve uma pilha no ficheiro: tamanho e depois cada carta (valor naipe) */
static void guardarPilha(FILE *f, PilhaJogo *pilha) {
    int j;
    fprintf(f, "%d\n", pilha->cartas.size);
    for (j = 0; j < pilha->cartas.size; j++)
        fprintf(f, "%d %d\n", pilha->cartas.cards[j].value, pilha->cartas.cards[j].suit);
}

/* guarda o estado do jogo em ficheiro */
void saveGame(char *nomePaciencia, PilhaJogo pilhas[], int numPilhas, char *ficheiro) {
    int i;
    FILE *f = fopen(ficheiro, "w");
    if (f == NULL) {
        printf("Erro ao guardar jogo!\n");
        return;
    }
    fprintf(f, "%s\n", nomePaciencia);
    fprintf(f, "%d\n", numPilhas);
    for (i = 0; i < numPilhas; i++)
        guardarPilha(f, &pilhas[i]);
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
