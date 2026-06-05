#include <target.h>

#include <sys/ioctl.h>

void TARG_get_term_size(int *rows, int *cols)
{
    struct winsize w;

    if (!ioctl(0, TIOCGWINSZ, &w)) {
        *rows = w.ws_row;
        *cols = w.sw_col;
    } else {
        *rows = -1;
        *cols = -1;
    }
}
