#ifndef PILE_H
#define PILE_H

#include "card.h"

// mudo para 52 para servir as duas fases do projeto
#define PILE_MAX 52

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

//funcoes adicionadas para a fase 2 

// Devolve quantas cartas do topo formam uma sequencia valida
int pileSequenceSize(Pile *p);

// Move n cartas do topo de src para dst
int pileMoveSequence(Pile *src, Pile *dst, int n);

#endif