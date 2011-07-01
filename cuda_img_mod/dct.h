#ifndef __DCT_H__
#define __DCT_H__
#include <sys/types.h>

#define PI 3.14159265
typedef double* dct_trig_table;

dct_trig_table dct_table_init(size_t size);

#endif
