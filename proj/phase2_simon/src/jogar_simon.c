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
        simonDisplayBoard (&game);           //mostra as cartas na mesa
        simonDisplayHelp();                  //instruções para jogar
        temp = game;    // guarda o estado do jogo
        int result = requestMove(&game);   //o requestMove pede um movimento ao jogador
        if (result == 99) {
            game = backup; //se o jogador digitou 99, voltamos a jogada atras
        } else if (result == 1) {
            backup = temp;  //se a jogada for valida, o estado anterior do jogo passa a ser o backup
        }
    }
    simonDisplayBoard (&game);
    simonDisplayWin();
}