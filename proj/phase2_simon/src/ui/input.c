#include "input.h"
#include "display.h"
#include <stdio.h>
#include <string.h>

int requestMove(SimonState *s) {
    char input[100];
    int origin, dest, quant;
    
    printf("\nJogada (origem destino quantidade) ou 'u' para undo: ");
    fgets(input, 100, stdin);
    
    // verifica se o jogador quer fazer undo
    if (input[0] == 'u' || input[0] == 'U') {
        return 'u';
    }
    
    // tenta ler 2 ou 3 numeros da linha
    int parsed = sscanf(input, "%d %d %d", &origin, &dest, &quant);
    
    // tem que ter pelo menos origem e destino
    if (parsed < 2) {
        printf("Formato errado! Use: origem destino [quantidade]\n");
        return 0;
    }
    
    // se nao digitou quantidade, assume 1
    if (parsed == 2) {
        quant = 1;
    }
    
    // valida as colunas
    if (origin < 1 || origin > 10 || dest < 1 || dest > 10) {
        printf("Colunas devem estar entre 1 e 10!\n");
        return 0;
    }
    
    // converte para indice (0 a 9)
    origin = origin - 1;
    dest = dest - 1;
    
    // executa o movimento
    if (quant == 1) {
        if (simonMove(s, origin, dest) == 1) {
            printf("Movimento feito!\n");
            simonUpdate(s);
            return 1;
        } else {
            printf("Movimento invalido!\n");
            return 0;
        }
    } else {
        if (simonMoveSequence(s, origin, dest, quant) == 1) {
            printf("Sequencia movida!\n");
            simonUpdate(s);
            return 1;
        } else {
            printf("Movimento invalido!\n");
            return 0;
        }
    }
}