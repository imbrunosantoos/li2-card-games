CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Ficheiros da lógica
LOGIC = src/logic/card.c src/logic/deck.c \
        src/logic/pile.c src/logic/game.c

# Ficheiros da interface
UI    = src/ui/display.c src/ui/input.c

all: golf

# Compila o jogo completo
golf: $(LOGIC) $(UI) src/main.c
	$(CC) $(CFLAGS) -o golf $(LOGIC) $(UI) src/main.c

# Compila e corre os testes CUnit
test: tests/test_logic.c $(LOGIC)
	$(CC) $(CFLAGS) -o tests/test_logic tests/test_logic.c $(LOGIC) -lcunit
	./tests/test_logic

# Verifica complexidade ciclomática (regra: máx 10, máx 15 instruções)
pmccabe:
	pmccabe -v src/logic/*.c src/ui/*.c src/main.c

clean:
	rm -f golf tests/test_logic