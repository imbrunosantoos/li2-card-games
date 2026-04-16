#include "input.h"
#include <stdio.h>

// Lê uma linha do terminal e interpreta o comando
Command inputRead(void) {
    char buf[16];  // buffer para guardar o que o jogador escreve, com o máximo de 16 caracteres 

    printf("O teu comando: ");                  // pede ao jogador para escrever um comando
    if (fgets(buf, sizeof(buf), stdin) == NULL) // lê a linha inteira que o jogador escreveu
        return CMD_QUIT;                         // fim de ficheiro ou erro, sai do jogo 

    // Interpreta o primeiro carácter
    switch (buf[0]) {
        case '1': return CMD_PILE_1;    // escolheu monte 1
        case '2': return CMD_PILE_2;    // escolheu monte 2
        case '3': return CMD_PILE_3;    // escolheu monte 3
        case '4': return CMD_PILE_4;    // escolheu monte 4
        case '5': return CMD_PILE_5;    // escolheu monte 5
        case '6': return CMD_PILE_6;    // escolheu monte 6
        case '7': return CMD_PILE_7;    // escolheu monte 7
        case 'd':
        case 'D': return CMD_DRAW;   // jogador quer buscar uma carta do baralho, aceita maiúscula e minúscula
        case 'q':
        case 'Q': return CMD_QUIT;      // jogador quer sair do jogo, aceita maiúscula e minúscula
        default:  return CMD_INVALID;   // jogador escreveu algo que não e valido 
    }
}
