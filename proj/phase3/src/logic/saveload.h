#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "engine.h"

// guarda o estado das pilhas num ficheiro
void saveGame(char *nomePaciencia, PilhaJogo pilhas[], int numPilhas, char *ficheiro);

// carrega o estado das pilhas de um ficheiro
void loadGame(PilhaJogo pilhas[], int numPilhas, char *ficheiro);

#endif