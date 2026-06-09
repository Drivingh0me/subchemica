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

int TARG_mem_limit(int *memory)
{
    *memory = 0;
    return 0;
}
