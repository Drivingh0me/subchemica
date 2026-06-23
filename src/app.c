#include "app.h"

#include "compute.h"
#include "export.h"
#include "tui.h"
#include "interpreter.h"
#include "error.h"
#include <target.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int length;
    int lines;
    double *data;
} Data;

typedef struct {
    int sets;
    Data *data_arr;
} Dataset;

#define ARG_MAX 64
#define VERSION "subchemica v0.1.1 (pre-alpha)\n"

/* argsparse
 * The flags array is an int of each flag given in order.
 * The args array is the start then end index of argv given to each flag
 * in same order as flags.
 * 0 is last flag.
 * EX:
 * flags[0] is open file.
 * args[0] is first argv index passed (-1 if none)
 * and args[1] is index of last arg given to open file.
 * flags:
 * -d/--debug 1
 * -f/--file 2 (takes args)
 * -t/--tui 3
 * -i/--interpreter 4
*/
typedef struct {
    int flag[ARG_MAX];
    int arg[2 * ARG_MAX];
} ArgParse;

static void cleanup()
{
    // printf("Cleaning up.\n");
}

int tool_echo(char *str)
{
    printf(GREEN "> " RESET "%s", str);
    return 0;
}

int function2(char *str)
{
    printf("I say: %s\n", str);
    return 0;
}

int get_short_flag(char c)
{
    switch (c) {
        case 'd':
            return 1;
        case 'f':
            return 2;
        case 't':
            return 3;
        case 'i':
            return 4;
        default:
            return INVALID_ARG;
    }
}

/* Not implemented */
int get_long_flag(char *c)
{
    if (exact_command(c, "--silent")) {
        return 9;
    }
}

static void parse_args(int argc, char **argv, ArgParse *args)
{
    int i;
    int x = 0;

    if (argc <= 1) {
        /* If no args, run interpreter */
        args->flag[0] = 4;
        args->flag[1] = 0;
        return;
    }

    /* Check for --version and --help explicitely */
    if (argc == 2) {
        if (exact_command(argv[1], "--version")) {
            printf(VERSION);
            args->flag[0] = 0;
            return;
        }

        if (exact_command(argv[1], "--help")) {
            printf("Help not implemented\n");
            args->flag[0] = 0;
            return;
        }
    }

    for (i = 1; i < argc && x < ARG_MAX; i++) {
        if (argv[i][0] == '-') {
            /* Check for --long */
            if (argv[i][1] == '-') {
                args->flag[x] = get_long_flag(argv[i]);
            }
            args->flag[x] = get_short_flag(argv[i][1]);
            args->arg[2 * x] = i + 1;
            if (x > 0) {
                args->arg[2 * x - 1] = i - 1;
            }

            if (args->flag[x] == INVALID_ARG) {
                /* Not a flag, error */
                args->flag[0] = INVALID_ARG;
                args->flag[1] = 0;
            }

            x++;
        }
    }

    /* terminates flag */
    args->flag[x] = 0;

    /* Set previous arg to end */
    if (x > 0) {
        args->arg[2 * x - 1] = i - 1;
    }
}

int execute_args(ArgParse args, char **argv)
{
    int i = 0;
    int status = 0;

    Toolset tools;
    tools.func[ECHO] = tool_echo;
    tools.func[SAY] = function2;

    while (args.flag[i] > 0) {
        /* must match args */
        switch (args.flag[i]) {
            case 1:
                /* debug */
                break;
            case 2:
                /* file */
                break;
            case 3:
                /* TUI */
                break;
            case 4:
                /* Interpreter */
                status = run_interpreter(tools);
                if (status) {goto Cleanup;}
                break;
            case 9:
                /* silent */
                break;
            default:
                return INVALID_VAL;
        }
        i++;
    }
    return 0;

/* Goto is chiasm form */
Cleanup:
    cleanup();
    return status;
}

/* Not implemented */
int app_startup(SystemInfo *sysInfo)
{
    /* Check system info.
     * Cleanup here with sysinfo if error
     */
    int mem;
    int status;

    // sysInfo->errorState.err = 0;
    // add_err_msg(sysInfo->errorState.errMsg, "No Error");

    status = TARG_mem_limit(&mem);

    return 0;
}

int run_app(int argc, char **argv, SystemInfo *sysInfo)
{
    ArgParse args;

    parse_args(argc, argv, &args);
    if (args.flag[0] <= 0) {
        return args.flag[0];
    }

    return execute_args(args, argv);
}

void app_shutdown(SystemInfo *sysInfo)
{
    /* Free all memory and files */
    cleanup();
}
