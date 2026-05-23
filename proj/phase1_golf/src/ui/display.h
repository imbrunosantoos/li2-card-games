#ifndef GOLF_DISPLAY_H
#define GOLF_DISPLAY_H

#include "../logic/game.h"

//funcao que limpa o terminal no jogo golf
void clearTerminalGolf(void);

// Mostra o tabuleiro completo no terminal
void golfDisplayBoard (GameState *g);

// Mostra os comandos disponíveis ao jogador
void golfDisplayHelp(void);

// Mostra mensagem de vitória
void golfDisplayWin(void);

// Mostra mensagem de erro numa jogada inválida
void golfDisplayInvalidMove(void);

#endif
