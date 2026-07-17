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

    printf(ALT_SCREEN);
    /* Vim-like with ':' to start a command */
    while (tuiShouldRun) {
        TARG_get_term_size(&termRows, &termCols);

    }
    printf(NORM_SCREEN);
}
