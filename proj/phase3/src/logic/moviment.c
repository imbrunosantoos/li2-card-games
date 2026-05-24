#include "moviment.h"
#include <string.h>

// verifica se uma flag existe nas regras do movimento
static int temFlag(char *flags, char flag) {
    int i = 0;
    while (flags[i] != '\0') {
        if (flags[i] == flag) return 1;
        i++;
    }
    return 0;
}

// verifica se as cartas a mover estao em sequencia valida
static int sequenciaValida(PilhaJogo *p, int quantidade, char *flags) {
    int total = p->cartas.size;
    int i;

    if (quantidade == 1) return 1;  // 1 carta e sempre valida

    for (i = 0; i < quantidade - 1; i++) {
        Card baixo = p->cartas.cards[total - quantidade + i];
        Card cima  = p->cartas.cards[total - quantidade + i + 1];

        // flag [ = decrescente consecutivo
        if (temFlag(flags, '[') && baixo.value != cima.value + 1) return 0;
        // flag m = mesmo naipe
        if (temFlag(flags, 'm') && baixo.suit != cima.suit) return 0;
    }
    return 1;
}

// devolve a cor da carta (0=preto, 1=vermelho)
static int corCarta(Card c) {
    if (c.suit == CLUBS || c.suit == SPADES) return 0;
    return 1;
}


// verifica se a carta pode ir para o destino
static int podeIrParaDestino(Card carta, PilhaJogo *destino, char *flags) {
    // flag V = destino tem que estar vazio
    if (temFlag(flags, 'V')) return destino->cartas.size == 0;

    // destino vazio sem flag V = pode sempre
    if (destino->cartas.size == 0) return 1;

    Card topo = pileTop(&destino->cartas);

    // flag ~ = valor +1 ou -1
    if (temFlag(flags, '~')) {
        int diff = carta.value - topo.value;
        if (diff != 1 && diff != -1) return 0;
    }

    // flag < = valor imediatamente inferior
    if (temFlag(flags, '<') && carta.value != topo.value - 1) return 0;

    // flag > = valor imediatamente superior
    if (temFlag(flags, '>') && carta.value != topo.value + 1) return 0;

    // flag D = cor diferente do destino
    if (temFlag(flags, 'D') && corCarta(carta) == corCarta(topo)) return 0;

    // flag M = mesmo naipe do destino
    if (temFlag(flags, 'M') && carta.suit != topo.suit) return 0;

    // flag a = carta a mover deve ser As
    if (temFlag(flags, 'a') && carta.value != 1) return 0;

    return 1;
}

// procura uma regra MOV para estes tipos de pilha
static RegraMovimento *procurarRegra(Jogo *j, char *tipoOrigem, char *tipoDestino, int quantidade) {
    int i;
    for (i = 0; i < j->regras.numMovimentos; i++) {
        RegraMovimento *r = &j->regras.movimentos[i];
        if (r->automatico == 1) continue;
        if (strcmp(r->origem, tipoOrigem) != 0) continue;
        if (strcmp(r->destino, tipoDestino) != 0) continue;
        if (quantidade > 1 && !temFlag(r->flags, '+')) continue;
        return r;
    }
    return NULL;
}

// move as cartas fisicamente de uma pilha para outra
static void moverCartas(PilhaJogo *origem, PilhaJogo *destino, int quantidade) {
    int total = origem->cartas.size;
    int i;
    Card lixo;

    for (i = 0; i < quantidade; i++) {
        Card c = origem->cartas.cards[total - quantidade + i];
        pilePush(&destino->cartas, c);
    }
    for (i = 0; i < quantidade; i++) {
        pilePop(&origem->cartas, &lixo);
    }
}

// tenta mover cartas de uma pilha para outra
int tentarMover(Jogo *j, int origem, int destino, int quantidade) {
    if (origem < 0 || origem >= j->numPilhas) return 0;
    if (destino < 0 || destino >= j->numPilhas) return 0;

    PilhaJogo *pOrigem  = &j->pilhas[origem];
    PilhaJogo *pDestino = &j->pilhas[destino];

    if (pOrigem->cartas.size == 0) return 0;
    if (quantidade > pOrigem->cartas.size) return 0;

    RegraMovimento *regra = procurarRegra(j, pOrigem->tipo, pDestino->tipo, quantidade);
    if (regra == NULL) return 0;

    // flag * = pode sempre mover
    if (temFlag(regra->flags, '*')) {
        moverCartas(pOrigem, pDestino, quantidade);
        return 1;
    }

    // valida sequencia e destino
    if (sequenciaValida(pOrigem, quantidade, regra->flags) == 0) return 0;

    Card cartaMover = pOrigem->cartas.cards[pOrigem->cartas.size - quantidade];
    if (podeIrParaDestino(cartaMover, pDestino, regra->flags) == 0) return 0;

    moverCartas(pOrigem, pDestino, quantidade);
    return 1;
}

// executa movimentos automaticos em cadeia
void executarAutomaticos(Jogo *j) {
    int i, o, d;
    int houveMovimento = 1;

    while (houveMovimento) {
        houveMovimento = 0;
        for (i = 0; i < j->regras.numMovimentos; i++) {
            RegraMovimento *r = &j->regras.movimentos[i];
            if (r->automatico == 0) continue;

            for (o = 0; o < j->numPilhas; o++) {
                if (strcmp(j->pilhas[o].tipo, r->origem) != 0) continue;
                for (d = 0; d < j->numPilhas; d++) {
                    if (strcmp(j->pilhas[d].tipo, r->destino) != 0) continue;
                    if (tentarMover(j, o, d, j->pilhas[o].cartas.size)) {
                        houveMovimento = 1;
                    }
                }
            }
        }
    }
}