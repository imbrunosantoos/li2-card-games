#ifndef CARD_H
#define CARD_H


// Os 4 naipes das cartas com o nome Suit para chamar
typedef enum {
    CLUBS, // Paus
    DIAMONDS, // Ouros
    HEARTS, // Copas
    SPADES // Espadas
} Suit;


// Cada carta possui um valor e um naipe
typedef struct {
    int value; // Valor de 1 a 13 
    Suit suit; // O respetivo naipe
} Card;

// Função que cria uma carta com um valor e um naipe
Card createCard(int value, Suit suit);

// Verifica se uma carta pode ser jogada em cima de outra
int cardIsPlayable(Card top, Card c);

#endif