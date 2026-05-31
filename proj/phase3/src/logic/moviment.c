#include "moviment.h"
#include <string.h>

/* ve se uma flag (uma letra) esta na lista de flags da regra */
static int temFlag(char *flags, char flag) {
    int i = 0;
    while (flags[i] != '\0') {
        if (flags[i] == flag) return 1;
        i++;
    }
    return 0;
}

/* cor da carta: 0 = preto (paus/espadas), 1 = vermelho (ouros/copas) */
static int corCarta(Card c) {
    if (c.suit == CLUBS || c.suit == SPADES) return 0;
    return 1;
}

/* verifica o valor entre duas cartas seguidas da sequencia que se move */
static int parValorValido(Card baixo, Card cima, char *flags) {
    if (temFlag(flags, '[') && baixo.value != cima.value + 1) return 0; // [ : decrescente
    if (temFlag(flags, ']') && baixo.value != cima.value - 1) return 0; // ] : crescente
    return 1;
}

/* verifica o naipe/cor entre duas cartas seguidas da sequencia que se move */
static int parNaipeValido(Card baixo, Card cima, char *flags) {
    if (temFlag(flags, 'm') && baixo.suit != cima.suit) return 0;           // m : mesmo naipe
    if (temFlag(flags, 'x') && baixo.suit == cima.suit) return 0;           // x : naipes diferentes
    if (temFlag(flags, 'c') && corCarta(baixo) != corCarta(cima)) return 0; // c : mesma cor
    if (temFlag(flags, 'd') && corCarta(baixo) == corCarta(cima)) return 0; // d : cores diferentes
    return 1;
}

/* ve se as cartas que vamos mover formam uma sequencia valida */
static int sequenciaValida(PilhaJogo *p, int quantidade, char *flags) {
    int total = p->cartas.size;
    int i;
    for (i = 0; i < quantidade - 1; i++) { // se for so 1 carta, nem entra no ciclo
        Card baixo = p->cartas.cards[total - quantidade + i];
        Card cima  = p->cartas.cards[total - quantidade + i + 1];
        if (!parValorValido(baixo, cima, flags)) return 0;
        if (!parNaipeValido(baixo, cima, flags)) return 0;
    }
    return 1;
}

/* ve se a carta de cima (topo) e a de baixo (fundo) sao As/Rei quando a regra pede */
static int cartasEspeciais(Card topo, Card fundo, char *flags) {
    if (temFlag(flags, 'a') && topo.value  != 1)  return 0; // a : carta de cima e As
    if (temFlag(flags, 'k') && topo.value  != 13) return 0; // k : carta de cima e Rei
    if (temFlag(flags, 'A') && fundo.value != 1)  return 0; // A : carta de baixo e As
    if (temFlag(flags, 'K') && fundo.value != 13) return 0; // K : carta de baixo e Rei
    return 1;
}

/* ve o valor da carta que assenta, em relacao ao topo do destino */
static int valorValido(Card carta, Card topo, char *flags) {
    if (temFlag(flags, '~') && carta.value != topo.value - 1 && carta.value != topo.value + 1) return 0; // ~ : logo acima ou logo abaixo
    if (temFlag(flags, '<') && carta.value != topo.value - 1) return 0; // < : valor logo abaixo
    if (temFlag(flags, '>') && carta.value != topo.value + 1) return 0; // > : valor logo acima
    return 1;
}

/* ve o naipe/cor da carta que assenta, em relacao ao topo do destino */
static int naipeValido(Card carta, Card topo, char *flags) {
    if (temFlag(flags, 'M') && carta.suit != topo.suit) return 0;           // M : mesmo naipe do topo
    if (temFlag(flags, 'X') && carta.suit == topo.suit) return 0;           // X : naipe diferente do topo
    if (temFlag(flags, 'C') && corCarta(carta) != corCarta(topo)) return 0; // C : mesma cor do topo
    if (temFlag(flags, 'D') && corCarta(carta) == corCarta(topo)) return 0; // D : cor diferente do topo
    return 1;
}

/* a regra precisa de comparar a carta com o topo do destino? */
static int precisaDeTopo(char *flags) {
    return temFlag(flags, '<') || temFlag(flags, '>') || temFlag(flags, '~')
        || temFlag(flags, 'M') || temFlag(flags, 'X')
        || temFlag(flags, 'C') || temFlag(flags, 'D');
}

/* ve se a carta de baixo da sequencia pode assentar no destino */
static int podeAssentar(Card carta, PilhaJogo *destino, char *flags) {
    if (temFlag(flags, 'V') && destino->cartas.size != 0) return 0; // V : destino tem de estar vazio
    if (destino->cartas.size == 0) return !precisaDeTopo(flags);    // vazio: so aceita se a regra nao comparar com o topo
    Card topo = pileTop(&destino->cartas);
    if (!valorValido(carta, topo, flags)) return 0;
    if (!naipeValido(carta, topo, flags)) return 0;
    return 1;
}

