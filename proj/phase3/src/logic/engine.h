#ifndef ENGINE_H
#define ENGINE_H

#include "parser.h"
#include "../../../common/pile.h"
#include "../../../common/deck.h"

#define MAX_PILHAS_JOGO 20

// representa uma pilha do jogo a decorrer
typedef struct {
    Pile cartas;            // as cartas da pilha
    char tipo[MAX_NOME];    // "TAB", "STOCK", "FUND"...
} PilhaJogo;

// representa o estado de um jogo a decorrer
typedef struct {
    Paciencia regras;              // as regras lidas do ficheiro
    PilhaJogo pilhas[MAX_PILHAS_JOGO];  // as pilhas do jogo
    int numPilhas;                 // quantas pilhas existem
} Jogo;

// cria o jogo a partir das regras (distribui cartas)
void criarJogo(Jogo *j, Paciencia *p);

// verifica se o jogador ganhou
int jogoGanho(Jogo *j);

#endif