#include <stdio.h>
#include "logic/game.h"
#include "ui/display.h"
#include "ui/input.h"

//variavel para guardar o historico de jogadas
#define MAX_HISTORY 1000

void executarUndo(SimonState *game, SimonState history[], int *currentTurn){
    if (*currentTurn > 0){
        (*currentTurn)--;
        *game = history[*currentTurn];
    } else {
        printf("Nao e possivel voltar mais atras!\n");
    }
}

void playSimon () {
    SimonState game;
    SimonState history[MAX_HISTORY];
    int currentTurn = 0;

    simonInit(&game); //prepara o jogo
    history[currentTurn] = game;  //chama o estado inicial do jogo

    while (simonIsOver (&game) == 0) {  //enquanto jogo não acabou
        simonDisplayBoard (&game);           //mostra as cartas na mesa
        simonDisplayHelp();                  //instruções para jogar
        int result = requestMove(&game);   //o requestMove pede um movimento ao jogador
        if (result == 'u') {
           executarUndo(&game, history, &currentTurn); //se o jogador digitou 99, voltamos a jogada atras
        } else if (result == 1) {
            currentTurn++;
            history[currentTurn] = game;  //se a jogada for valida, o estado anterior do jogo passa a ser o backup
        }
    }
    simonDisplayBoard (&game);
    simonDisplayWin();
}