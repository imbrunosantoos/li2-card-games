CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g \
         -I./common \
         -I./phase1_golf/src/logic \
         -I./phase1_golf/src/ui \
         -I./phase2_simon/src/logic \
         -I./phase2_simon/src/ui \
         -I./menu_principal \
         -I/opt/homebrew/opt/cunit/include

LDFLAGS = -L/opt/homebrew/opt/cunit/lib -lcunit

COMMON = common/card.c common/deck.c common/pile.c

# Todos os ficheiros fonte para o programa completo
ALL_SRC = main.c \
          menu_principal/menu.c \
          common/card.c \
          common/deck.c \
          common/pile.c \
          phase1_golf/src/logic/game.c \
          phase1_golf/src/ui/display.c \
          phase1_golf/src/ui/input.c \
          phase1_golf/src/jogar_golf.c \
          phase2_simon/src/logic/game.c \
          phase2_simon/src/ui/display.c \
          phase2_simon/src/ui/input.c \
          phase2_simon/src/jogar_simon.c

all: cardgames

cardgames: $(ALL_SRC)
	$(CC) $(CFLAGS) -o cardgames $(ALL_SRC)

# Targets legacy (mantidos para compatibilidade)
golf: cardgames
simon: cardgames

# Compila testes
test: tests/test_logic.c $(COMMON) phase1_golf/src/logic/game.c phase2_simon/src/logic/game.c
	$(CC) $(CFLAGS) -o tests/test_logic tests/test_logic.c $(COMMON) phase1_golf/src/logic/game.c phase2_simon/src/logic/game.c $(LDFLAGS)
	./tests/test_logic

pmccabe:
	pmccabe -v common/*.c phase1_golf/src/logic/*.c phase1_golf/src/ui/*.c phase2_simon/src/logic/*.c phase2_simon/src/ui/*.c

clean:
	rm -f cardgames golf simon tests/test_logic

.PHONY: all golf simon test pmccabe clean