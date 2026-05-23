#include "engine.h"
#include <string.h>

// cria as pilhas e distribui as cartas
void criarJogo(Jogo *j, Paciencia *p) {
    Deck baralho;
    Card carta;
    int i, k;

    j->regras = *p;        // guarda as regras
    j->numPilhas = 0;

    // prepara o baralho
    deckInit(&baralho);
    deckShuffle(&baralho);

    // para cada comando INIT, cria uma pilha
    for (i = 0; i < p->numPilhas; i++) {
        PilhaJogo pj;
        pileInit(&pj.cartas);
        strcpy(pj.tipo, p->pilhas[i].tipo);   // guarda o tipo (TAB, STOCK...)

        // distribui as cartas que esta pilha deve ter
        for (k = 0; k < p->pilhas[i].numCartas; k++) {
            if (deckDraw(&baralho, &carta) == 1) {
                pilePush(&pj.cartas, carta);
            }
        }

        j->pilhas[j->numPilhas] = pj;
        j->numPilhas++;
    }
}

// verifica se o jogador ganhou (todas as condicoes WIN cumpridas)
int jogoGanho(Jogo *j) {
    int i, p;

    // verifica cada condicao de vitoria
    for (i = 0; i < j->regras.numVitorias; i++) {
        char *tipoVitoria = j->regras.vitorias[i].tipo;
        int cartasNecessarias = j->regras.vitorias[i].numCartas;

        // verifica todas as pilhas desse tipo
        for (p = 0; p < j->numPilhas; p++) {
            if (strcmp(j->pilhas[p].tipo, tipoVitoria) == 0) {
                // se a pilha nao tem o numero certo de cartas, nao ganhou
                if (j->pilhas[p].cartas.size != cartasNecessarias) {
                    return 0;
                }
            }
        }
    }

    return 1;  // todas as condicoes cumpridas
}