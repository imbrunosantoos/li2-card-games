#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "../../../common/pile.h"

// guarda o estado das pilhas num ficheiro
void saveGame(char *nomePaciencia, Pile pilhas[], int numPilhas, char *ficheiro);

// carrega o estado das pilhas de um ficheiro
void loadGame(Pile pilhas[], int numPilhas, char *ficheiro);

#endif