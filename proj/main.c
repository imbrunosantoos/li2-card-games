#include <stdio.h>
#include <string.h>
#include "phase3/src/logic/parser.h"
#include "phase3/src/logic/game.h"
#include "phase3/src/ui/menu.h"

int main(void) {
    ListaPaciencias lista = lerPastaPaciencias();

    if (lista.numPaciencias == 0) {
        printf("Nenhuma paciencia encontrada!\n");
        return 1;
    }

    int opcao = mostrarMenu(&lista);

    while (opcao != 0) {
        if (opcao >= 1 && opcao <= lista.numPaciencias) {
            Paciencia p = parsePaciencia(lista.caminhos[opcao - 1]);
            getchar();  // limpa o \n que ficou do scanf
            jogarPaciencia(&p);
        } else {
            printf("Opcao invalida!\n");
        }
        opcao = mostrarMenu(&lista);
    }

    printf("Ate logo!\n");
    return 0;
}