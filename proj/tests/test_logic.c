#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../common/card.h"
#include "../common/deck.h"
#include "../common/pile.h"
#include "../phase1_golf/src/logic/game.h"
#include "../phase2_simon/src/logic/game.h"
#include "../phase3/src/logic/parser.h"
#include "../phase3/src/logic/engine.h"
#include "../phase3/src/logic/moviment.h"


/* TESTES GOLF (PHASE 1) */

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

/* TESTES SIMON (PHASE 2) */

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

/* TESTES FASE 3 — parser */

/* testa se o nome do jogo e lido corretamente */
void test_parser_nome(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    CU_ASSERT_STRING_EQUAL(p.nome, "Golf");
}

/* testa se o numero de baralhos e lido */
void test_parser_numBaralhos(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    CU_ASSERT_EQUAL(p.numBaralhos, 1);
}

/* testa se os tipos de pilhas sao lidos */
void test_parser_tipos(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    CU_ASSERT(p.numTipos > 0);
}

/* testa se os movimentos sao lidos */
void test_parser_movimentos(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    CU_ASSERT(p.numMovimentos > 0);
}

/* testa se as condicoes de vitoria sao lidas */
void test_parser_vitorias(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    CU_ASSERT(p.numVitorias > 0);
}

/* TESTES FASE 3 — engine */

void test_parser_golf(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    CU_ASSERT(p.numPilhas > 0);
}

void test_criar_jogo(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    Jogo j;
    criarJogo(&j, &p);
    CU_ASSERT(j.numPilhas > 0);
}

/* testa que jogo nao ganho no inicio */
void test_jogoGanho_falso(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    Jogo j;
    criarJogo(&j, &p);
    CU_ASSERT_EQUAL(jogoGanho(&j), 0);
}

/* TESTES FASE 3 — moviment */

void test_mover_invalido(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    Jogo j;
    criarJogo(&j, &p);
    CU_ASSERT_EQUAL(tentarMover(&j, -1, 0, 1), 0);
}

/* testa um movimento valido: STOCK (indice 8) -> DESCARTE (indice 7) com flag * */
void test_tentarMover_stockParaDescarte(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    Jogo j;
    criarJogo(&j, &p);
    CU_ASSERT_EQUAL(tentarMover(&j, 8, 7, 1), 1);
}

/* testa que movimentos automaticos correm sem crash */
void test_executarAutomaticos_semCrash(void) {
    Paciencia p = parsePaciencia("paciencias/golf.paciencia");
    Jogo j;
    criarJogo(&j, &p);
    executarAutomaticos(&j);
    CU_ASSERT(j.numPilhas > 0);
}

/* MAIN */

int main(void) {
    CU_initialize_registry();

    /* Suite do Golf */
    CU_pSuite sGolf = CU_add_suite("GOLF (Phase 1)", NULL, NULL);
    CU_add_test(sGolf, "cardIsPlayable", test_golf_cardIsPlayable_valid);
    CU_add_test(sGolf, "deckInit", test_golf_deckInit);
    CU_add_test(sGolf, "pilePushPop", test_golf_pilePushPop);
    CU_add_test(sGolf, "gameInit", test_golf_gameInit);

    /* Suite do Simon */
    CU_pSuite sSimon = CU_add_suite("SIMON (Phase 2)", NULL, NULL);
    CU_add_test(sSimon, "simonInit", test_simon_init);
    CU_add_test(sSimon, "simonMove", test_simon_move_valid);
    CU_add_test(sSimon, "simonIsOver", test_simon_is_over_false);
    CU_add_test(sSimon, "pileSequenceSize", test_simon_pileSequenceSize);

    /* Suite do parser fase 3 */
    CU_pSuite sParser = CU_add_suite("PARSER (Phase 3)", NULL, NULL);
    CU_add_test(sParser, "nome", test_parser_nome);
    CU_add_test(sParser, "numBaralhos", test_parser_numBaralhos);
    CU_add_test(sParser, "tipos", test_parser_tipos);
    CU_add_test(sParser, "movimentos", test_parser_movimentos);
    CU_add_test(sParser, "vitorias", test_parser_vitorias);

    /* Suite do engine/moviment fase 3 */
    CU_pSuite sPhase3 = CU_add_suite("ENGINE (Phase 3)", NULL, NULL);
    CU_add_test(sPhase3, "parser golf", test_parser_golf);
    CU_add_test(sPhase3, "criar jogo", test_criar_jogo);
    CU_add_test(sPhase3, "jogo nao ganho no inicio", test_jogoGanho_falso);
    CU_add_test(sPhase3, "mover invalido", test_mover_invalido);
    CU_add_test(sPhase3, "mover STOCK->DESCARTE", test_tentarMover_stockParaDescarte);
    CU_add_test(sPhase3, "automaticos sem crash", test_executarAutomaticos_semCrash);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
