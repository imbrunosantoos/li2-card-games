#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "deck.h"
#include "pile.h"

// Esta estrutura guarda o estado atual de uma partida
typedef struct {
    Deck deck;          // O baralho de onde saem as cartas
    Pile columns[10];   // As 10 colunas de cartas que vemos na mesa
} SimonState;

// Define o que cada parte do código faz:

// 1. Cria o jogo, baralha e distribui as cartas pelas colunas
void simonInit(SimonState *s);

// 2. Tenta mover uma única carta de uma coluna para outra
int simonMove(SimonState *s, int topCol, int destCol);

// 3. Tenta mover um bloco de várias cartas em sequência de uma vez
int simonMoveSequence(SimonState *s, int topCol, int destCol, int numCards);

// 4. Verifica se o jogador já limpou a mesa toda e ganhou o jogo
int simonIsOver(SimonState *s);

// 5. Procura sequências completas (Rei a Ás) para as apagar da mesa
void simonUpdate(SimonState *s);

#endif