#include "tui.h"
#include <target.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printxt(char* str, int len)
{
    fwrite(str, 1, len, stdout);
}

void throw_err(int err)
{
    printf(REDBOLD "Error: %d" RESET, err);
}

static int same_word(char* sample, char *key)
{
    int i = 0;
    while (key[i] != '\n') {
        if (sample[i] != key[i] || sample[i] == '\n') {
            return 0;
        }
        i++;
    }
    return 1;
}

static int exact_command(char* sample, char *key)
{
    int i = 0;
    while (key[i] != '\n') {
        if (sample[i] != key[i] || sample[i] == '\n') {
            return 0;
        }
        i++;
    }
    if (sample[i] != '\n') {
        return 0;
    }
    return 1;
}

int interpreter_parse(char* buffer)
{
    /* needs to be easy to add calls and still be fast */
    /* while *buffer != '\n' {}; */

    return 0;
}

void run_tui(Toolset tools)
{
    int termRows;
    int termCols;

    // enum Command req[12];
    // unsigned short numReq = 0;
    // char paths[20];
    // unsigned short numPaths = 0;

    int tuiShouldRun = 1;
    char buffer[80];
    char *a;
    int waste;

    printf("subchemica V0.1.1\nAangstrom interpreter running.\n");
    while (tuiShouldRun) {
        TARG_get_term_size(&termRows, &termCols);
        /* Prints "> " in blue */
        printxt(INT_NEWLN, 11);

        /* MUST MATCH CASES */
        /* Cases to close interpreter */
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

        /* ITERATED CASES */
        /* Operator and tool calls */
        waste = interpreter_parse(buffer);
        if (waste) {
            throw_err(waste);
        }

        if (same_word(buffer, "func1\n")) {
            /* Deetermine how much str to give func */
            waste = tools.func[COALESCE](buffer);
            if (waste) {
                throw_err(waste);
            }
        }

        if (same_word(buffer, "func2\n")) {
            waste = tools.func[ANALYSIS](buffer);
            if (waste) {
                throw_err(waste);
            }
        }
    }
}
