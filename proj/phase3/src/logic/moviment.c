#include "moviment.h"
#include <string.h>

/* verifica se uma flag existe nas regras do movimento */
static int temFlag(char *flags, char flag) {
    int i = 0;
    while (flags[i] != '\0') {
        if (flags[i] == flag) return 1;
        i++;
    }
    return 0;
}

/* devolve a cor da carta (0=preto, 1=vermelho) */
static int corCarta(Card c) {
    if (c.suit == CLUBS || c.suit == SPADES) return 0;
    return 1;
}

/* valida o par de valores entre duas cartas consecutivas */
static int parValorValido(Card baixo, Card cima, char *flags) {
    if (temFlag(flags, '[') && baixo.value != cima.value + 1) return 0;
    if (temFlag(flags, ']') && baixo.value != cima.value - 1) return 0;
    return 1;
}

/* valida o par de naipes/cores entre duas cartas consecutivas */
static int parNaipeCorValido(Card baixo, Card cima, char *flags) {
    if (temFlag(flags, 'm') && baixo.suit != cima.suit) return 0;
    if (temFlag(flags, 'x') && baixo.suit == cima.suit) return 0;
    if (temFlag(flags, 'c') && corCarta(baixo) != corCarta(cima)) return 0;
    if (temFlag(flags, 'd') && corCarta(baixo) == corCarta(cima)) return 0;
    return 1;
}

/* verifica se as cartas a mover estao em sequencia valida */
static int sequenciaValida(PilhaJogo *p, int quantidade, char *flags) {
    int total = p->cartas.size;
    int i;

    if (quantidade == 1) return 1;

    for (i = 0; i < quantidade - 1; i++) {
        Card baixo = p->cartas.cards[total - quantidade + i];
        Card cima  = p->cartas.cards[total - quantidade + i + 1];
        if (!parValorValido(baixo, cima, flags)) return 0;
        if (!parNaipeCorValido(baixo, cima, flags)) return 0;
    }
    return 1;
}

/* verifica se a carta e valida independentemente do destino */
static int cartaEspecialValida(Card carta, char *flags) {
    if (temFlag(flags, 'a') && carta.value != 1) return 0;
    if (temFlag(flags, 'k') && carta.value != 13) return 0;
    return 1;
}

/* verifica o valor da carta em relacao ao topo do destino */
static int valorValido(Card carta, Card topo, char *flags) {
    if (temFlag(flags, '~')) {
        int diff = carta.value - topo.value;
        if (diff != 1 && diff != -1) return 0;
    }
    if (temFlag(flags, '<') && carta.value != topo.value - 1) return 0;
    if (temFlag(flags, '>') && carta.value != topo.value + 1) return 0;
    return 1;
}

/* verifica o naipe e cor da carta em relacao ao topo do destino */
static int naipeCorValido(Card carta, Card topo, char *flags) {
    if (temFlag(flags, 'D') && corCarta(carta) == corCarta(topo)) return 0;
    if (temFlag(flags, 'M') && carta.suit != topo.suit) return 0;
    if (temFlag(flags, 'X') && carta.suit == topo.suit) return 0;
    if (temFlag(flags, 'C') && corCarta(carta) != corCarta(topo)) return 0;
    return 1;
}

/* verifica se a carta pode ir para o destino */
static int podeIrParaDestino(Card carta, PilhaJogo *destino, char *flags) {
    if (temFlag(flags, 'V') && destino->cartas.size != 0) return 0;
    if (destino->cartas.size == 0) return 1;
    Card topo = pileTop(&destino->cartas);
    if (!valorValido(carta, topo, flags)) return 0;
    if (!naipeCorValido(carta, topo, flags)) return 0;
    return 1;
}

/* verifica se uma regra manual se aplica a estes tipos e quantidade */
static int regraAplica(RegraMovimento *r, char *tipoOrigem, char *tipoDestino, int quantidade) {
    if (r->automatico == 1) return 0;
    if (strcmp(r->origem, tipoOrigem) != 0) return 0;
    if (strcmp(r->destino, tipoDestino) != 0) return 0;
    if (quantidade > 1 && !temFlag(r->flags, '+')) return 0;
    return 1;
}

