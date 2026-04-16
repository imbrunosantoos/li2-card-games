#include "display.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

// Símbolos UTF-8 para cada naipe, a posição corresponde ao valor do enum
static const char *suitSymbol[] = {
    "♣", // CLUBS    = 0
    "♦", // DIAMONDS = 1
    "♥", // HEARTS   = 2
    "♠"  // SPADES   = 3
};

// Letras para os valores especiais, a posição corresponde ao valor do enum
static const char *valueStr[] = {
    "?",  // 0 — não usado
    "A",  // 1
    "2","3","4","5","6","7","8","9","10",
    "J",  // 11
    "Q",  // 12
    "K"   // 13
};

// Imprime uma carta formatada ex: [3♣] ou [7♦]
static void printCard(Card c) {
    if (c.value == 10)
        printf("|%s%s|", valueStr[c.value], suitSymbol[c.suit]);
    else
        printf("| %s%s|", valueStr[c.value], suitSymbol[c.suit]);
}

// Mostra o tabuleiro completo, com o descarte, o baralho e os 7 montes
void displayBoard (GameState *g) {
    int linha = 0;
    int col;
    Card c;
    printf("\n--- GOLF SOLITAIRE ---\n");
    printf("Descarte: ");
    if (gameDiscardTop(g, &c)) {
        printCard(c);
    } else {
        printf("[  ]");
    }
    printf("  |  Stock: %d\n\n", 52 - g->deck.top);
    printf("  1      2      3      4      5      6      7\n");
    printf("-----------------------------------------------\n");
    while (linha < 5) {
        col = 0;
        while (col < 7) {
            if (linha < g->tableu[col].size) {
                printCard(g->tableu[col].cards[linha]);
                printf("  ");
            } else {
                printf("       "); 
            }
            col++;
        }
        printf("\n");
        linha++;
    }
}

void displayHelp(void) {
    printf("\nComandos: (1-7) Escolher Pilha | (d) Biscar | (q) Sair\n");
}

void displayWin(void) {
    printf("\n  PARABENS! Ganhaste o jogo!  \n");
}

void displayInvalidMove(void) {
    printf("\n Jogada invalida!\n");
}