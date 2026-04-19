#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../common/card.h"
#include "../common/deck.h"
#include "../common/pile.h"
#include "../phase1_golf/src/logic/game.h"
#include "../phase2_simon/src/logic/game.h"

// ========== TESTES GOLF (PHASE 1) ==========

void test_golf_cardIsPlayable_valid(void) {
    Card top = createCard(5, HEARTS);
    Card c1 = createCard(6, SPADES);
    Card c2 = createCard(4, CLUBS);
    CU_ASSERT_TRUE(cardIsPlayable(top, c1));
    CU_ASSERT_TRUE(cardIsPlayable(top, c2));
}

void test_golf_deckInit(void) {
    Deck d;
    deckInit(&d);
    CU_ASSERT_EQUAL(d.top, 0);
    CU_ASSERT_FALSE(deckIsEmpty(&d));
}

void test_golf_pilePushPop(void) {
    Pile p;
    pileInit(&p);
    Card c = createCard(7, HEARTS);
    CU_ASSERT_TRUE(pilePush(&p, c));
    Card out;
    CU_ASSERT_TRUE(pilePop(&p, &out));
    CU_ASSERT_EQUAL(out.value, 7);
}

void test_golf_gameInit(void) {
    GameState g;
    gameInit(&g);
    for (int i = 0; i < NUM_PILES; i++)
        CU_ASSERT_EQUAL(g.tableu[i].size, 5);
}

// ========== TESTES SIMON (PHASE 2) ==========

void test_simon_init(void) {
    SimonState s;
    simonInit(&s);
    
    int total_cartas = 0;
    for (int i = 0; i < 10; i++) {
        total_cartas += s.columns[i].size;
    }
    CU_ASSERT(total_cartas > 0);
}

void test_simon_move_valid(void) {
    SimonState s;
    simonInit(&s);
    
    int resultado = simonMove(&s, 0, 5);
    CU_ASSERT(resultado == 0 || resultado == 1);
}

void test_simon_is_over_false(void) {
    SimonState s;
    simonInit(&s);
    
    int resultado = simonIsOver(&s);
    CU_ASSERT(resultado == 0);
}

void test_simon_pileSequenceSize(void) {
    Pile p;
    pileInit(&p);
    Card c1 = createCard(8, HEARTS);
    Card c2 = createCard(7, HEARTS);
    pilePush(&p, c1);
    pilePush(&p, c2);
    
    int seq = pileSequenceSize(&p);
    CU_ASSERT_EQUAL(seq, 2);
}

// ========== MAIN ==========

int main(void) {
    CU_initialize_registry();

    // Suite do Golf
    CU_pSuite sGolf = CU_add_suite("GOLF (Phase 1)", NULL, NULL);
    CU_add_test(sGolf, "cardIsPlayable", test_golf_cardIsPlayable_valid);
    CU_add_test(sGolf, "deckInit", test_golf_deckInit);
    CU_add_test(sGolf, "pilePushPop", test_golf_pilePushPop);
    CU_add_test(sGolf, "gameInit", test_golf_gameInit);

    // Suite do Simon
    CU_pSuite sSimon = CU_add_suite("SIMON (Phase 2)", NULL, NULL);
    CU_add_test(sSimon, "simonInit", test_simon_init);
    CU_add_test(sSimon, "simonMove", test_simon_move_valid);
    CU_add_test(sSimon, "simonIsOver", test_simon_is_over_false);
    CU_add_test(sSimon, "pileSequenceSize", test_simon_pileSequenceSize);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}