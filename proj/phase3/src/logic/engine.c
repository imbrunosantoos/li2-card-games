#include "engine.h"
#include <string.h>

/* cria uma PilhaJogo a partir de um INIT e distribui as cartas */
static PilhaJogo inicializarPilha(Deck *baralho, PilhaInicial *pi) {
    PilhaJogo pj;
    Card carta;
    int k;
    pileInit(&pj.cartas);
    strcpy(pj.tipo, pi->tipo);
    for (k = 0; k < pi->numCartas; k++) {
        if (deckDraw(baralho, &carta) == 1)
            pilePush(&pj.cartas, carta);
    }
    return pj;
}

/* cria as pilhas e distribui as cartas */
void criarJogo(Jogo *j, Paciencia *p) {
    Deck baralho;
    int i;
    j->regras = *p;
    j->numPilhas = 0;
    deckInit(&baralho);
    deckShuffle(&baralho);
    for (i = 0; i < p->numPilhas; i++) {
        j->pilhas[j->numPilhas] = inicializarPilha(&baralho, &p->pilhas[i]);
        j->numPilhas++;
    }
}

/* verifica se o jogador ganhou (todas as condicoes WIN cumpridas) */
int jogoGanho(Jogo *j) {
    int i, p;

    for (i = 0; i < j->regras.numVitorias; i++) {
        char *tipoVitoria = j->regras.vitorias[i].tipo;
        int cartasNecessarias = j->regras.vitorias[i].numCartas;

        for (p = 0; p < j->numPilhas; p++) {
            if (strcmp(j->pilhas[p].tipo, tipoVitoria) == 0) {
                if (j->pilhas[p].cartas.size != cartasNecessarias) {
                    return 0;
                }
            }
        }
    }

    return 1;
}
