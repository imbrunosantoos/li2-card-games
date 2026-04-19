#include <stdio.h>
#include "logic/game.h"
#include "ui/display.h"
#include "ui/input.h"

void playSimon () {
    SimonState game;
    SimonState backup;  //guarda a jogada anterior
    SimonState temp;    //guarda o estado atual do jogo antes de saber se a joda é valida

    simonInit(&game); //prepara o jogo
    backup = game;  //aqui o backup é o estado inicial

    while (simonIsOver (&game) == 0) {  //enquanto jogo não acabou
        displayBoard (&game);           //mostra as cartas na mesa
        displayHelp();                  //instruções para jogar
        temp = game;    // guarda o estado do jogo
        int result = requesteMove(&game);   //o requesteMove pede um movimento ao jogador
        if (result == 99) {
            game = backup; //se o jogador digitou 99, voltamos a jogada atras
        }
        else if (result == 1) {
            backup = temp;  //se a jogada for valida, o estado anterior do jogo passa a ser o backup
        }
    }
    displayBoard (&game);
    displayWin();
}