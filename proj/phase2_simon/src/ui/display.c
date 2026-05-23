#include "display.h"
#include <stdio.h>
#include <stdlib.h>  // para o system


// Simbolos UTF-8 para cada naipe
static const char *simonSuitSymbol[] = {
    "♣", // CLUBS = 0
    "♦", // DIAMONDS = 1
    "♥", // HEARTS = 2
    "♠"  // SPADES = 3
};

// Letras para os valores das cartas
static const char *simonValueStr[] = {
    "?",  // 0 nao usado
    "A",  // 1
    "2","3","4","5","6","7","8","9","10",
    "J",  // 11
    "Q",  // 12
    "K"   // 13
};
// limpa o terminal
void clearTerminalSimon(void) {
    system("clear");
}

// Imprime uma carta formatada ex: [3♣] ou [10♦]
static void simonPrintCard(Card c) {
    if (c.value == 10)
        printf("|%s%s|", simonValueStr[c.value], simonSuitSymbol[c.suit]);
    else
        printf("| %s%s|", simonValueStr[c.value], simonSuitSymbol[c.suit]);
}

// mostra cabecalho com nome do jogo e numeracao das colunas
static void simonDisplayHeader(void) {
    printf("\n--- SIMPLE SIMON ---\n");
    printf("  1      2      3      4      5      6      7      8      9     10\n");
    printf("-------------------------------------------------------------------\n");
}

// mostra uma linha do tabuleiro (todas as 10 colunas)
static void simonDisplayLinha(SimonState *s, int linha) {
    int col = 0;
    while (col < 10) {
        if (linha < s->columns[col].size) {
            simonPrintCard(s->columns[col].cards[linha]);
            printf("  ");
        } else {
            printf("       ");
        }
        col++;
    }
    printf("\n");
}

// mostra o tabuleiro completo
void simonDisplayBoard(SimonState *s) {
    int linha = 0;
    simonDisplayHeader();
    while (linha < 13) {
        simonDisplayLinha(s, linha);
        linha++;
    }
    printf("\n");
}

// Mostra os comandos disponiveis
void simonDisplayHelp(void) {
    printf("\nComandos: origem destino [quantidade] | 'u' para undo\n");
    printf("Exemplo: '1 4 2' (move 2 cartas da col 1 para 4) | '1 4' (move 1 carta)\n");
}

// Mostra mensagem de vitoria
void simonDisplayWin(void) {
    printf("\n  PARABENS! Ganhaste o jogo!  \n");
}

// Mostra erro de jogada invalida
void simonDisplayInvalidMove(void) {
    printf("\n Jogada invalida!\n");
}

