#ifndef __MATRIX_UTILS_H__
#define __MATRIX_UTILS_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned char byte;
typedef void (*elem_fn)(void*);

byte* generate_byte_matrix(size_t width, size_t height);
double* generate_double_matrix(size_t width, size_t height);
void print_byte(void* b);
void print_double(void* d);
void print_matrix_generic(int elem_w, int elem_h, int elem_size,
                          int elem_width, int group_size, byte* elems,
                          elem_fn print_fn);

#endif
