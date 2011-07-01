#ifndef __JPEG_UTILS_H__
#define __JPEG_UTILS_H__
#include <jpeglib.h>
#include <setjmp.h>

extern const int COLORSPACE_RGB;
extern const int COLORSPACE_YUV;
extern const int COLORSPACE_GREY;

struct
{
    struct jpeg_error_mgr mgr_pub;
    jmp_buf err_jmp_buff;
}jpeg_err_mgr;

typedef struct
{
    struct jpeg_decompress_struct decomp;
    struct jpeg_err_mgr err_struct;
}jpeg_reader_t;
#endif
