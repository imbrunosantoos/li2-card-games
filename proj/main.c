#include <stdio.h>
#include <string.h>
#include "phase3/src/logic/parser.h"
#include "phase3/src/ui/menu.h"

void playGolf(void);
void playSimon(void);

static void lancarJogo(Paciencia *p) {
    if (strcmp(p->nome, "Golf") == 0) {
        playGolf();
    } else if (strcmp(p->nome, "SimpleSimon") == 0) {
        playSimon();
    } else {
        printf("Paciencia '%s' ainda nao implementada!\n", p->nome);
    }
}

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
            lancarJogo(&p);
        } else {
            printf("Opcao invalida!\n");
        }
        opcao = mostrarMenu(&lista);
    }

    printf("Ate logo!\n");
    return 0;
}