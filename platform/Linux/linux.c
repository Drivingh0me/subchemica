#include <target.h>
#include <sys/ioctl.h>

void TARG_get_term_size(int *rows, int *cols)
{
    struct winsize w;
    if (!ioctl(0, TIOCGWINSZ, &w)) {
        *rows = w.ws_row;
        *cols = w.ws_col;
    } else {
        *rows = -1;
        *cols = -1;
    }
}

/* Replace with reading proc/meminfo for MemAvailable and CommitLimit
 * to etermine how "hard" the app runs with sysInfo.
 */
int TARG_mem_limit(int *memory)
{
    struct rlimit limit;

    if (!getrlimit(RLIMIT_AS, &limit)) {
        if (limit.rlim_cur == RLIM_INFINITY) {
            memory = -1;
            return 0;
        } else {
            memory = limit.rlim_cur / 1000;
            return 0;
        }
    } else {
        return -1;
    }
}
