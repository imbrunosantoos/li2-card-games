#include "game.h"
#include "moviment.h"
#include "../ui/display.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "saveload.h"

#define MAX_HISTORICO 100

/* le a jogada do utilizador */
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

/* desfaz a ultima jogada */
static int tratarUndo(int turno, char *mensagem) {
    if (turno > 0) return turno - 1;
    strcpy(mensagem, "Nao ha jogadas para desfazer!");
    return turno;
}

/* guarda o jogo em ficheiro */
static int tratarSave(Jogo historico[], int turno, Paciencia *p, char *mensagem) {
    saveGame(p->nome, historico[turno].pilhas, historico[turno].numPilhas, "save.txt");
    strcpy(mensagem, "Jogo guardado!");
    return turno;
}

/* executa uma jogada e devolve o novo turno */
static int tratarJogada(Jogo historico[], int turno, int origem, int destino, int quantidade, char *mensagem) {
    historico[turno + 1] = historico[turno];
    if (tentarMover(&historico[turno + 1], origem, destino, quantidade)) {
        executarAutomaticos(&historico[turno + 1]);
        return turno + 1;
    }
    strcpy(mensagem, "Movimento invalido!");
    return turno;
}

/* trata o resultado da jogada e devolve o novo turno */
static int tratarResultado(Jogo historico[], int turno, Paciencia *p,
                            int resultado, int origem, int destino, int quantidade, char *mensagem) {
    if (resultado == 'q') return -1;
    if (resultado == 'u') return tratarUndo(turno, mensagem);
    if (resultado == 's') return tratarSave(historico, turno, p, mensagem);
    if (resultado == 'l') {
        loadGame(historico[turno].pilhas, historico[turno].numPilhas, "save.txt");
        strcpy(mensagem, "Jogo carregado!");
        return turno;
    }
    if (resultado == -1) {
        strcpy(mensagem, "Formato errado! Ex: 1 3  ou  1 3 2");
        return turno;
    }
    return tratarJogada(historico, turno, origem, destino, quantidade, mensagem);
}

/* corre o loop principal do jogo */
void jogarPaciencia(Paciencia *p) {
    Jogo historico[MAX_HISTORICO];
    int turno = 0;
    int origem = 0, destino = 0, quantidade = 0;
    char mensagem[100] = "";

    criarJogo(&historico[0], p);
    executarAutomaticos(&historico[0]);

    while (turno >= 0 && turno < MAX_HISTORICO && jogoGanho(&historico[turno]) == 0) {
        system("clear");
        mostrarJogo(&historico[turno]);
        mostrarComandos();
        if (mensagem[0] != '\0')
            printf(">> %s\n", mensagem);
        mensagem[0] = '\0';
        int resultado = lerJogada(&origem, &destino, &quantidade);
        turno = tratarResultado(historico, turno, p, resultado, origem, destino, quantidade, mensagem);
    }

    if (turno >= 0 && turno < MAX_HISTORICO && jogoGanho(&historico[turno])) {
        printf("\nPARABENS! Ganhaste!\n");
    }
}
