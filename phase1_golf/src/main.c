#include "logic/game.h"
#include "ui/display.h"
#include "ui/input.h"

// Processa o comando e executa a jogada correspondente
static void handleCommand(GameState *g, Command cmd) {
    int ok = 0;

    if (cmd >= CMD_PILE_1 && cmd <= CMD_PILE_7) {
        ok = gameMoveToDiscard(g, cmd - 1); // cmd 1-7 → índice 0-6
    } else if (cmd == CMD_DRAW) {
        ok = gameDrawcard(g);
    }

    if (!ok && cmd != CMD_QUIT)
        displayInvalidMove();
}

int main(void) {
    GameState g;
    gameInit(&g);      // inicializa e baralha
    displayHelp();     // mostra comandos

    Command cmd;
    do {
        displayBoard(&g);         // mostra tabuleiro
        cmd = inputRead();        // lê comando do jogador
        handleCommand(&g, cmd);   // executa
    } while (cmd != CMD_QUIT && !gameIsOver(&g));

    if (gameIsOver(&g))
        displayWin();

    return 0;
}
