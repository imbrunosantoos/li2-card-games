#include "game.h"

// Esta função prepara o jogo do zero
void simonInit(SimonState *s) {
    int col, c, i, limit; // variaveis coluna, carta e limite
    Card temp;

    deckInit(&s->deck);
    deckShuffle(&s->deck);

    for (i = 0; i < 10; i++) { //começamos por pôr todas as 10 colunas vazias
        pileInit(&s->columns[i]);
    }
    for (col = 0; col < 10; col++) { //distribuir as cartas pelas colunas
        if (col < 3) {
            limit = 8;  //limite de 8 cartas para as primeiras 3 colunas
        } else {
            limit = 8 - (col - 2);  // para distribuir de forma decrescente para o resto das colunas, na coluna correspondente, 
        }                           //estabelecemos um limite de 8 - (o numero da coluna - 2) para que fique sempre com menos 1 carta que a coluna anterior
        for (c = 0; c < limit; c++) {       //vai buscar cartas ao baralho e mete-as nas colunas ate ficarem com o nº de cartas limit
            if (deckDraw(&s->deck, &temp) == 1) {
                pilePush(&s->columns[col], temp);
            }
        }
    }
}

// Esta função serve para mover apenas uma carta de cada vez
int simonMove(SimonState *s, int topCol, int destCol) {
    Card movingCard;
    Card destCard;

    if (topCol < 0 || topCol > 9 || destCol < 0 || destCol > 9) {  //verifica se a coluna é valida
        return 0;
    }
    if (pileIsEmpty(&s->columns[topCol]) == 1) {  //se a coluna estiver vazia, não há nada para tirar de lá
        return 0;
    }
    //vemos qual é a carta que vai ser movida
    movingCard = pileTop(&s->columns[topCol]);

    if (pileIsEmpty(&s->columns[destCol]) == 1) {   //se a coluna de destino estiver vazia, podemos sempre mover a carta
        pilePop(&s->columns[topCol], &movingCard);
        pilePush(&s->columns[destCol], movingCard);
        return 1;
    }

    //se a coluna que queremos mover a carta não estiver vazia, so podemos mover a carta se for o valor abaixo
    destCard = pileTop(&s->columns[destCol]);
    if (movingCard.value == destCard.value - 1) {
        pilePop(&s->columns[topCol], &movingCard);
        pilePush(&s->columns[destCol], movingCard);
        return 1;
    }
    
    //se não for nenhum destes casos nao podemos mover a carta
    return 0;
}

//move um grupo de várias cartas juntas
int simonMoveSequence(SimonState *s, int topCol, int destCol, int numCards) {
    int i, total;
    Card aux;
    Card c; 

    total = pileSize(&s->columns[topCol]);

    if (numCards <= 0 || numCards > total) {  //para não tentarmos mover zero cartas ou mais do que existem
        return 0;
    }
    for (i = 0; i < numCards - 1; i++) {                                //confirmar se o grupo de cartas que queremos mover está bem organizado
        Card c1 = s->columns[topCol].cards[total - numCards + i];       //têm de ter todas o mesmo naipe e estar em escada (ex: 7, 6, 5...)
        Card c2 = s->columns[topCol].cards[total - numCards + i + 1];
        if (c1.suit != c2.suit || c1.value != c2.value + 1) {
            return 0;
        }
    }
    //se a primeira carta dessa sequencia pode ir para a coluna de destino
    c = s->columns[topCol].cards[total - numCards];
    if (pileIsEmpty(&s->columns[destCol]) == 0) {
        Card target = pileTop(&s->columns[destCol]);
        if (c.value != target.value - 1) {
            return 0;
        }
    }
    for (i = 0; i < numCards; i++) {    //se for possivel, primeiro copiamos as cartas para o destino
        aux = s->columns[topCol].cards[total - numCards + i];
        pilePush(&s->columns[destCol], aux);
    }
    for (i = 0; i < numCards; i++) {    //depois limpamos as cartas da coluna de onde elas vieram
        Card lixo; 
        pilePop(&s->columns[topCol], &lixo);
    }
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

//limpa as sequências completas de rei a ás que aparecerem
void simonUpdate(SimonState *s) {
    int col, c;
    Card aux;

    for (col = 0; col < 10; col++) {
        int size = pileSize(&s->columns[col]);
        if (size >= 13) {   //para uma sequencia tar completa tem que ter pelo menos 13 cartas
            if (s->columns[col].cards[size - 13].value == 12) { //verificamos se a carta mais abaixo da sequencia é um rei
                int ok = 0; //contamos quantas cartas estão na ordem correta (ok)
                for (c = 0; c < 12; c++) { //comparamos as 13 cartas, par a par
                    Card bellowCard = s->columns[col].cards[size - 13 + c]; //o size -13 é para focar nas ultimas 13 cartas
                    Card aboveCard = s->columns[col].cards[size - 13 + c + 1];  //usamos o "+ c" ou "+ c + 1" que é para comparar as duas cartas e ver se sao do mesmo naipe e se estao em escada
                    if (bellowCard.suit == aboveCard.suit && bellowCard.value == aboveCard.value + 1) { //se o par tiver o mesmo naipe e tiver em escada, contamos como "ok"
                        ok = ok + 1;
                    }
                }
                if (ok == 12) { //se o ok=12, significa que temos as 13 cartas em ordem
                    for (c = 0; c < 13; c++) { //tiramos essas 13 cartas da mesa
                        pilePop(&s->columns[col], &aux);    // usamos o pilePop para retirar as cartas da mesa uma a uma 
                    }                                       // usamos o aux para receber as cartas que o pilePop retira, serve como um "lixo"
                }
            }
        }
    }
}