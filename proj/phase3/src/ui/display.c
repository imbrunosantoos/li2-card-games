#include "display.h"
#include <stdio.h>
#include <string.h>

/* simbolos dos naipes */
static const char *naipes[] = { "♣", "♦", "♥", "♠" };

/* letras dos valores */
static const char *valores[] = {
    "?", "A", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "J", "Q", "K"
};

/* imprime uma carta formatada */
static void imprimirCarta(Card c) {
    if (c.value == 10)
        printf("|%s%s|", valores[c.value], naipes[c.suit]);
    else
        printf("| %s%s|", valores[c.value], naipes[c.suit]);
}

/* verifica se as cartas de uma pilha sao visiveis */
static int pilhaVisivel(Jogo *j, int i) {
    int t;
    for (t = 0; t < j->regras.numTipos; t++) {
        if (strcmp(j->regras.tipos[t].nome, j->pilhas[i].tipo) == 0) {
            if (strchr(j->regras.tipos[t].flags, '_') != NULL) return 0;
        }
    }
    return 1;
}

/* verifica se so o topo e visivel */
static int soTopoVisivel(Jogo *j, int i) {
    int t;
    for (t = 0; t < j->regras.numTipos; t++) {
        if (strcmp(j->regras.tipos[t].nome, j->pilhas[i].tipo) == 0) {
            if (strchr(j->regras.tipos[t].flags, '^') != NULL) return 1;
        }
    }
    return 0;
}

/* mostra a linha de cabecalho com indices das pilhas */
static void mostrarNumerosPilhas(Jogo *j) {
    int i;
    for (i = 0; i < j->numPilhas; i++)
        printf("  %2d   ", i + 1);
    printf("\n");
}

/* mostra a linha com os tipos das pilhas */
static void mostrarTiposPilhas(Jogo *j) {
    int i;
    for (i = 0; i < j->numPilhas; i++)
        printf("(%-5s) ", j->pilhas[i].tipo);
    printf("\n");
}

/* mostra a linha separadora */
static void mostrarSeparador(Jogo *j) {
    int i;
    for (i = 0; i < j->numPilhas; i++)
        printf("-------");
    printf("\n");
}

/* devolve o numero maximo de linhas visiveis */
static int maxLinhasVisiveis(Jogo *j) {
    int i, max = 1;
    for (i = 0; i < j->numPilhas; i++) {
        if (pilhaVisivel(j, i) && j->pilhas[i].cartas.size > max)
            max = j->pilhas[i].cartas.size;
    }
    return max;
}

/* mostra uma celula individual na posicao (pilha i, linha) */
static void mostrarCelula(Jogo *j, int i, int linha) {
    if (!pilhaVisivel(j, i)) {
        if (linha == 0)
            printf("[%2d##] ", j->pilhas[i].cartas.size);
        else
            printf("       ");
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
}

/* mostra uma linha completa de cartas */
static void mostrarLinhaCartas(Jogo *j, int linha) {
    int i;
    for (i = 0; i < j->numPilhas; i++) {
        if (linha < j->pilhas[i].cartas.size)
            mostrarCelula(j, i, linha);
        else
            printf("       ");
    }
    printf("\n");
}

/* mostra o tabuleiro do jogo ao utilizador */
void mostrarJogo(Jogo *j) {
    int linha, maxLinhas;
    printf("\n=== %s ===\n", j->regras.nome);
    mostrarNumerosPilhas(j);
    mostrarTiposPilhas(j);
    mostrarSeparador(j);
    maxLinhas = maxLinhasVisiveis(j);
    for (linha = 0; linha < maxLinhas; linha++)
        mostrarLinhaCartas(j, linha);
    printf("\n");
}

/* mostra os comandos disponiveis */
void mostrarComandos(void) {
    printf("Comandos: <origem> <destino> [quantidade] | 'u' undo | 'q' sair\n");
}
