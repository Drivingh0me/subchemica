#include <target.h>
#include <sys/ioctl.h>

void TARG_get_term_size(TermSize *t)
{
    struct winsize w;
    if (!ioctl(0, TIOCGWINSZ, &w)) {
        t->rows = w.ws_row;
        t->cols = w.ws_col;
    } else {
        t->rows = -1;
        t->cols = -1;
    }
}

int TARG_mem_limit(int *memory)
{
    *memory = 0;
    return 0;
}
