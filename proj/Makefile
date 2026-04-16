CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g \
         -I./common \
         -I./phase1_golf/src/logic \
         -I./phase1_golf/src/ui

COMMON = common/card.c common/deck.c common/pile.c

#Jogo da fase 1
GOLF = phase1_golf/src/logic/game.c \
       phase1_golf/src/ui/display.c \
       phase1_golf/src/ui/input.c \
       phase1_golf/src/main.c

all: golf

# Compila o jogo completo
golf: $(COMMON) $(GOLF)
	$(CC) $(CFLAGS) -o golf $(COMMON) $(GOLF)

# Compila e corre os testes CUnit
test: tests/test_logic.c $(COMMON) phase1_golf/src/logic/game.c
	$(CC) $(CFLAGS) -o tests/test_logic tests/test_logic.c $(COMMON) phase1_golf/src/logic/game.c -lcunit
	./tests/test_logic

# Verifica complexidade ciclomática (regra: máx 10, máx 15 instruções)
pmccabe:
	pmccabe -v common/*.c phase1_golf/src/logic/*.c phase1_golf/src/ui/*.c

clean:
	rm -f golf tests/test_logic