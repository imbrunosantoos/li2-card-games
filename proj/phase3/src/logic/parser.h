#ifndef PARSER_H
#define PARSER_H

#define MAX_TIPOS 10
#define MAX_PILHAS 20
#define MAX_MOVIMENTOS 20
#define MAX_NOME 50
#define MAX_FLAGS 30

// representa um tipo de pilha (ex: TAB, STOCK, DESCARTE)
typedef struct {
    char nome[MAX_NOME];   // "TAB", "STOCK", "DESCARTE"
    char flags[MAX_FLAGS]; // "=", "_", "^", "1"
} TipoPilha;

// representa uma pilha inicializada
typedef struct {
    char tipo[MAX_NOME];   // "TAB", "STOCK"
    int  numCartas;        // quantas cartas começa
} PilhaInicial;

// representa uma regra de movimento
typedef struct {
    char origem[MAX_NOME];  // "TAB"
    char destino[MAX_NOME]; // "DESCARTE"
    char flags[MAX_FLAGS];  // "*", "~", "+[m<"
    int  automatico;        // 0 = MOV, 1 = AUTO
} RegraMovimento;

// representa uma condicao de vitoria
typedef struct {
    char tipo[MAX_NOME];  // "TAB"
    int  numCartas;       // 0 = vazio, 13 = completo
} CondicaoVitoria;

// representa uma paciencia completa
typedef struct {
    char nome[MAX_NOME];                    // "Golf"
    int  numBaralhos;                       // 1 ou 2
    TipoPilha    tipos[MAX_TIPOS];          // tipos de pilhas
    int          numTipos;
    PilhaInicial pilhas[MAX_PILHAS];        // pilhas iniciais
    int          numPilhas;
    RegraMovimento movimentos[MAX_MOVIMENTOS]; // regras
    int            numMovimentos;
    CondicaoVitoria vitorias[MAX_TIPOS];    // condicoes
    int             numVitorias;
} Paciencia;

// le um ficheiro .paciencia e devolve a estrutura preenchida
Paciencia parsePaciencia(char *caminho);

// mostra o conteudo de uma paciencia (para debug)
void imprimirPaciencia(Paciencia *p);

#endif