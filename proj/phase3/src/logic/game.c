#include "game.h"
#include "moviment.h"
#include "../ui/display.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "saveload.h"

#define MAX_HISTORICO 100

// le a jogada do utilizador
static int lerJogada(int *origem, int *destino, int *quantidade) {
    char linha[100];
    printf("Jogada (origem destino [quantidade]) ou 'u' undo 's' save 'l' load 'q' sair: ");
    fgets(linha, 100, stdin);

    if (linha[0] == 'u' || linha[0] == 'U') return 'u';
    if (linha[0] == 'q' || linha[0] == 'Q') return 'q';
    if (linha[0] == 's' || linha[0] == 'S') return 's';
    if (linha[0] == 'l' || linha[0] == 'L') return 'l';

    int lidos = sscanf(linha, "%d %d %d", origem, destino, quantidade);
    if (lidos < 2) return -1;
    if (lidos == 2) *quantidade = 1;

    *origem  = *origem  - 1;
    *destino = *destino - 1;
    return 1;
}

// trata o resultado da jogada e devolve o novo turno
static int tratarResultado(Jogo historico[], int turno, Paciencia *p,
                            int resultado, int origem, int destino, int quantidade) {
    if (resultado == 'q') return -1;  // ← usa -1 para sair
    if (resultado == 'u') {
        if (turno > 0) return turno - 1;
        printf("Nao ha jogadas para desfazer!\n");
        return turno;
    }
    if (resultado == 's') {
        saveGame(p->nome, historico[turno].pilhas, historico[turno].numPilhas, "save.txt");
        return turno;
    }
    if (resultado == 'l') {
        loadGame(historico[turno].pilhas, historico[turno].numPilhas, "save.txt");
        return turno;
    }
    if (resultado == -1) {
        printf("Formato errado!\n");
        return turno;
    }
    historico[turno + 1] = historico[turno];
    if (tentarMover(&historico[turno + 1], origem, destino, quantidade)) {
        executarAutomaticos(&historico[turno + 1]);
        return turno + 1;
    }
    printf("Movimento invalido!\n");
    return turno;
}

// corre o loop principal do jogo
void jogarPaciencia(Paciencia *p) {
    Jogo historico[MAX_HISTORICO];
    int turno = 0;
    int origem, destino, quantidade;

    criarJogo(&historico[0], p);
    executarAutomaticos(&historico[0]);

    while (turno >= 0 && turno < MAX_HISTORICO && jogoGanho(&historico[turno]) == 0) {
        system("clear");
        mostrarJogo(&historico[turno]);
        mostrarComandos();
        int resultado = lerJogada(&origem, &destino, &quantidade);
        turno = tratarResultado(historico, turno, p, resultado, origem, destino, quantidade);
    }

    if (turno >= 0 && turno < MAX_HISTORICO && jogoGanho(&historico[turno])) {
        printf("\nPARABENS! Ganhaste!\n");
    }
}