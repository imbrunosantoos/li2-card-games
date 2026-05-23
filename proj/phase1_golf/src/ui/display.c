#include "display.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

// Símbolos UTF-8 para cada naipe, a posição corresponde ao valor do enum
static const char *golfSuitSymbol[] = {
    "♣", // CLUBS    = 0
    "♦", // DIAMONDS = 1
    "♥", // HEARTS   = 2
    "♠"  // SPADES   = 3
};

// Letras para os valores especiais, a posição corresponde ao valor do enum
static const char *golfValueStr[] = {
    "?",  // 0 — não usado
    "A",  // 1
    "2","3","4","5","6","7","8","9","10",
    "J",  // 11
    "Q",  // 12
    "K"   // 13
};

// Imprime uma carta formatada ex: [3♣] ou [7♦]
static void golfPrintCard(Card c) {
    if (c.value == 10)
        printf("|%s%s|", golfValueStr[c.value], golfSuitSymbol[c.suit]);
    else
        printf("| %s%s|", golfValueStr[c.value], golfSuitSymbol[c.suit]);
}

// mostra cabecalho com descarte, stock e numeracao das colunas
static void golfDisplayHeader(GameState *g) {
    Card c;
    printf("\n--- GOLF SOLITAIRE ---\n");
    printf("Descarte: ");
    if (gameDiscardTop(g, &c)) {
        golfPrintCard(c);
    } else {
        printf("[  ]");
    }
    printf("  |  Stock: %d\n\n", 52 - g->deck.top);
    printf("  1      2      3      4      5      6      7\n");
    printf("-----------------------------------------------\n");
}

// mostra uma linha do tabuleiro (todas as 7 colunas)
static void golfDisplayLinha(GameState *g, int linha) {
    int col = 0;
    while (col < 7) {
        if (linha < g->tableu[col].size) {
            golfPrintCard(g->tableu[col].cards[linha]);
            printf("  ");
        } else {
            printf("       ");
        }
        col++;
    }
    printf("\n");
}

// mostra o tabuleiro completo
void golfDisplayBoard(GameState *g) {
    int linha = 0;
    golfDisplayHeader(g);
    while (linha < 5) {
        golfDisplayLinha(g, linha);
        linha++;
    }
}

void golfDisplayHelp(void) {
    printf("\nComandos: (1-7) Escolher Pilha | (d) Biscar | (q) Sair\n");
}

void golfDisplayWin(void) {
    printf("\n  PARABENS! Ganhaste o jogo!  \n");
}

void golfDisplayInvalidMove(void) {
    printf("\n Jogada invalida!\n");
}