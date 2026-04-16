#include "game.h"

// Coloca uma carta no topo do monte de descarte antes de adicionar, verifica se o monte ainda tem espaço
static int discardPush (DiscardPile *d, Card c) {
    if (d->size >= DISCARD_MAX)              // Verifica se o descarte já está cheio
    return 0;                                // Se estuiver cheio sai da função devolve 0  
    d->cards [d->size] = c;                  // Coloca a carta nova na primeira posição livre 
    d->size++;                               // Aumenta o contador de cartas em 1
    return 1;                                // Carta é adicionada 
}

// Vai buscar a carta do topo do descarte sem a remover
static int discardTop (DiscardPile *d, Card *out) {
    if (d->size == 0)                   // Verifica se o monte de descarte está vazio
        return 0;                       // Se estiver cheio sai da funcao e devolve 0
    *out = d->cards [d->size -1];       // Vai a ultima posicao e copia a carta para out
    return 1;                           // devolve 1 que é para indicar a carta 
}

// Distribui 5 cartas por cada um dos 7 montes 
static void dealCards (GameState *g) {
    int i;     // Numero do monte que esta a ser preechido, vai de 0 a 6
    int j;     // Quantas cartas ja foram colocadas no monte, vai de 0 a 4
    Card c;    // Carta temporaria que guarda a carta retirada do baralho 

    for (i=0; i< NUM_PILES; i++) {              // Passa pelos 7 montes um a um
        for (j=0; j < PILE_MAX; j++) {          // Passa pelas 5 cartas uma a uma
            if (deckDraw (&g->deck, &c))        // Tira a primeira carta do baralho
                pilePush (&g->tableu [i], c);   // Coloca essa carta na mesa 
        }
    }
}

// Coloca a primeira carta do baralho no descarte
static void initDiscard (GameState *g) {
    Card c;
    g->discard.size = 0;                // O monte de descrate começa vazio 
    if (deckDraw (&g->deck, &c))        // Tira a primeira carta do baralho 
        discardPush (&g->discard, c);   // Coloca essa carta no descarte para ficar visivel
}

// Prepara o jogo para começar
void gameInit(GameState *g) {
    int i;
    deckInit(&g->deck);             // Cria o baralho com as 52 cartas todas            
    deckShuffle(&g->deck);          // Baralha as cartas para ficarem em ordem aleatória 
    for (i = 0; i < NUM_PILES; i++) // Passa pelos 7 montes um a um                     
        pileInit(&g->tableu[i]);    // Inicializa cada monte para ficar vazio            
    dealCards(g);                   // Distribui 5 cartas por cada um dos 7 montes      
    initDiscard(g);                 // Coloca 1 carta visível no monte de descarte       
}

// Verifica se o jogo acabou — só acaba quando os 7 montes estão vazios 
int gameIsOver(GameState *g) {
    int i;
    for (i = 0; i < NUM_PILES; i++)           // Passa pelos 7 montes um a um              
        if (!pileIsEmpty(&g->tableu[i]))     // Se encontrar um monte que ainda tem cartas 
            return 0;                         // O jogo ainda não acabou, devolve 0         
    return 1;                                 // Se chegou aqui todos os montes estão vazios 
}

// Verifica se uma carta pode ser jogada no descarte 
int gameCanDiscard(GameState *g, Card card) {
    Card top;
    if (!discardTop(&g->discard, &top)) // Tenta ir buscar a carta do topo do descarte     
        return 0;                       // Se o descarte estiver vazio não é possível jogar 
    return cardIsPlayable(card, top);     // Verifica se a carta a jogar é seguida da do topo 
}

// Move a carta do topo de um monte para o descarte 
int gameMoveToDiscard(GameState *g, int pile) {
    Card c;
    if (!isValidPile(pile))              return 0; // Se o número do monte não existe sai        
    if (pileIsEmpty(&g->tableu[pile]))  return 0; // Se o monte estiver vazio não há carta      
    c = pileTop(&g->tableu[pile]);      // Vai buscar a carta do topo do monte        
    if (!gameCanDiscard(g, c))           return 0; // Verifica se a carta pode ir para o descarte 
    pilePop(&g->tableu[pile], &c);                // Remove a carta do topo do monte            
    discardPush(&g->discard, c);                   // Coloca essa carta no topo do descarte      
    return 1;                                      // Devolve 1 para dizer que a jogada foi feita 
}

// Tira uma carta do baralho e coloca-a no descarte 
int gameDrawcard(GameState *g) {
    Card c;
    if (!deckDraw(&g->deck, &c)) // Verifica se o baralho ainda tem cartas          
        return 0;                // Se o baralho estiver vazio sai e devolve 0      
    discardPush(&g->discard, c); // Coloca a carta retirada no topo do descarte     
    return 1;                    // Devolve 1 para dizer que a carta foi retirada   
}

// Devolve a carta do topo do descarte sem a remover 
int gameDiscardTop(GameState *g, Card *out) {
    return discardTop(&g->discard, out); // Chama a função auxiliar e devolve o resultado 
}

// Verifica se o número do monte está entre 0 e 6 
int isValidPile(int pile) {
    return pile >= 0 && pile < NUM_PILES; // Devolve 1 se está entre 0 e 6, 0 se não está 
}