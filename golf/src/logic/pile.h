#ifndef PILE_H
#define PILE_H

#include "card.h"

// Cada pilha do Golf começa com 5 cartas
#define PILE_MAX 5

typedef struct {
    Card cards [PILE_MAX]; // as cartas da pilha
    int size;             // quantas cartas existem agora ( size - 1 é sempre o índice do topo)

} Pile;
// a última carta colocada é a primeira a sair

// Inicia uma pilha vazia
void pileInit (Pile *p);

// Adiciona carta no topo
int pilePush (Pile *p, Card c);

// Remove carta do topo 
int pilePop (Pile *p, Card *out);

// Verifica se a pilha está vazia
int pileIsEmpty(Pile *p);

// Devolve a carta do topo sem a remover
Card pileTop (Pile *p);

#endif