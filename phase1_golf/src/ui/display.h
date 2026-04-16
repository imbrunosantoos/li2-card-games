#ifndef DISPLAY_H
#define DISPLAY_H

#include "../logic/game.h"

// Mostra o tabuleiro completo no terminal
void displayBoard (GameState *g);

// Mostra os comandos disponíveis ao jogador
void displayHelp(void);

// Mostra mensagem de vitória
void displayWin(void);

// Mostra mensagem de erro numa jogada inválida
void displayInvalidMove(void);

#endif
