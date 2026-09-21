#include <stdio.h>
#include <stdlib.h>

#include "compute.h"

typedef struct {
    double *elements;
    int size;
    int capacity;
} VecDouble;

typedef struct {
    int *elements;
    int size;
    int capacity;
} VecInt;

/* Maybe make this u8 instead of char? */
typedef struct {
    char *elements;
    int size;
    int capacity;
} VecByte;

typedef struct {
    VecDouble matrix;
    int rows;
    int cols;
} MtxDouble;

typedef struct {
    VecDouble tens;
    VecInt shape;
} TensDouble;

/* Prints a VecDouble in scientific notation */
int print_vec(VecDouble v) {
    for (int i = 0; i < v.size; i++) {
        printf("%E", v.elements[i]);
    }
    return 0;
}

/* Append a single value onto a VecDouble. */
int append_VecDouble(VecDouble *v, double d) {
    if (v->size == v->capacity) {
        /* increase capacity */
        v->capacity = v->capacity * 2;
        v->elements = malloc(v->capacity * sizeof(*(v->elements)));
    }

    if (v->elements == NULL) {
        v->capacity = 0;
        v->size = 0;
        return -1;
    }
    return 0;
}

// #include <gsl/gsl_fit.h>
// #include <gsl/gsl_multifit_nlinear.h>

// int fit(void)
// {
//     double x[4] = {1.0, 2.0, 3.0, 4.0};
//     double y[4] = {2.2, 3.9, 6.1, 8.0};
//     double w[4] = {1.0, 1.0, 1.0, 1.0};
//     unsigned int n = 4;
//     double c0, c1, cov00, cov01, cov11, chisq;
//     gsl_fit_wlinear(x, 1, w, 1, y, 
//                     1, n, &c0, &c1, &cov00, &cov01, &cov11, &chisq);
//     printf("FIT: y = %gx + %g\n", c1, c0);
//
//     return 0;
// }


