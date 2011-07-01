#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <jpeglib.h>
#include "jpeg_utils.h"

const int COLORSPACE_RGB = JCS_RGB;
const int COLORSPACE_YUV = JCS_YCbCr;
const int COLORSPACE_GREY = JCS_GRAYSCALE;

void jpeg_err_abort (j_common_ptr cinfo)
{
    fprintf(stderr,"Libjpeg encountered an error, aborting\n");
    exit(-1);
}

jpeg_reader_t* jpeg_reader_new(int colorspace)
{
    jpeg_reader_t* reader = malloc(sizeof(jpeg_reader_t));
    reader->decomp.out_color_space = colorspace;
    reader->decomp.err = jpeg_std_error(&(reader->err_struct).pub);
    reader->err_struct.mgr_pub.error_exit = jpeg_err_abort;
    jpeg_create_decompress(&(reader->decomp));
}

int jpeg_parsemem(jpeg_reader_t* jparser, char* inbuffer, size_t in_len, char* outbuffer)
{
    //struct jpeg_decompress_struct cinfo;
    //struct my_error_mgr jerr;
    JSAMPARRAY buffer;		/* Output row buffer */
    int row_stride;		/* physical row width in output buffer */
    //if ((infile = fopen(filename, "rb")) == NULL) {
    //    fprintf(stderr, "can't open %s\n", filename);
    //    return 0;
    //}
    //cinfo.err = jpeg_std_error(&jerr.pub);
    //jerr.pub.error_exit = my_error_exit;
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return 0;
    }
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)
        ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        put_scanline_someplace(buffer[0], row_stride);
    }
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    /* And we're done! */
    return 0;
}

int jpeg_readfile(char * filename, char* outbuffer)
{
}
