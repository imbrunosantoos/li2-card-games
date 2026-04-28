#include "input.h"
#include <stdio.h>
#include <ctype.h>

static Command charToCommand(char c) {
    if (c >= '1' && c <= '7') {
        return (Command)(CMD_PILE_1 + (c - '1'));
    }
    if (c == 'd' || c == 'D') return CMD_DRAW;
    if (c == 'q' || c == 'Q') return CMD_QUIT;
    return CMD_INVALID;
}

Command inputRead(void) {
    char buf[16];

    printf("O teu comando: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return CMD_QUIT;

    return charToCommand(buf[0]);
}
