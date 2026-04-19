#include <stdio.h>
#include "menu_principal/menu.h"

void playGolf ();
void playSimon ();

int main() {
    int option = -1;    //usamos o -1 que é para garantir que o ciclo comece 
    while (option != 0) {
        option = showMenu();
        if (option == 1) {
            playGolf();
        }
        if (option == 2){
            playSimon();
        }
        if (option != 1 && option != 2 && option != 0) {
            printf("\nOpcao Invalida!\n");
        }
    }
    return 0;
}