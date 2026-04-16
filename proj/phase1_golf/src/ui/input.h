#ifndef INPUT_H
#define INPUT_H

// Representa o comando do jogador
typedef enum {
    CMD_PILE_1 = 1, // jogar da pilha 1
    CMD_PILE_2,     // jogar da pilha 2
    CMD_PILE_3,     // jogar da pilha 3
    CMD_PILE_4,     // jogar da pilha 4
    CMD_PILE_5,     // jogar da pilha 5
    CMD_PILE_6,     // jogar da pilha 6
    CMD_PILE_7,     // jogar da pilha 7
    CMD_DRAW,       // biscar do baralho
    CMD_QUIT,       // sair
    CMD_INVALID     // comando não reconhecido
} Command;

// Lê e devolve o comando do jogador
Command inputRead(void);

#endif
