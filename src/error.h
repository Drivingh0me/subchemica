#ifndef ERROR_H
#define ERROR_H

#include "interpreter.h"

#define ERR_MSG_LEN_MAX 128

/* enum and union for global error types of int */
typedef enum {
    MEM_ALLOC,
    IO,
    INVALID_ARG
} Error;

/* Last error state gets printed */
typedef struct {
    int err;
    char errMsg[ERR_MSG_LEN_MAX];
} ErrorState;

/* Does not cleanup, just reports error */
void app_err(int errno, ErrorState errState);
void add_err_msg(ErrorState errSt, char *str);

#endif /* ERROR_H */
