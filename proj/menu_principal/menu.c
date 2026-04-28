#include "menu.h"
#include <stdio.h>

int mostrarMenuPrincipal() {
    int option;
    int result;

    printf("\n====================================");
    printf("\n          MENU DE JOGOS             ");
    printf("\n====================================");
    printf("\n 1 - Jogar GOLF (Fase 1)");
    printf("\n 2 - Jogar SIMON (Fase 2)");
    printf("\n 0 - Sair do Programa");
    printf("\n------------------------------------");
    printf("\nEscolha uma opcao: ");

    result = scanf(" %d", &option);
    if (result != 1) {
        return -1;
    }
    return option;
}