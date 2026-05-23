#include "game.h"

// Inicializa as 10 colunas vazias
static void simonInitColumns(SimonState *s) {
    int i;
    for (i = 0; i < 10; i++) {
        pileInit(&s->columns[i]);
    }
}

// Calcula o limite de cartas para uma coluna (8 para as 3 primeiras, depois decrescente)
static int simonGetColumnLimit(int col) {
    if (col < 3) {
        return 8;
    }
    return 8 - (col - 2);
}

// Distribui as cartas pelas colunas segundo os limites
static void simonDealCards(SimonState *s) {
    int col, c, limit;
    Card temp;

    for (col = 0; col < 10; col++) {
        limit = simonGetColumnLimit(col);
        for (c = 0; c < limit; c++) {
            if (deckDraw(&s->deck, &temp) == 1) {
                pilePush(&s->columns[col], temp);
            }
        }
    }
}

// Esta função prepara o jogo do zero
void simonInit(SimonState *s) {
    deckInit(&s->deck);
    deckShuffle(&s->deck);
    simonInitColumns(s);
    simonDealCards(s);
}

// transfere a carta do topo de uma coluna para outra
static void transferirCarta(SimonState *s, int origem, int destino) {
    Card carta;
    pilePop(&s->columns[origem], &carta);
    pilePush(&s->columns[destino], carta);
}

/// Esta função serve para mover apenas uma carta de cada vez
int simonMove(SimonState *s, int topCol, int destCol) {
    Card movingCard;
    Card destCard;

    if (topCol < 0 || topCol > 9 || destCol < 0 || destCol > 9) {
        return 0;
    }
    if (pileIsEmpty(&s->columns[topCol]) == 1) {
        return 0;
    }

    movingCard = pileTop(&s->columns[topCol]);

    if (pileIsEmpty(&s->columns[destCol]) == 1) {
        transferirCarta(s, topCol, destCol);
        return 1;
    }

    destCard = pileTop(&s->columns[destCol]);
    if (movingCard.value == destCard.value - 1) {
        transferirCarta(s, topCol, destCol);  // ← mudou aqui
        return 1;
    }

    return 0;
}

// Valida se um grupo de cartas está em sequência válida (mesmo naipe, valores em escada)
static int simonValidateSequence(SimonState *s, int topCol, int numCards) {
    int i, total;
    total = pileSize(&s->columns[topCol]);

    for (i = 0; i < numCards - 1; i++) {
        Card c1 = s->columns[topCol].cards[total - numCards + i];
        Card c2 = s->columns[topCol].cards[total - numCards + i + 1];
        if (c1.suit != c2.suit || c1.value != c2.value + 1) {
            return 0;
        }
    }
    return 1;
}

// Valida se a primeira carta da sequência pode ser movida para a coluna de destino
static int simonCanMoveToDest(SimonState *s, int topCol, int destCol, int numCards) {
    int total = pileSize(&s->columns[topCol]);
    Card c = s->columns[topCol].cards[total - numCards];

    if (pileIsEmpty(&s->columns[destCol]) == 1) {
        return 1;
    }
    Card target = pileTop(&s->columns[destCol]);
    return (c.value == target.value - 1) ? 1 : 0;
}

// Executa a movimentação das cartas
static void simonExecuteMove(SimonState *s, int topCol, int destCol, int numCards) {
    int i, total;
    Card aux;
    total = pileSize(&s->columns[topCol]);

    for (i = 0; i < numCards; i++) {
        aux = s->columns[topCol].cards[total - numCards + i];
        pilePush(&s->columns[destCol], aux);
    }
    for (i = 0; i < numCards; i++) {
        Card lixo;
        pilePop(&s->columns[topCol], &lixo);
    }
}

//move um grupo de várias cartas juntas
int simonMoveSequence(SimonState *s, int topCol, int destCol, int numCards) {
    int total;
    total = pileSize(&s->columns[topCol]);

    if (numCards <= 0 || numCards > total) {
        return 0;
    }
    if (simonValidateSequence(s, topCol, numCards) == 0) {
        return 0;
    }
    if (simonCanMoveToDest(s, topCol, destCol, numCards) == 0) {
        return 0;
    }
    simonExecuteMove(s, topCol, destCol, numCards);
    return 1;
}

//verifica se o jogo ja acabou, quando não sobra nenhuma carta na mesa
int simonIsOver(SimonState *s) {
    int i;
    for (i = 0; i < 10; i++) {  //percorre as 10 colunas, se encontrar alguma que não esteja vazia o jogo continua
        if (pileIsEmpty(&s->columns[i]) == 0) return 0;
    }
    return 1;   //se todas as colunas estiverem vazias o jogo acabou
}

// Verifica se uma coluna tem uma sequência completa de Rei a Ás
static int simonCheckSequence(SimonState *s, int col) {
    int size = pileSize(&s->columns[col]);
    int c, ok = 0;

    if (size < 13) {
        return 0;
    }
    if (s->columns[col].cards[size - 13].value != 12) {
        return 0;
    }
    for (c = 0; c < 12; c++) {
        Card bellowCard = s->columns[col].cards[size - 13 + c];
        Card aboveCard = s->columns[col].cards[size - 13 + c + 1];
        if (bellowCard.suit == aboveCard.suit && bellowCard.value == aboveCard.value + 1) {
            ok++;
        }
    }
    return (ok == 12) ? 1 : 0;
}

// Remove a sequência completa de 13 cartas da coluna
static void simonRemoveSequence(SimonState *s, int col) {
    int c;
    Card aux;
    for (c = 0; c < 13; c++) {
        pilePop(&s->columns[col], &aux);
    }
}

//limpa as sequências completas de rei a ás que aparecerem
void simonUpdate(SimonState *s) {
    int col;
    for (col = 0; col < 10; col++) {
        if (simonCheckSequence(s, col) == 1) {
            simonRemoveSequence(s, col);
        }
    }
}