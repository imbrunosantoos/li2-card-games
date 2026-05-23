#include "display.h"
#include <stdio.h>

// simbolos dos naipes
static const char *naipes[] = { "♣", "♦", "♥", "♠" };

// letras dos valores
static const char *valores[] = {
    "?", "A", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "J", "Q", "K"
};

// imprime uma carta formatada
static void imprimirCarta(Card c) {
    if (c.value == 10)
        printf("|%s%s|", valores[c.value], naipes[c.suit]);
    else
        printf("| %s%s|", valores[c.value], naipes[c.suit]);
}

// mostra o tabuleiro do jogo em colunas
void mostrarJogo(Jogo *j) {
    int i, linha, maxLinhas;

    printf("\n=== %s ===\n", j->regras.nome);

    // descobre o maximo de cartas numa pilha
    maxLinhas = 0;
    for (i = 0; i < j->numPilhas; i++) {
        if (j->pilhas[i].cartas.size > maxLinhas) {
            maxLinhas = j->pilhas[i].cartas.size;
        }
    }
    if (maxLinhas == 0) maxLinhas = 1;

    // cabecalho so com numeros
    for (i = 0; i < j->numPilhas; i++) {
        printf("  %2d   ", i + 1);
    }
    printf("\n");

    // tipo de cada pilha
    for (i = 0; i < j->numPilhas; i++) {
        printf(" (%s)  ", j->pilhas[i].tipo);
    }
    printf("\n");

    // separador
    for (i = 0; i < j->numPilhas; i++) {
        printf("-------");
    }
    printf("\n");

    // mostra as cartas linha por linha
    for (linha = 0; linha < maxLinhas; linha++) {
        for (i = 0; i < j->numPilhas; i++) {
            if (linha < j->pilhas[i].cartas.size) {
                imprimirCarta(j->pilhas[i].cartas.cards[linha]);
                printf(" ");
            } else {
                printf("       ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// mostra os comandos disponiveis
void mostrarComandos(void) {
    printf("Comandos: <origem> <destino> [quantidade] | 'u' undo | 'q' sair\n");
}