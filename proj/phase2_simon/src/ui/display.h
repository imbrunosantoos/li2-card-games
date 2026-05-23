#ifndef DISPLAY_H
#define DISPLAY_H

#include "../logic/game.h"

//funcao que limpa o terminal no jogo simon
void clearTerminalSimon(void);


// Mostra o tabuleiro completo no terminal
void simonDisplayBoard(SimonState *s);

// Mostra os comandos disponíveis ao jogador
void simonDisplayHelp(void);

// Mostra mensagem de vitória
void simonDisplayWin(void);

// Mostra mensagem de erro numa jogada inválida
void simonDisplayInvalidMove(void);

#endif