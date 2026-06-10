#include "error.h"

#include "interpreter.h"

#include <stdio.h>
#include <stdlib.h>

/* Does not cleanup, just reports error */
void app_err(int errno)
{
    if (errno < 0) {
        /* Uses ANSI escape sequence to color error message. */
        printf(REDBOLD "FATAL ERROR: %d" RESET "\n", errno);
        exit(errno);
    } else {
        printf(REDBOLD "RECOVERABLE ERROR: %d BECAME FATAL.\n" RESET
               "This is likely a bug.\n", errno);
        exit(errno);
    }
}

void add_err_msg(ErrorState errSt, char *str)
{
    int i = 0;

    while (str[i] != '\0' && i < ERR_MSG_LEN_MAX) {
        errSt.errMsg[i] = str[i];
        i++;
    }
}
