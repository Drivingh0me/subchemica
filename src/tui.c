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

void append_char(char c, char *buffer, int *index)
{
    buffer[*index] = c;
    (*index)++;
}

void append_string(char *s, char *buffer, int *index)
{
    int i = 0;
    while (s[i] != 0) {
        append_char(s[i], buffer, index);
        i++;
    }
}

int tui_engine(char c, Screen *screen, TermSize term)
{
    int format_chars = 25;
    int buffer_index = 0;

    screen->length = term.rows * term.cols + format_chars;
    screen->buffer = malloc(screen->length * sizeof(char));
    if (screen->buffer == 0) {
        return -1;
    }
    screen->capacity = screen->length;

    for (int i = 0; i < term.rows; i++) {
        if (i == term.rows - 1) {
            append_string(RED, screen->buffer, &buffer_index);
        }
        for (int j = 0; j < term.cols; j++) {
            append_char(c, screen->buffer, &buffer_index);
        }
        if (i == term.rows - 1) {
            append_string(RESET, screen->buffer, &buffer_index);
        }
    }
    screen->buffer[buffer_index] = 0;
    buffer_index++;

    return 0;
}

void run_tui(Toolset tools)
{
    TermSize termsize;
    int tuiShouldRun = 1;
    Screen screen;
    char c;
    int err;

    c = 0;

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
        TARG_get_term_size(&termsize);
        printf(CLEAR);
        printf(CURSOR_HOME);

        err = tui_engine(c, &screen, termsize);
        if (err != 0) {
            tuiShouldRun = 0;
            goto tui_engine_err;
        }

        printf(screen.buffer);
        fflush(stdout);
        err = read(STDIN_FILENO, &c, 1);
        if (err != 1 || c == 27) {
            tuiShouldRun = 0;
        }

    tui_engine_err:
        free(screen.buffer);
        screen.buffer = NULL;
    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
    printf(NORM_SCREEN);
}
