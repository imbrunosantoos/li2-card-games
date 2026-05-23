#include "display.h"
#include <stdio.h>

// simbolos dos naipes
static const char *naipes[] = { "C", "D", "H", "S" };

// letras dos valores
static const char *valores[] = {
    "?", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
};

// imprime uma carta (ex: 7H, 10C)
static void imprimirCarta(Card c) {
    printf("%s%s ", valores[c.value], naipes[c.suit]);
}

// mostra o tabuleiro do jogo
void mostrarJogo(Jogo *j) {
    int i, k;

    printf("\n=== %s ===\n", j->regras.nome);

    for (i = 0; i < j->numPilhas; i++) {
        printf("%d (%s): ", i + 1, j->pilhas[i].tipo);

        if (j->pilhas[i].cartas.size == 0) {
            printf("[vazia]");
        } else {
            for (k = 0; k < j->pilhas[i].cartas.size; k++) {
                imprimirCarta(j->pilhas[i].cartas.cards[k]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// mostra os comandos disponiveis
void mostrarComandos(void) {
    printf("Comandos: <origem> <destino> [quantidade] | 'u' undo | 's' save | 'q' sair\n");
}