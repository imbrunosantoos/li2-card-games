#include "game.h"
#include "moviment.h"
#include "../ui/display.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_HISTORICO 100

// le a jogada do utilizador
static int lerJogada(int *origem, int *destino, int *quantidade) {
    char linha[100];
    printf("Jogada (origem destino [quantidade]) ou 'u' undo ou 'q' sair: ");
    fgets(linha, 100, stdin);

    if (linha[0] == 'u' || linha[0] == 'U') return 'u';
    if (linha[0] == 'q' || linha[0] == 'Q') return 'q';

    int lidos = sscanf(linha, "%d %d %d", origem, destino, quantidade);
    if (lidos < 2) return -1;
    if (lidos == 2) *quantidade = 1;

    *origem  = *origem  - 1;
    *destino = *destino - 1;
    return 1;
}

// corre o loop principal do jogo
void jogarPaciencia(Paciencia *p) {
    Jogo historico[MAX_HISTORICO];
    int turno = 0;
    int origem, destino, quantidade;

    criarJogo(&historico[0], p);
    executarAutomaticos(&historico[0]);

    while (jogoGanho(&historico[turno]) == 0) {
        system("clear");
        mostrarJogo(&historico[turno]);
        mostrarComandos();

        int resultado = lerJogada(&origem, &destino, &quantidade);

        if (resultado == 'q') break;

        if (resultado == 'u') {
            if (turno > 0) {
                turno--;
                printf("Voltaste uma jogada!\n");
            } else {
                printf("Nao ha jogadas para desfazer!\n");
            }
            continue;
        }

        if (resultado == -1) {
            printf("Formato errado!\n");
            continue;
        }

        // copia o estado atual para o proximo
        historico[turno + 1] = historico[turno];

        if (tentarMover(&historico[turno + 1], origem, destino, quantidade)) {
            executarAutomaticos(&historico[turno + 1]);
            turno++;
            printf("Movimento feito!\n");
        } else {
            printf("Movimento invalido!\n");
        }
    }

    if (jogoGanho(&historico[turno])) {
        printf("\nPARABENS! Ganhaste!\n");
    }
}