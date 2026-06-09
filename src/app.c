#include "app.h"

#include "compute.h"
#include "export.h"
#include "tui.h"
#include "interpreter.h"
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
    int flags[32];
    int args[64];
} ArgParse;

static void cleanup()
{
    printf("Cleaning up.\n");
}

int function1(char *str)
{
    printf("Function1 ran. %s\n", str);
    return 0;
}

int function2(char *str)
{
    printf("Function2 ran. %s\n", str);
    return 0;
}

/* Do not cleanup, just report error */
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

/* FLAGS:
 * -t/--tui: Run TUI
 * -l/--load: Load a file or directory
*/
static void parse_args(int argc, char **argv, ArgParse *args)
{
    int i = 0;

    if (argc <= 1) {
        args->flags[0] = 4;
        args->flags[1] = 0;
        return;
    }

    for (i < argc; i++) {
        if (argv[0] == '-') {
            get_flag(that);
            continue;
            /* check for "--" */
        }

        append_flag_arg(i);
    }

    // if (argv[2][0] == '-') {
    //     if (argv[2][1] == 't') {
    //         *runInterpreter = 1;
    //     }
    // }
}

int app_startup(SystemInfo *sysInfo)
{
    /* Check system info. */
    /* Cleanup here with sysinfo if error */
    /* Consider impl a lite argparse into here so that sysinfo doesn't
     * have to be filled if not needed.
     * impl:
     * --version, -v
     * -- help, -h
     * -s, --system (do not get system info)
     * OS upon --version.
     */
    int mem;
    int status;

    status = TARG_mem_limit(&mem);

    return 0;
}

int run_app(int argc, char **argv, SystemInfo *sysInfo)
{
    int status;
    int runInterpreter;
    ArgParse args;
    // Dataset dataset;
    Toolset tools;

    tools.func[COALESCE] = function1;
    tools.func[ANALYSIS] = function2;

    parse_args(argc, argv, &args);

    if (runInterpreter) {
        run_interpreter(tools);
    }
    /* Cleanup here with sysinfo if error */

    return 0;
}

void app_shutdown(SystemInfo *sysInfo)
{
    /* Free all memory used by main run */
    cleanup();
}
