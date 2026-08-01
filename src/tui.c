#include "tui.h"

#include "interpreter.h"
#include <target.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Temporary */
#include <termios.h>
#include <unistd.h>

void run_tui(Toolset tools)
{
    int termRows;
    int termCols;
    int tuiShouldRun = 1;
    char buffer[256];
    char c;
    int err;

    printf(ALT_SCREEN);
    fflush(stdout);

    /* Pull into function and targ */
    struct termios orig;
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig);
    raw = orig;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    /* Vim-like with ':' to start a command */
    while (tuiShouldRun) {
        TARG_get_term_size(&termRows, &termCols);
        printf(CLEAR);
        fflush(stdout);
        printf(CURSOR_HOME);
        printf("%c", c);
        fflush(stdout);
        err = read(STDIN_FILENO, &c, 1);
        if (err != 1 || c == 'q') {
            tuiShouldRun = 0;
        }


    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
    printf(NORM_SCREEN);
}
