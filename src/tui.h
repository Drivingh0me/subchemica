#ifndef TUI_H
#define TUI_H

#include "interpreter.h"

void run_tui(Toolset tools);

#define ALT_SCREEN "\033[?1049h"
#define NORM_SCREEN "\033[?1049l"

#endif /* TUI_H */
