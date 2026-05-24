#include "display.h"
#include <stdio.h>
#include <string.h>

// simbolos dos naipes
static const char *naipes[] = { "♣", "♦", "♥", "♠" };

// letras dos valores
static const char *valores[] = {
    "?", "A", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "J", "Q", "K"
};

// imprime uma carta formatada
static void imprimirCarta(Card c) {
    if (c.value == 10)
        printf("|%s%s|", valores[c.value], naipes[c.suit]);
    else
        printf("| %s%s|", valores[c.value], naipes[c.suit]);
}

// verifica se as cartas de uma pilha sao visiveis
static int pilhaVisivel(Jogo *j, int i) {
    int t;
    for (t = 0; t < j->regras.numTipos; t++) {
        if (strcmp(j->regras.tipos[t].nome, j->pilhas[i].tipo) == 0) {
            // flag _ = cartas invisiveis
            if (j->regras.tipos[t].flags[0] == '_') return 0;
        }
    }
    return 1;
}

// verifica se so o topo e visivel
static int soTopoVisivel(Jogo *j, int i) {
    int t;
    for (t = 0; t < j->regras.numTipos; t++) {
        if (strcmp(j->regras.tipos[t].nome, j->pilhas[i].tipo) == 0) {
            // flag ^ = so o topo e visivel
            if (j->regras.tipos[t].flags[0] == '^') return 1;
        }
    }
    return 0;
}

//funcao para mostrar o jogo ao utilizador
void mostrarJogo(Jogo *j) {
    int i, linha, maxLinhas;

    printf("\n=== %s ===\n", j->regras.nome);

    // descobre o maximo de cartas numa pilha visivel
    maxLinhas = 1;
    for (i = 0; i < j->numPilhas; i++) {
        if (pilhaVisivel(j, i) && j->pilhas[i].cartas.size > maxLinhas) {
            maxLinhas = j->pilhas[i].cartas.size;
        }
    }

    // cabecalho com numeros
    for (i = 0; i < j->numPilhas; i++) {
        printf("  %2d   ", i + 1);
    }
    printf("\n");

    // tipos das pilhas
    for (i = 0; i < j->numPilhas; i++) {
        printf("(%-5s) ", j->pilhas[i].tipo);
    }
    printf("\n");

    // separador
    for (i = 0; i < j->numPilhas; i++) {
        printf("-------");
    }
    printf("\n");

    // mostra as cartas linha por linha
    for (linha = 0; linha < maxLinhas; linha++) {
        for (i = 0; i < j->numPilhas; i++) {
            if (linha < j->pilhas[i].cartas.size) {
                if (!pilhaVisivel(j, i)) {
                    if (linha == 0) {
                    printf("[%2d##] ", j->pilhas[i].cartas.size);
                    } else {
                    printf("       ");}
                } else if (soTopoVisivel(j, i)) {
                    if (linha == j->pilhas[i].cartas.size - 1) {
                        imprimirCarta(j->pilhas[i].cartas.cards[linha]);
                        printf("  ");
                    } else {
                        printf("       ");
                    }
                } else {
                    imprimirCarta(j->pilhas[i].cartas.cards[linha]);
                    printf("  ");
                }
            } else {
                printf("       ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
// mostra os comandos disponiveis
void mostrarComandos(void) {
    printf("Comandos: <origem> <destino> [quantidade] | 'u' undo | 'q' sair\n");
}