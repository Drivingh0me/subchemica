#include "tui.h"

#include "interpreter.h"
#include <target.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Temporary */
#include <termios.h>
#include <unistd.h>

typedef struct {
    int length;
    /* The len that has been malloc'd */
    int capacity;
    char *buffer;
} Screen;

typedef struct {
    int rows;
    int cols;
} TermSize;

int tui_engine(char c, Screen *screen, TermSize term)
{
    screen->length = term.rows * term.cols;
    screen->buffer = malloc(screen->length * sizeof(char));
    if (screen->buffer == 0) {
        return 1;
    }
    screen->capacity = screen->length;
    screen->buffer[0] = c;
    screen->buffer[1] = c + 1;
    screen->buffer[2] = 0;
    return 0;
}

void run_tui(Toolset tools)
{
    // int termRows;
    // int termCols;
    TermSize termsize;
    int tuiShouldRun = 1;
    Screen screen;
    char c;
    int err;

    c = ' ';

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
        TARG_get_term_size(&termsize.rows, &termsize.cols);
        printf(CLEAR);
        printf(CURSOR_HOME);

        err = tui_engine(c, &screen, termsize);
        printf(screen.buffer);
        fflush(stdout);
        err = read(STDIN_FILENO, &c, 1);
        if (err != 1 || c == 'q') {
            tuiShouldRun = 0;
        }
        free(screen.buffer);
        screen.buffer = NULL;
    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
    printf(NORM_SCREEN);
}
