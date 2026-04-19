#include "pile.h"

// Inicia a pilha - começa sempre vazia
void pileInit (Pile *p) {
    p -> size = 0; // 0 cartas, ainda nao tem cartas
}

// Devolve o tamanho da pilha
int pileSize(Pile *p) {
    return p->size;
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

// Devolve quantas cartas do topo formam uma sequencia valida
int pileSequenceSize(Pile *p){
    int n = 1; // a sequencia tem pelo menos uma carta valida que e a do topo
    int i = p->size - 1; // indice do topo

    while (i > 0) {
        // carta atual e a carta abaixo dela
        int mesmaNaipe = p->cards[i].suit == p->cards[i-1].suit;
        int valorSeguido = p->cards[i-1].value == p->cards[i].value + 1;

        if (mesmaNaipe && valorSeguido) {
            n++; // faz parte da sequencia
            i--;
        } else {
            return n; // sequencia terminou
        }
    }
    return n;
}

// Move n cartas de src para dst
int pileMoveSequence(Pile *src, Pile *dst, int n) {
    // calcula onde comeca a sequencia que vais mover
    int inicio = src->size - n;
    
    // copia cada uma das n cartas para dst
    while (inicio < src->size) {
        dst->cards[dst->size] = src->cards[inicio];  // copia a carta
        dst->size++;                                  // dst cresce
        inicio++;                                     // proximo carta
    }
    
    // remove as n cartas de src
    src->size = src->size - n;
    
    return 1;  // sucesso
}