/* procura uma regra MOV para estes tipos de pilha */
static RegraMovimento *procurarRegra(Jogo *j, char *tipoOrigem, char *tipoDestino, int quantidade) {
    int i;
    for (i = 0; i < j->regras.numMovimentos; i++) {
        if (regraAplica(&j->regras.movimentos[i], tipoOrigem, tipoDestino, quantidade))
            return &j->regras.movimentos[i];
    }
    return NULL;
}

/* move as cartas fisicamente de uma pilha para outra */
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

/* valida todas as condicoes e executa o movimento */
static int validarEExecutar(PilhaJogo *pOrigem, PilhaJogo *pDestino,
                             RegraMovimento *regra, int quantidade) {
    Card cartaBase = pOrigem->cartas.cards[pOrigem->cartas.size - quantidade]; /* fundo da sequencia */
    Card cartaTopo = pOrigem->cartas.cards[pOrigem->cartas.size - 1];          /* topo da sequencia */
    if (temFlag(regra->flags, 'A') && cartaBase.value != 1) return 0;   /* A = base e As */
    if (temFlag(regra->flags, 'K') && cartaBase.value != 13) return 0;  /* K = base e Rei */
    if (!cartaEspecialValida(cartaTopo, regra->flags)) return 0;         /* a/k = topo e As/Rei */
    if (!sequenciaValida(pOrigem, quantidade, regra->flags)) return 0;
    if (!podeIrParaDestino(cartaBase, pDestino, regra->flags)) return 0;
    moverCartas(pOrigem, pDestino, quantidade);
    return 1;
}

/* tenta mover cartas de uma pilha para outra */
int tentarMover(Jogo *j, int origem, int destino, int quantidade) {
    if (origem < 0 || origem >= j->numPilhas) return 0;
    if (destino < 0 || destino >= j->numPilhas) return 0;

    PilhaJogo *pOrigem  = &j->pilhas[origem];
    PilhaJogo *pDestino = &j->pilhas[destino];

    if (pOrigem->cartas.size == 0) return 0;
    if (quantidade > pOrigem->cartas.size) return 0;

    RegraMovimento *regra = procurarRegra(j, pOrigem->tipo, pDestino->tipo, quantidade);
    if (regra == NULL) return 0;

    if (temFlag(regra->flags, '*')) {
        moverCartas(pOrigem, pDestino, quantidade);
        return 1;
    }

    return validarEExecutar(pOrigem, pDestino, regra, quantidade);
}

/* tenta mover para todos os destinos do tipo correto */
static int tentarMoverParaDestinos(Jogo *j, RegraMovimento *r, int o) {
    int d, moveu = 0;
    for (d = 0; d < j->numPilhas; d++) {
        if (strcmp(j->pilhas[d].tipo, r->destino) == 0) {
            if (tentarMover(j, o, d, j->pilhas[o].cartas.size))
                moveu = 1;
        }
    }
    return moveu;
}

/* aplica uma regra AUTO a todos os pares origem/destino */
static int aplicarRegraAuto(Jogo *j, RegraMovimento *r) {
    int o, moveu = 0;
    for (o = 0; o < j->numPilhas; o++) {
        if (strcmp(j->pilhas[o].tipo, r->origem) == 0) {
            if (tentarMoverParaDestinos(j, r, o))
                moveu = 1;
        }
    }
    return moveu;
}

/* executa movimentos automaticos em cadeia */
void executarAutomaticos(Jogo *j) {
    int i;
    int houveMovimento = 1;
    while (houveMovimento) {
        houveMovimento = 0;
        for (i = 0; i < j->regras.numMovimentos; i++) {
            if (j->regras.movimentos[i].automatico == 1) {
                if (aplicarRegraAuto(j, &j->regras.movimentos[i]))
                    houveMovimento = 1;
            }
        }
    }
}
