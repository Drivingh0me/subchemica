#ifndef TARGET_H
#define TARGET_H

typedef struct {
    int rows;
    int cols;
} TermSize;

void TARG_get_term_size(TermSize *t);
int TARG_mem_limit(int *memory);

#endif /* TARGET_H */
