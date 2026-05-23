#include "saveload.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// converte valor int para string (1->A, 11->J, etc)
static void valorParaStr(int valor, char *out) {
    if (valor == 1)       strcpy(out, "A");
    else if (valor == 11) strcpy(out, "J");
    else if (valor == 12) strcpy(out, "Q");
    else if (valor == 13) strcpy(out, "K");
    else sprintf(out, "%d", valor);
}

// converte naipe int para char (0->C, 1->D, 2->H, 3->S)
static char naipeParaChar(int naipe) {
    if (naipe == 0) return 'C';
    if (naipe == 1) return 'D';
    if (naipe == 2) return 'H';
    return 'S';
}

// converte string para valor int (A->1, J->11, etc)
static int strParaValor(char *str) {
    if (strcmp(str, "A") == 0)  return 1;
    if (strcmp(str, "J") == 0)  return 11;
    if (strcmp(str, "Q") == 0)  return 12;
    if (strcmp(str, "K") == 0)  return 13;
    return atoi(str);
}

// converte char para naipe int (C->0, D->1, H->2, S->3)
static int charParaNaipe(char c) {
    if (c == 'C') return 0;
    if (c == 'D') return 1;
    if (c == 'H') return 2;
    return 3;
}

// guarda o estado das pilhas num ficheiro
void saveGame(char *nomePaciencia, Pile pilhas[], int numPilhas, char *ficheiro) {
    int i, j;
    FILE *f = fopen(ficheiro, "w");
    if (f == NULL) {
        printf("Erro ao guardar jogo!\n");
        return;
    }

    // primeira linha = nome da paciencia
    fprintf(f, "%s\n", nomePaciencia);

    // uma linha por pilha
    for (i = 0; i < numPilhas; i++) {
        for (j = 0; j < pilhas[i].size; j++) {
            char valor[4];
            valorParaStr(pilhas[i].cards[j].value, valor);
            char naipe = naipeParaChar(pilhas[i].cards[j].suit);
            fprintf(f, "%s%c", valor, naipe);
            if (j < pilhas[i].size - 1) fprintf(f, " ");
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Jogo guardado em '%s'!\n", ficheiro);
}

// carrega o estado das pilhas de um ficheiro
void loadGame(Pile pilhas[], int numPilhas, char *ficheiro) {
    int i;
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL) {
        printf("Erro ao carregar jogo!\n");
        return;
    }

    // ignora primeira linha (nome da paciencia)
    char linha[500];
    fgets(linha, 500, f);

    // le uma linha por pilha
    for (i = 0; i < numPilhas; i++) {
        pileInit(&pilhas[i]);
        if (fgets(linha, 500, f) == NULL) break;

        // parse de cada carta na linha
        char *token = strtok(linha, " \n");
        while (token != NULL) {
            int len = strlen(token);
            char naipeChar = token[len - 1];
            token[len - 1] = '\0';
            int valor = strParaValor(token);
            int naipe = charParaNaipe(naipeChar);
            Card c = createCard(valor, (Suit)naipe);
            pilePush(&pilhas[i], c);
            token = strtok(NULL, " \n");
        }
    }

    fclose(f);
    printf("Jogo carregado de '%s'!\n", ficheiro);
}