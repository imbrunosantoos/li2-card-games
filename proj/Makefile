all:
	gcc -o cardgames \
		main.c \
		phase3/src/logic/parser.c \
		phase3/src/logic/engine.c \
		phase3/src/logic/moviment.c \
		phase3/src/logic/game.c \
		phase3/src/logic/saveload.c \
		phase3/src/ui/menu.c \
		phase3/src/ui/display.c \
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
		phase2_simon/src/jogar_simon.c \
		-I./common \
		-I./phase1_golf/src/logic \
		-I./phase1_golf/src/ui \
		-I./phase2_simon/src/logic \
		-I./phase2_simon/src/ui \
		-I./phase3/src/logic \
		-I./phase3/src/ui

test:
	gcc -o test \
		tests/test_logic.c \
		common/card.c \
		common/deck.c \
		common/pile.c \
		phase1_golf/src/logic/game.c \
		phase2_simon/src/logic/game.c \
		phase3/src/logic/parser.c \
		phase3/src/logic/engine.c \
		phase3/src/logic/moviment.c \
		-I./common \
		-I./phase1_golf/src/logic \
		-I./phase2_simon/src/logic \
		-I./phase3/src/logic \
		-I/opt/homebrew/Cellar/cunit/2.1-3/include \
		-L/opt/homebrew/Cellar/cunit/2.1-3/lib \
		-lcunit
	./test

pmccabe:
	pmccabe \
		common/card.c \
		common/deck.c \
		common/pile.c \
		phase1_golf/src/logic/game.c \
		phase1_golf/src/ui/display.c \
		phase1_golf/src/ui/input.c \
		phase2_simon/src/logic/game.c \
		phase2_simon/src/ui/display.c \
		phase2_simon/src/ui/input.c \
		phase3/src/logic/parser.c \
		phase3/src/logic/engine.c \
		phase3/src/logic/moviment.c \
		phase3/src/logic/game.c \
		phase3/src/logic/saveload.c \
		phase3/src/ui/display.c \
		phase3/src/ui/menu.c

clean:
	rm -f cardgames test