/* devolve as flags do tipo de uma pilha (= _ ^ 1) */
static char *flagsDoTipo(Jogo *j, char *tipo) {
    int t;
    for (t = 0; t < j->regras.numTipos; t++) {
        if (strcmp(j->regras.tipos[t].nome, tipo) == 0)
            return j->regras.tipos[t].flags;
    }
    return "";
}

/* flag de tipo 1: a pilha de destino so pode ficar com 1 carta */
static int destinoCabe(Jogo *j, PilhaJogo *destino, int quantidade) {
    if (temFlag(flagsDoTipo(j, destino->tipo), '1') && (quantidade != 1 || destino->cartas.size != 0))
        return 0;
    return 1;
}

/* ve se UMA regra deixa mover 'quantidade' cartas da origem para o destino (so verifica) */
static int regraPermite(PilhaJogo *origem, PilhaJogo *destino, RegraMovimento *r, int quantidade) {
    Card fundo = origem->cartas.cards[origem->cartas.size - quantidade]; // carta de baixo (assenta no destino)
    Card topo  = origem->cartas.cards[origem->cartas.size - 1];          // carta de cima
    if (temFlag(r->flags, '*')) return 1;                               // * : pode sempre
    if (!cartasEspeciais(topo, fundo, r->flags)) return 0;
    if (!sequenciaValida(origem, quantidade, r->flags)) return 0;
    if (!podeAssentar(fundo, destino, r->flags)) return 0;
    return 1;
}

/* ve se uma regra e para estes tipos de pilha e este numero de cartas */
static int regraServe(RegraMovimento *r, char *origem, char *destino, int quantidade, int automatico) {
    if (r->automatico != automatico) return 0;
    if (strcmp(r->origem, origem) != 0) return 0;
    if (strcmp(r->destino, destino) != 0) return 0;
    if (quantidade > 1 && !temFlag(r->flags, '+')) return 0; // + : pode mover varias cartas
    return 1;
}

/* tira 'quantidade' cartas do topo da origem e poe no topo do destino */
static void moverCartas(PilhaJogo *origem, PilhaJogo *destino, int quantidade) {
    int total = origem->cartas.size;
    int i;
    Card lixo;
    for (i = 0; i < quantidade; i++)
        pilePush(&destino->cartas, origem->cartas.cards[total - quantidade + i]);
    for (i = 0; i < quantidade; i++)
        pilePop(&origem->cartas, &lixo);
}

/* ve se um indice de pilha existe */
static int pilhaExiste(Jogo *j, int i) {
    return i >= 0 && i < j->numPilhas;
}

/* experimenta todas as regras: ha alguma que permita esta jogada? (disjuncao) */
static int existeRegra(Jogo *j, PilhaJogo *o, PilhaJogo *d, int quantidade) {
    int i;
    for (i = 0; i < j->regras.numMovimentos; i++) {
        RegraMovimento *r = &j->regras.movimentos[i];
        if (regraServe(r, o->tipo, d->tipo, quantidade, 0) && regraPermite(o, d, r, quantidade))
            return 1;
    }
    return 0;
}

/* tenta mover cartas de uma pilha para outra (jogada do utilizador) */
int tentarMover(Jogo *j, int origem, int destino, int quantidade) {
    if (!pilhaExiste(j, origem) || !pilhaExiste(j, destino)) return 0;
    PilhaJogo *o = &j->pilhas[origem];
    PilhaJogo *d = &j->pilhas[destino];
    if (quantidade < 1 || quantidade > o->cartas.size) return 0;
    if (!destinoCabe(j, d, quantidade)) return 0;
    if (!existeRegra(j, o, d, quantidade)) return 0;
    moverCartas(o, d, quantidade);
    return 1;
}

/* tenta um movimento automatico de uma pilha para outra (da pilha toda ate 1 carta) */
static int tentarAuto(Jogo *j, RegraMovimento *r, int origem, int destino) {
    PilhaJogo *o = &j->pilhas[origem];
    PilhaJogo *d = &j->pilhas[destino];
    int q = o->cartas.size;
    while (q >= 1) {
        if (regraServe(r, o->tipo, d->tipo, q, 1) && destinoCabe(j, d, q) && regraPermite(o, d, r, q)) {
            moverCartas(o, d, q);
            return 1;
        }
        q = q - 1;
    }
    return 0;
}

/* aplica uma regra automatica a todos os pares de pilhas */
static int aplicarAuto(Jogo *j, RegraMovimento *r) {
    int o, d, moveu = 0;
    for (o = 0; o < j->numPilhas; o++)
        for (d = 0; d < j->numPilhas; d++)
            if (tentarAuto(j, r, o, d)) moveu = 1;
    return moveu;
}

/* faz os movimentos automaticos em cadeia, ate nao haver mais nenhum */
void executarAutomaticos(Jogo *j) {
    int i, houve = 1;
    while (houve) {
        houve = 0;
        for (i = 0; i < j->regras.numMovimentos; i++)
            if (j->regras.movimentos[i].automatico == 1)
                if (aplicarAuto(j, &j->regras.movimentos[i])) houve = 1;
    }
}
