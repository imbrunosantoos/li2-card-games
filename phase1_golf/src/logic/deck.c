#include "deck.h"
#include <stdlib.h>
#include <time.h>

// Preenche o baralho com as 52 cartas por ordem
void deckInit(Deck *d) {
    int i = 0;                           // contador linear (0 a 51)
    for (int s = 0; s < 4; s++) {        // percorre os 4 naipes
        for (int v = 1; v <= 13; v++) {  // percorre os 13 valores
            d->cards[i] = createCard(v, (Suit)s); // cria a carta e guarda
            i++;                         // avanca para a proxima posicao
        }
    }
    d->top = 0; // a proxima carta a tirar e a primeira
}

// baralha as cartas aleatoriamente
void deckShuffle(Deck *d) {
    srand(time(NULL)); // garante que e diferente a cada jogo
    for (int i = 0; i < DECK_SIZE; i++) {  // percorre cada carta
        int j = rand() % DECK_SIZE;        // escolhe posicao aleatoria
        Card tmp    = d->cards[i];  // guarda a carta i num temporario
        d->cards[i] = d->cards[j];  // mete a carta j no lugar de i
        d->cards[j] = tmp;          // mete o temporario no lugar de j
    }
}

// tira a carta do topo e guarda em out
int deckDraw(Deck *d, Card *out) {
    if (deckIsEmpty(d)) return 0;    // se vazio nao ha carta para tirar
    *out = d->cards[d->top];         // guarda a carta no out
    d->top++;                        // avanca para a proxima carta
    return 1;                        // sucesso
}

// verifica se o baralho esta vazio
int deckIsEmpty(Deck *d) {
    if (d->top >= DECK_SIZE) return 1; // top chegou ao fim = vazio
    return 0;                          // ainda tem cartas
}