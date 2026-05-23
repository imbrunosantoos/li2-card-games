#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

// verifica se o ficheiro termina em .paciencia
static int ehFicheiroPaciencia(char *nome) {
    int len = strlen(nome);
    if (len < 10) return 0;
    return strcmp(nome + len - 9, "paciencia") == 0;
}

// le a pasta paciencias/ e guarda os caminhos
ListaPaciencias lerPastaPaciencias(void) {
    ListaPaciencias lista;
    lista.numPaciencias = 0;

    DIR *dir = opendir("paciencias");
    if (dir == NULL) {
        printf("Erro: pasta paciencias/ nao encontrada!\n");
        return lista;
    }

    struct dirent *entrada;
    while ((entrada = readdir(dir)) != NULL) {
        if (ehFicheiroPaciencia(entrada->d_name)) {
            snprintf(lista.caminhos[lista.numPaciencias],
                     100,
                     "paciencias/%s",
                     entrada->d_name);
            lista.numPaciencias++;
        }
    }

    closedir(dir);
    return lista;
}

// mostra o menu e devolve indice da paciencia escolhida
int mostrarMenu(ListaPaciencias *lista) {
    int i, opcao;

    printf("\n============================\n");
    printf("   ESCOLHE UMA PACIENCIA    \n");
    printf("============================\n");

    for (i = 0; i < lista->numPaciencias; i++) {
        Paciencia p = parsePaciencia(lista->caminhos[i]);
        printf("%d. %s\n", i + 1, p.nome);
    }

    printf("0. Sair\n");
    printf("----------------------------\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    return opcao;
}