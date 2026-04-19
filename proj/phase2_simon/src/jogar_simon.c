#include <stdio.h>
#include "logic/game.h"
#include "ui/display.h"
#include "ui/input.h"

void playSimon () {
    SimonState game;
    simonInit(&game); //prepara o jogo

    while (simonIsOver (&game) == 0) {  //enquanto jogo não acabou
        displayBoard (&game);           //mostra as cartas na mesa
        displayHelp();                  //instruções para jogar
        requesteMove(&game);            //pede um movimento ao jogador
    }
    displayBoard (&game);
    displayWin();
}