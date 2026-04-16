#ifndef DECK_H
#define DECK_H

#include "card.h"

// Um baralho completo tem sempre 52 cartas (4 naipes × 13 valores)
#define DECK_SIZE 52

// Estrutura que representa o baralho 
typedef struct {
    Card cards[DECK_SIZE]; // 52 cartas 
    int  top;              // Indice da proxima carta a tirar
                           // quando top == 52, o baralho está vazio

} Deck;

// Inicia o baralho com as 52 cartas 
void deckInit(Deck *d);

// Baralha as 52 cartas aleatoriamente 
void deckShuffle(Deck *d);

// Retira uma carta do topo do baralho 0
int deckDraw(Deck *d, Card *out);

// Devolve 1 se o baralho estiver vazio 
int deckIsEmpty(Deck *d);

#endif