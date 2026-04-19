#ifndef DISPLAY_H
#define DISPLAY_H

#include "../logic/game.h"

// Mostra o tabuleiro completo no terminal
// Apresenta as 10 colunas com as cartas distribuidas
void displayBoard(SimonState *s);

// Mostra os comandos disponíveis ao jogador
// Explica como fazer uma jogada e como sair
void displayHelp(void);

// Mostra mensagem de vitória
// Apresentada quando o jogador conseguir esvaziar todas as colunas
void displayWin(void);

// Mostra mensagem de erro numa jogada inválida
// Apresentada quando o utilizador tenta fazer um movimento que nao e permitido
void displayInvalidMove(void);

#endif