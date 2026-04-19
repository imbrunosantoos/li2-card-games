#include "display.h"
#include <stdio.h>

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

// Imprime uma carta formatada ex: [3♣] ou [10♦]
static void simonPrintCard(Card c) {
    if (c.value == 10)
        printf("|%s%s|", simonValueStr[c.value], simonSuitSymbol[c.suit]);
    else
        printf("| %s%s|", simonValueStr[c.value], simonSuitSymbol[c.suit]);
}

// Mostra o tabuleiro com as 10 colunas
void simonDisplayBoard(SimonState *s) {
    int linha = 0;
    int col;
    
    printf("\n--- SIMPLE SIMON ---\n");
    printf("  1      2      3      4      5      6      7      8      9     10\n");
    printf("-------------------------------------------------------------------\n");
    
    // mostra ate 13 linhas (maximo de cartas por coluna)
    while (linha < 13) {
        col = 0;
        
        // percorre as 10 colunas
        while (col < 10) {
            // verifica se ha carta nesta posicao
            if (linha < s->columns[col].size) {
                simonPrintCard(s->columns[col].cards[linha]);
                printf("  ");
            } else {
                printf("       "); // espaco vazio se nao ha carta
            }
            col++;
        }
        printf("\n");
        linha++;
    }
    printf("\n");
}

// Mostra os comandos disponiveis
void simonDisplayHelp(void) {
    printf("\nComandos: Escolhe origem (1-10); Destino (1-10); Quantidade de cartas; Undo (99)\n");
}

// Mostra mensagem de vitoria
void simonDisplayWin(void) {
    printf("\n  PARABENS! Ganhaste o jogo!  \n");
}

// Mostra erro de jogada invalida
void simonDisplayInvalidMove(void) {
    printf("\n Jogada invalida!\n");
}

// Mostra uma dica ao jogador
void displayHint(SimonState *s) {
    (void)s;  // parametro nao usado ainda
    printf("\n--- DICA ---\n");
    printf("Tenta encontrar sequencias do mesmo naipe em ordem decrescente!\n");
    printf("Exemplo: K♥, Q♥, J♥, 10♥, ..., A♥\n");
}