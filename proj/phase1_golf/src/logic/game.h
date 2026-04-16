#ifndef GAME_H
#define GAME_H 

#include "deck.h"
#include "pile.h"

#define DISCARD_MAX 52 // Máximo de cartas na pilha de descarte 
#define NUM_PILES 7 // O jogo possui 7 pilhas de cartas na mesa

// Monte de descarte
// Guarda todas as cartas que foram descartadas ao longo do jogo 
typedef struct {
    Card cards[DISCARD_MAX];    // sequencia com todas as cartas descartadas 
    int size;                   // numero de cartas no monte de descarte 
} DiscardPile;

// Estado completo do jogo
// Junta os 7 montes de cartas da mesa, o monte de descarte e o baralho
typedef struct {
    Pile        tableu[NUM_PILES];  // os 7 montes da mesa, cada um com PILE_MAX cartas 
    DiscardPile discard;           // monte de descarte
    Deck        deck;              // baralho com as cartas restantes
} GameState;

// Prepara o jogo para começar
// Baralha as cartas, distribui PILE_MAX por cada monte e coloca a primeira carta no monte de descarte 
void gameInit(GameState *g);

// Verifica se o jogo cabou 
// O jogo acaba quando todos os 7 montes da mesa ficam vazios, devolve 1 se o jogo acabou ou 0 se ainda ha cartas na mesa 
int gameIsOver (GameState *g);

// Verifica se o número do monte é valido, se não está vazio e se a carta pode ser jogada no descarte. Devolve 1 se a jogada for feita ou devolve 0 se não for possível 
int gameMoveToDiscard (GameState *g, int pile);

// Verifica se a carta pode ser jogada no monte de discarte
// So e possivel jogar se o valor da carta for acima ou abaixo da carta que esta no topo do monte de discarte. Devolve 1 se a jogada e valida ou devolve 0 se nao e permitida 
int gameCanDiscard (GameState *g, Card card);

// Tira uma carta do baralho e coloca-a no topo do monte de descarte , devolve 1 se foi possivel , 0 se o baralho nao tiver mais cartas 
// Esta jogada pode ser efetuada a qualquer momento do jogo 
int  gameDrawcard(GameState *g);

// Mostra qual e a carta que esta no topo do descarte sem a remover, devolve 1 se for possivel ou devolve 0 se o descarte estiver vazio  
int  gameDiscardTop(GameState *g, Card *out);

// Verifica se o número do monte é valido
// O numero tem de estar entre 0 e 6, devolve 1 se e valido, 0 se esta fora dos limites 
int isValidPile (int pile);

#endif  