#include "tui.h"

#include "interpreter.h"
#include <target.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void run_tui(Toolset tools)
{
    int termRows;
    int termCols;
    int tuiShouldRun = 1;
    char buffer[256];
    char *a;
    int waste;

    /* Vim-like with ':' to start a command */
    while (tuiShouldRun) {
        TARG_get_term_size(&termRows, &termCols);
        printf(CLEAR CURSOR_HOME);
        printxt(INT_NEWLN, 11);

        a = fgets(buffer, sizeof(buffer), stdin);
        if (a != buffer) {
            tuiShouldRun = 0;
        }

        if (exact_command(buffer, "quit\n")) {
            tuiShouldRun = 0;
        }

        if (exact_command(buffer, "clear\n")) {
            printf(CLEAR CURSOR_HOME);
        }
    }
}
