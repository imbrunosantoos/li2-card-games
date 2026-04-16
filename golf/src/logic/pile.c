#include "pile.h"

// Inicia a pilha - começa sempre vazia
void pileInit (Pile *p) {
    p -> size = 0; // 0 cartas, ainda nao temc artas
}

// Coloca uma carta no topo da pilha
int pilePush (Pile *p, Card c) {
    if (p -> size >= PILE_MAX) return 0; // pilha cheia
    p -> cards [p -> size] = c;          // coloca na próxima posição livre
    p -> size++;                         // aumenta o tamanho
    return 1;
}

// Remove a carta do topo e guarda em *out
int pilePop (Pile *p, Card *out) {
    if (pileIsEmpty (p)) return 0; // pilha vazia -> nada para retirar
    p -> size --;                 // desce o índice do topo
    *out = p -> cards [p -> size]; // copia a carta removida para *out
    return 1;
}

// Verifica se a pilha está vazia 
int pileIsEmpty (Pile *p) {
    if (p->size == 0)
    return 1;  // esta vazia
else
    return 0;  // tem cartas
}

// Verifica o topo sem remover (verificar jogadas)
Card pileTop (Pile *p) {
    return p -> cards [p -> size - 1]; // último elemento válido
}