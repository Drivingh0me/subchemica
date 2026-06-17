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
    // char callback_str[256];

    // /* White space count */
    // int ws_count = 0;
    // int ws_index[128];
    //
    // /* Words */
    // int word_index[128];
    //
    // /* Find ws_count and ws_index */
    // while (buffer[i] != '\0' && ws_count < 126) {
    //     if (buffer[i] == ' ') {
    //         ws_index[ws_count] = i;
    //         ws_count++;
    //     }
    //     i++;
    // }
    // ws_index[ws_count] = -1;
    //
    // /* This ain't right ----------------------- */
    // if (buffer[0] < 32) {
    //     word_index[0] = 0;
    // }
    //
    // for (i = 0; i < ws_count; i++) {
    //     word_index[i] = ws_index[i]
    //     word_index[i] = ws_index[i - 1] + 1;
    // }
    //
    // for (i = 0; i <= ws_count; i++) {
    //     printf("i:%d, word index:%d", i, word_index[i]);
    // }
    // /* ----------- */

    /* needs to be easy to add calls and still be fast
    * needs to loop through to check for all commands
    * and pass strings to calls
    * while *buffer != '\n' {};
    * Consider command(str) to pass to command
    * Consider detect key '\' to start newline without interupting buffer.
    */
    int words[128];
    int word_index = 0;
    int prev_char_ws = 1;

    while (buffer[i] != '\0') {
        if (prev_char_ws) {
            if (buffer[i] > 32) {
                words[word_index] = i;
                word_index++;
                prev_char_ws = 0;
            } else {
                prev_char_ws = 1;
            }
        }
        i++;
    }

    for (i = 0; i < word_index; i++) {
        if (same_word(buffer + words[i], "echo")) {
            printf("it's echo\n");
            /* Determine how much str to give func */
            i++;
            status = tools.func[ECHO](buffer + words[i]);
            if (status) {
                return status;
            }
        } else {
            printf("not echo\n");
            printf("str: %s", buffer  + words[i]);
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
    }
    return 0;
}
