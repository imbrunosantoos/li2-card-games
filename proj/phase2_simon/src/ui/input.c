#include "input.h"
#include "display.h"
#include <stdio.h>
#include <string.h>

// funcao que le e valida o input dado
static int lerInput(int *origem, int *destino, int *quantidade) {
    char linha[100];
    printf("\nJogada (origem destino [quantidade]) ou 'u' para undo: ");
    fgets(linha, 100, stdin);

    if (linha[0] == 'u' || linha[0] == 'U') return 'u';

    int lidos = sscanf(linha, "%d %d %d", origem, destino, quantidade);
    if (lidos < 2) return -1;
    if (lidos == 2) *quantidade = 1;
    if (*origem < 1 || *origem > 10 || *destino < 1 || *destino > 10) return -1;

    *origem = *origem - 1;
    *destino = *destino - 1;
    return 1;
}

// funcao que executa o movimento
static int executarMovimento(SimonState *s, int origem, int destino, int quantidade) {
    if (quantidade == 1) {
        if (simonMove(s, origem, destino) == 1) {
            printf("Movimento feito!\n");
            simonUpdate(s);
            return 1;
        }
    } else {
        if (simonMoveSequence(s, origem, destino, quantidade) == 1) {
            printf("Sequencia movida!\n");
            simonUpdate(s);
            return 1;
        }
    }
    printf("Movimento invalido!\n");
    return 0;
}

// funcao principal que apenas solicita o movimento
int requestMove(SimonState *s) {
    int origem, destino, quantidade;
    int resultado = lerInput(&origem, &destino, &quantidade);

    if (resultado == 'u') return 'u';
    if (resultado == -1) return 0;

    return executarMovimento(s, origem, destino, quantidade);
}