#include "interpreter.h"
#include <target.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* REPL - Read Eval Print Loop */

void printxt(char* str, int len)
{
    fwrite(str, 1, len, stdout);
}

int same_word(char* sample, char *key)
{
    int i = 0;
    while (key[i] != '\0') {
        if (sample[i] != key[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

int exact_command(char* sample, char *key)
{
    int i = 0;
    while (key[i] != '\0') {
        if (sample[i] != key[i]) {
            return 0;
        }
        i++;
    }
    if (sample[i] != '\0') {
        return 0;
    }
    return 1;
}

static int interpreter_parse(char* buffer, Toolset tools)
{
    int status = 0;
    int i = 0;
    char callback_str[256];

    /* White space count */
    int ws_count = 0;
    int ws_index[128];

    while (buffer[i] != '\0') {
        if (buffer[i] == ' ' || buffer[i] == '\\') {
            ws_index[ws_count] = i;
            ws_count++;
        }
        i++;
    }

    /* needs to be easy to add calls and still be fast
    * needs to loop through to check for all commands
    * and pass strings to calls
    * while *buffer != '\n' {};
    * Consider command(str) to pass to command
    * Consider detect key '\' to start newline without interupting buffer.
    */

    for (i = 0; i < ws_count; i++) {
        if (same_word(buffer + ws_index[i] + 1, "echo")) {
            printf("it's echo\n");
            /* Determine how much str to give func */
            i++;
            status = tools.func[ECHO](buffer + ws_index[i] + 1);
            if (status) {
                return status;
            }
        } else {
            printf("not echo\n");
            printf("str: %s", buffer  + ws_index[i]);
        }
    }

    // if (same_word(buffer, "echo")) {
    //     /* Determine how much str to give func */
    //     status = tools.func[ECHO](buffer);
    //     if (status) {
    //         return status;
    //     }
    // }
    //
    if (same_word(buffer, "say")) {
        /* Determine how much str to give func */
        status = tools.func[SAY](buffer);
        if (status) {
            return status;
        }
    }

    return status;
}

int run_interpreter(Toolset tools)
{
    int termRows;
    int termCols;

    int interpreterShouldRun = 1;
    char buffer[256];
    char *a;
    int status;

    printf("subchemica V0.1.1\nAangstrom interpreter running.\n");
    while (interpreterShouldRun) {
        TARG_get_term_size(&termRows, &termCols);
        /* Prints "> " in blue */
        printxt(INT_NEWLN, 11);

        /* MUST MATCH CASES */
        /* Cases to close interpreter */
        a = fgets(buffer, sizeof(buffer), stdin);

        if (a != buffer) {
            interpreterShouldRun = 0;
        }

        if (exact_command(buffer, "quit\n")) {
            interpreterShouldRun = 0;
        }

        if (exact_command(buffer, "clear\n")) {
            printf(CLEAR CURSOR_HOME);
        }

        /* Add help */

        /* ITERATED CASES */
        /* Operator and tool calls */
        status = interpreter_parse(buffer, tools);
        if (status) {
            return status;
        }

        // if (same_word(buffer, "func1\n")) {
        //     /* Deetermine how much str to give func */
        //     status = tools.func[COALESCE](buffer);
        //     if (status) {
        //         return status;
        //     }
        // }
        //
        // if (same_word(buffer, "func2\n")) {
        //     status = tools.func[ANALYSIS](buffer);
        //     if (status) {
        //         return status;
        //     }
        // }
    }
    return 0;
}
