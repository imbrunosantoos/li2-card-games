#ifndef MENU_PACIENCIAS_H
#define MENU_PACIENCIAS_H

#include "../logic/parser.h"

#define MAX_PACIENCIAS 20

// guarda os caminhos dos ficheiros encontrados
typedef struct {
    char caminhos[MAX_PACIENCIAS][100];
    int  numPaciencias;
} ListaPaciencias;

// le a pasta paciencias/ e lista os ficheiros
ListaPaciencias lerPastaPaciencias(void);

// mostra o menu e devolve indice escolhido (0 = sair)
int mostrarMenu(ListaPaciencias *lista);

#endif