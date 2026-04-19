#include "input.h"
#include <stdio.h>

void requestMove (SimonState *s) {
    int readOrigin, readDest, quant;    //variaveis origem, destino e quantidade

    printf ("\n---------- MENU DE JOGADA ----------\n");
    printf ("ORIGEM (1-10): ");
    scanf(" %d", &readOrigin);
    printf ("DESTINO (1-10): ");
    scanf(" %d", &readDest);
    printf ("QUANIDADE: ");
    scanf(" %d", &quant);

    int origin = readOrigin - 1;    //como as colunas vão estar numeradas de 1 a 10, entao ao comando que o jogador colocar, 
    int dest = readDest - 1;        //retiramos 1 para converter para indice 

    if (quant == 1) {
        if (simonMove(s, origin, dest) == 1) {  //apenas move uma carta, s (estado do jogo), origin (coluna de origem) e dest (coluna em que a carta vai ser colocada)
            printf ("Concluído.\n");            //tem de ser igual a 1 porque signifca que a operação foi concluida sem problemas 
        } else {
            printf ("Inválido! Tenta novamente.\n");
        }
    } else {
        if (simonMoveSequence (s, origin, dest, quant) == 1) {  //igual ao de cima, simonMove, so que ate tenta mover uma quantidade de cartas juntas da origem para o destino
            printf ("Concluído.\n");
        } else {
            printf ("Inválido! Tenta novamente.\n");
        }
    }
    simonUpdate(s);
}