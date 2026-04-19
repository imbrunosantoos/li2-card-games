#include "input.h"
#include "display.h"
#include <stdio.h>

int requestMove (SimonState *s) {
    int readOrigin, readDest, quant;    //variaveis origem, destino e quantidade

    printf ("\n---------- MENU DE JOGADA ----------\n");
    printf ("ORIGEM (1-10), Undo (99) ou Dica (88): ");
    scanf(" %d", &readOrigin);
    
    // Opção de dica
    if (readOrigin == 88) {
        displayHint(s);
        return 88;
    }
    
    // Opção de undo
    if (readOrigin == 99) {
        return 99; //sinal de undo
    }
    
    printf ("DESTINO (1-10): ");
    scanf(" %d", &readDest);
    printf ("QUANIDADE: ");
    scanf(" %d", &quant);

    int origin = readOrigin - 1;    //como as colunas vão estar numeradas de 1 a 10, entao ao comando que o jogador colocar, 
    int dest = readDest - 1;        //retiramos 1 para converter para indice 

    if (quant == 1) {
        if (simonMove(s, origin, dest) == 1) {  //apenas move uma carta, s (estado do jogo), origin (coluna de origem) e dest (coluna em que a carta vai ser colocada)
            printf ("Concluído.\n");            //tem de ser igual a 1 porque signifca que a operação foi concluida sem problemas 
            return 1;
        } else {
            printf ("Inválido! Tenta novamente.\n");
            return 0;
        }
    } else {
        if (simonMoveSequence (s, origin, dest, quant) == 1) {  //igual ao de cima, simonMove, so que ate tenta mover uma quantidade de cartas juntas da origem para o destino
            printf ("Concluído.\n");
            return 1;
        } else {
            printf ("Inválido! Tenta novamente.\n");
            return 0;
        }
    }
    simonUpdate(s);
    return 0;
}