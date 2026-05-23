#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#include "engine.h"

// tenta mover cartas de uma pilha para outra
// devolve 1 se conseguiu, 0 se nao pode
int tentarMover(Jogo *j, int origem, int destino, int quantidade);

// executa os movimentos automaticos depois de cada jogada
void executarAutomaticos(Jogo *j);

#endif