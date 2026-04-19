#include "card.h"

// Cria uma carta com o valor e naipe recebidos 
Card createCard(int value, Suit suit) {
    Card c;        // Cria uma carta vazia 
    c.value = value; // Atribiu um valor (1-13) à carta
    c.suit  = suit;  // Atribui um naipe à carta 
    return c;        // Devolve a carta preenchida (valor + naipe) 
}

// Verifica se a carta c pode ser jogada em cima de outra carta
int cardIsPlayable(Card top, Card c) {
    int diff = top.value - c.value; // Calcula a diferença entre os dois valores
    if (diff < 0) diff = -diff;     // Valor absoluto (sempre positivo)
    return (diff == 1);             // Apenas é jogável se a diferença for exatamente 1
}