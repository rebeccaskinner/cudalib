#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include "dct.h"

dct_trig_table dct_table_init(size_t size)
{
    dct_trig_table table = (dct_trig_table)malloc(2*size*sizeof(double));
    register double alpha = (PI/(double)size)*(PI/(double)size);
    for(size_t k1 = 0; k1 < size; ++k1)
    {
        for(size_t k2 = 0; k2 < size; ++k2)
        {
            for(size_t n = 0; n < size; ++n)
            {
                table[(k1*size)+k2] = cos(alpha * pow((n+0.5),2) * k1 * k2);
            }
        }
    }
    return table;
}
