#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// remove comentarios e espacos do fim da linha
static void limparLinha(char *linha) {
    char *hash = strchr(linha, '#');
    if (hash) *hash = '\0';

    int len = strlen(linha);
    while (len > 0 && (linha[len-1] == '\n' || linha[len-1] == ' ')) {
        linha[len-1] = '\0';
        len--;
    }
}

// verifica se a linha esta vazia
static int linhaVazia(char *linha) {
    int i = 0;
    while (linha[i] != '\0') {
        if (linha[i] != ' ' && linha[i] != '\n') return 0;
        i++;
    }
    return 1;
}

// processa linha JOGO
static void processarJogo(Paciencia *p, char *linha) {
    sscanf(linha, "JOGO %s", p->nome);
}

// processa linha BARALHOS
static void processarBaralhos(Paciencia *p, char *linha) {
    sscanf(linha, "BARALHOS %d", &p->numBaralhos);
}

// processa linha TIPO
static void processarTipo(Paciencia *p, char *linha) {
    TipoPilha t;
    sscanf(linha, "TIPO %s %s", t.nome, t.flags);
    p->tipos[p->numTipos] = t;
    p->numTipos++;
}

// processa linha INIT
static void processarInit(Paciencia *p, char *linha) {
    PilhaInicial pi;
    sscanf(linha, "INIT %s %d", pi.tipo, &pi.numCartas);
    p->pilhas[p->numPilhas] = pi;
    p->numPilhas++;
}

// processa linha MOV ou AUTO
static void processarMov(Paciencia *p, char *linha, int automatico) {
    RegraMovimento r;
    r.automatico = automatico;
    if (automatico) {
        sscanf(linha, "AUTO %s %s %s", r.origem, r.destino, r.flags);
    } else {
        sscanf(linha, "MOV %s %s %s", r.origem, r.destino, r.flags);
    }
    p->movimentos[p->numMovimentos] = r;
    p->numMovimentos++;
}

// processa linha WIN
static void processarWin(Paciencia *p, char *linha) {
    CondicaoVitoria v;
    sscanf(linha, "WIN %s %d", v.tipo, &v.numCartas);
    p->vitorias[p->numVitorias] = v;
    p->numVitorias++;
}

// inicializa uma paciencia vazia
static void inicializarPaciencia(Paciencia *p) {
    p->numBaralhos  = 1;
    p->numTipos     = 0;
    p->numPilhas    = 0;
    p->numMovimentos = 0;
    p->numVitorias  = 0;
    strcpy(p->nome, "");
}

// le o ficheiro e preenche a paciencia
Paciencia parsePaciencia(char *caminho) {
    Paciencia p;
    inicializarPaciencia(&p);

    FILE *f = fopen(caminho, "r");
    if (f == NULL) {
        printf("Erro ao abrir ficheiro: %s\n", caminho);
        return p;
    }

    char linha[200];
    while (fgets(linha, 200, f)) {
        limparLinha(linha);
        if (linhaVazia(linha)) continue;

        if (strncmp(linha, "JOGO", 4) == 0)     processarJogo(&p, linha);
        else if (strncmp(linha, "BARALHOS", 8) == 0) processarBaralhos(&p, linha);
        else if (strncmp(linha, "TIPO", 4) == 0)     processarTipo(&p, linha);
        else if (strncmp(linha, "INIT", 4) == 0)     processarInit(&p, linha);
        else if (strncmp(linha, "AUTO", 4) == 0)     processarMov(&p, linha, 1);
        else if (strncmp(linha, "MOV", 3) == 0)      processarMov(&p, linha, 0);
        else if (strncmp(linha, "WIN", 3) == 0)      processarWin(&p, linha);
    }

    fclose(f);
    return p;
}

// mostra o conteudo de uma paciencia (para debug)
void imprimirPaciencia(Paciencia *p) {
    int i;
    printf("Nome: %s\n", p->nome);
    printf("Baralhos: %d\n", p->numBaralhos);

    printf("Tipos (%d):\n", p->numTipos);
    for (i = 0; i < p->numTipos; i++) {
        printf("  %s flags=%s\n", p->tipos[i].nome, p->tipos[i].flags);
    }

    printf("Pilhas (%d):\n", p->numPilhas);
    for (i = 0; i < p->numPilhas; i++) {
        printf("  %s cartas=%d\n", p->pilhas[i].tipo, p->pilhas[i].numCartas);
    }

    printf("Movimentos (%d):\n", p->numMovimentos);
    for (i = 0; i < p->numMovimentos; i++) {
        printf("  %s %s -> %s %s\n",
            p->movimentos[i].automatico ? "AUTO" : "MOV",
            p->movimentos[i].origem,
            p->movimentos[i].destino,
            p->movimentos[i].flags);
    }

    printf("Vitorias (%d):\n", p->numVitorias);
    for (i = 0; i < p->numVitorias; i++) {
        printf("  %s = %d\n", p->vitorias[i].tipo, p->vitorias[i].numCartas);
    }
}