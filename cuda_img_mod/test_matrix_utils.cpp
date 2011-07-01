#include <math.h>
#include "matrix_utils.h"
#include "dct.h"

int main()
{
    //srand(10);
    //byte* bm = generate_byte_matrix(16,16);
    //double* dm = generate_double_matrix(16,16);
    //print_matrix_generic(16,16,1,6,8,bm,print_byte);
    //print_matrix_generic(16,16,sizeof(double),10,4,(byte*)dm,print_double);
    dct_trig_table t = dct_table_init(8);
    printf("8x8 DCT kernel:\n");
    print_matrix_generic(8,8,sizeof(double),10,8,(byte*)t,print_double);
    return 0;
}
