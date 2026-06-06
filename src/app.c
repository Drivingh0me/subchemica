#include "app.h"

#include "math.h"
#include "export.h"
#include "tui.h"

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

/* argsparse
 * The flags array is an int of each flag given in order.
 * The args array is the start then end index of argv given to each flag
 * in same order as flags.
 * EX:
 * flags[0] is open file.
 * args[0] is first argv index passed (-1 if none)
 * and args[1] is index of last arg given to open file.
*/
typedef struct {
    int* flags;
    int* args;
} argsparse;

static void cleanup()
{
    printf("Cleaning up.\n");
}

int function1(int a)
{
    printf("Function%d ran.\n", a);
    return 0;
}

int function2(int a)
{
    printf("Function%d ran.\n", a);
    return 0;
}

void app_err(int errno)
{
    if (errno < 0) {
        /* Uses ANSI escape sequence to color error message. */
        printf(REDBOLD "FATAL ERROR: %d" RESET "\n", errno);
        cleanup();
        exit(errno);
    } else {
        printf(REDBOLD "RECOVERABLE ERROR: %d BECAME FATAL.\n" RESET
               "This is likely a bug.\n", errno);
        cleanup();
        exit(errno);
    }
}

/* FLAGS:
 * -t/--tui: Run TUI
 * -l/--load: Load a file or directory
*/
static void parse_args(int argc, char **argv, int *runTui)
{
    *runTui = 0;
    if (argc == 1) {
        *runTui = 1;
    }

    if (argc > 1) {
        if (argv[2][0] == '-') {
            if (argv[2][1] == 't') {
                *runTui = 1;
            }
        }
    }
}

static void export()
{
    printf("Exporting.\n");
}

static int run_analysis(Dataset data)
{
    char should_export = 0;
    int status;

    if (should_export) {
        export();
    }

    // status = fit();
    // if (status) {
    //     return 3;
    // }

    return 0;
}

static int coalesce_data(Dataset *dataset)
{
    printf("Coalescing data.\n");

    return 0;
}

int app_startup(SystemInfo *sysInfo)
{
    /* Check system info. */
    return 0;
}

int run_app(int argc, char **argv, SystemInfo *sysInfo)
{
    int status;
    int runTui;
    Dataset dataset;
    Toolset tools;

    tools.func[COALESCE] = function1;
    tools.func[ANALYSIS] = function2;

    parse_args(argc, argv, &runTui);

    if (runTui) {
        run_tui(tools);
    }

    return 0;
}

void app_shutdown(SystemInfo sysInfo)
{
    cleanup();
}
