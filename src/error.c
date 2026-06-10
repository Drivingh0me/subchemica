#include "error.h"

#include "interpreter.h"

#include <stdio.h>
#include <stdlib.h>

void print_err(Error err)
{
    switch (err) {
        case MEM_ALLOC:
        printf("Memory allocation failed\n");
        break;
        case IO:
        printf("IO error\n");
        break;
        case INVALID_ARG:
        printf("Invalid argument\n");
        break;
        case INVALID_VAL:
        printf("Invalid value\n");
        break;
        case EMPTY_ARG:
        printf("Empty argument\n");
        break;
    }
}

/* Does not cleanup, just reports error */
void app_err(Error err)
{
    if (err < 0) {
        /* Uses ANSI escape sequence to color error message. */
        printf(REDBOLD "FATAL ERROR: %d" RESET "\n", err);
        print_err(err);
    } else {
        printf(REDBOLD "RECOVERABLE ERROR: %d BECAME FATAL.\n" RESET
               "This is likely a bug.\n", err);
        print_err(err);
    }
}

void fatal_err(Error err)
{
    /* Uses ANSI escape sequence to color error message. */
    printf(REDBOLD "UNRECOVERABLE ERROR: %d" RESET "\n", err);
    exit(err);
}

// void add_err_msg(ErrorState errSt, char *str)
// {
//     int i = 0;
//
//     while (str[i] != '\0' && i < ERR_MSG_LEN_MAX) {
//         errSt.errMsg[i] = str[i];
//         i++;
//     }
// }
//
// void throw_err(int err)
// {
//     printf(REDBOLD "Error: %d" RESET, err);
// }
