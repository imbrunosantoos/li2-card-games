#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

/* verifica se o ficheiro termina em .paciencia */
static int ehFicheiroPaciencia(char *nome) {
    int len = strlen(nome);
    if (len < 11) return 0;
    return strcmp(nome + len - 10, ".paciencia") == 0;
}

/* adiciona uma paciencia a lista com bounds check */
static void adicionarPaciencia(ListaPaciencias *lista, char *nome) {
    if (lista->numPaciencias < MAX_PACIENCIAS) {
        snprintf(lista->caminhos[lista->numPaciencias], 100, "paciencias/%s", nome);
        lista->numPaciencias++;
    }
}

/* le a pasta paciencias/ e guarda os caminhos */
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
        if (ehFicheiroPaciencia(entrada->d_name))
            adicionarPaciencia(&lista, entrada->d_name);
    }

    closedir(dir);
    return lista;
}

/* imprime a lista de paciencias, numeradas */
static void imprimirOpcoes(ListaPaciencias *lista) {
    int i;
    for (i = 0; i < lista->numPaciencias; i++) {
        Paciencia p = parsePaciencia(lista->caminhos[i]);
        printf("%d. %s\n", i + 1, p.nome);
    }
}

/* mostra o menu e devolve indice da paciencia escolhida */
int mostrarMenu(ListaPaciencias *lista) {
    int opcao;
    char linha[20];
    printf("\n============================\n");
    printf("   ESCOLHE UMA PACIENCIA    \n");
    printf("============================\n");
    imprimirOpcoes(lista);
    printf("0. Sair\n");
    printf("----------------------------\n");
    printf("Opcao: ");
    if (fgets(linha, 20, stdin) == NULL) return 0; // fim do input = sair
    opcao = 0;
    sscanf(linha, "%d", &opcao);
    return opcao;
}
