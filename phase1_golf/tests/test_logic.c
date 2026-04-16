#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/logic/card.h"
#include "../src/logic/deck.h"
#include "../src/logic/pile.h"
#include "../src/logic/game.h"

// ---- CARD ---- //

void test_createCard(void) {
    Card c = createCard(7, HEARTS);
    CU_ASSERT_EQUAL(c.value, 7);      // valor guardado corretamente
    CU_ASSERT_EQUAL(c.suit, HEARTS);  // naipe guardado corretamente
}

void test_cardIsPlayable_valid(void) {
    Card top = createCard(5, HEARTS);
    Card c1  = createCard(6, SPADES); // 5→6 válido
    Card c2  = createCard(4, CLUBS);  // 5→4 válido
    CU_ASSERT_TRUE(cardIsPlayable(top, c1));
    CU_ASSERT_TRUE(cardIsPlayable(top, c2));
}

void test_cardIsPlayable_invalid(void) {
    Card top = createCard(5, HEARTS);
    Card c1  = createCard(7, SPADES); // 5→7 inválido (diff=2)
    Card c2  = createCard(1, CLUBS);  // A→K NÃO é adjacente neste Golf
    Card king = createCard(13, CLUBS);
    CU_ASSERT_FALSE(cardIsPlayable(top, c1));
    CU_ASSERT_FALSE(cardIsPlayable(createCard(1,CLUBS), king)); // A↔K inválido
}

// ---- DECK ---- //

void test_deckInit(void) {
    Deck d;
    deckInit(&d);
    CU_ASSERT_EQUAL(d.top, 0);         // começa no início
    CU_ASSERT_FALSE(deckIsEmpty(&d));   // não está vazio
    CU_ASSERT_EQUAL(d.cards[0].value, 1);            // primeiro: Ás de Paus
    CU_ASSERT_EQUAL(d.cards[0].suit,  CLUBS);
    CU_ASSERT_EQUAL(d.cards[51].value, 13);           // último: Rei de Espadas
    CU_ASSERT_EQUAL(d.cards[51].suit,  SPADES);
}

void test_deckDraw(void) {
    Deck d;
    deckInit(&d);
    Card out;
    CU_ASSERT_TRUE(deckDraw(&d, &out)); // conseguiu tirar carta
    CU_ASSERT_EQUAL(d.top, 1);          // top avançou
    CU_ASSERT_EQUAL(out.value, 1);      // era o Ás de Paus
}

void test_deckIsEmpty(void) {
    Deck d;
    deckInit(&d);
    d.top = DECK_SIZE;                  // simula baralho esgotado
    CU_ASSERT_TRUE(deckIsEmpty(&d));
    Card out;
    CU_ASSERT_FALSE(deckDraw(&d, &out)); // não consegue tirar carta
}

// ---- PILE ---- //

void test_pileInit(void) {
    Pile p;
    pileInit(&p);
    CU_ASSERT_EQUAL(p.size, 0);       // começa vazia
    CU_ASSERT_TRUE(pileIsEmpty(&p));  // confirmado por pileIsEmpty
}

void test_pilePushPop(void) {
    Pile p;
    pileInit(&p);
    Card c = createCard(7, HEARTS);
    CU_ASSERT_TRUE(pilePush(&p, c));   // push com sucesso
    CU_ASSERT_EQUAL(p.size, 1);        // tamanho aumentou
    Card out;
    CU_ASSERT_TRUE(pilePop(&p, &out)); // pop com sucesso
    CU_ASSERT_EQUAL(out.value, 7);     // era o 7 de Copas
    CU_ASSERT_TRUE(pileIsEmpty(&p));   // pilha voltou a ficar vazia
}

void test_pileTop(void) {
    Pile p;
    pileInit(&p);
    Card c1 = createCard(3, CLUBS);
    Card c2 = createCard(9, DIAMONDS);
    pilePush(&p, c1);
    pilePush(&p, c2);
    Card top = pileTop(&p);
    CU_ASSERT_EQUAL(top.value, 9);     // topo é o último que entrou
    CU_ASSERT_EQUAL(p.size, 2);        // pileTop não remove a carta
}

// ---- GAME ---- //

void test_gameInit(void) {
    GameState g;
    gameInit(&g);
    for (int i = 0; i < NUM_PILES; i++)
    CU_ASSERT_EQUAL(g.tableu[i].size, 5); // cada pilha tem 5 cartas
    CU_ASSERT_EQUAL(g.deck.top, 36);          // 35 distribuídas + 1 descarte
    CU_ASSERT_TRUE(g.discard.size > 0);           // existe carta no descarte
}

void test_gameIsOver_false(void) {
    GameState g;
    gameInit(&g);
    CU_ASSERT_FALSE(gameIsOver(&g)); // jogo começa sem estar terminado
}

void test_gameIsOver_true(void) {
    GameState g;
    gameInit(&g);
    for (int i = 0; i < NUM_PILES; i++)
        g.tableu[i].size = 0;         // esvazia todas as pilhas manualmente
    CU_ASSERT_TRUE(gameIsOver(&g));  // agora está terminado
}

// ---- MAIN DOS TESTES ---- //

int main(void) {
    CU_initialize_registry();

    CU_pSuite sCard = CU_add_suite("Card", NULL, NULL);
    CU_add_test(sCard, "createCard",             test_createCard);
    CU_add_test(sCard, "cardIsPlayable válido",  test_cardIsPlayable_valid);
    CU_add_test(sCard, "cardIsPlayable inválido",test_cardIsPlayable_invalid);

    CU_pSuite sDeck = CU_add_suite("Deck", NULL, NULL);
    CU_add_test(sDeck, "deckInit",    test_deckInit);
    CU_add_test(sDeck, "deckDraw",    test_deckDraw);
    CU_add_test(sDeck, "deckIsEmpty", test_deckIsEmpty);

    CU_pSuite sPile = CU_add_suite("Pile", NULL, NULL);
    CU_add_test(sPile, "pileInit",    test_pileInit);
    CU_add_test(sPile, "pilePushPop", test_pilePushPop);
    CU_add_test(sPile, "pileTop",     test_pileTop);

    CU_pSuite sGame = CU_add_suite("Game", NULL, NULL);
    CU_add_test(sGame, "gameInit",       test_gameInit);
    CU_add_test(sGame, "gameIsOver false",test_gameIsOver_false);
    CU_add_test(sGame, "gameIsOver true", test_gameIsOver_true);

    CU_basic_set_mode(CU_BRM_VERBOSE); // mostra detalhes de cada teste
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}