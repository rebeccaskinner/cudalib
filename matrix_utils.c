#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "color_print.h"
#include "matrix_utils.h"
#include "common_defs.h"

byte* generate_byte_matrix(int width, int height)
{
    byte* mat = (byte*)malloc(width*height);
    for(int j = 0; j < height; ++j)
        for(int k = 0; k < width; ++k)
            *(mat+((j*width)+k)) = rand()%256;
    return mat;
}

double* generate_double_matrix(int width, int height)
{
    double* mat = (double*)malloc(width*height);
    for(int j = 0; j < height; ++j)
        for(int k = 0; k < width; ++k)
            *(mat+((j*width)+k)) = ((double)((rand()%100000)+100)/100.0);
    return mat;
}

void print_byte(void* b)
{
    printf(" 0x%02X ",*((byte*)(b)));
}

void print_char(void* b)
{
    printf(" %c ",*((char*)(b)));
}

void print_double(void* d)
{
    printf(" %+08.3f ",*((double*)(d)));
}

void print_matrix_generic(int elem_w, int elem_h, int elem_size,
                          int elem_width, int group_size, byte* elems,
                          elem_fn print_fn)
{
    int v_len = (elem_h * elem_size);
    int h_len = (elem_w * elem_size);
    color_printf(CPF_NORMAL,CPF_RED,CPF_BLACK,"+");
    for(int i = 0; i < elem_w; ++i)
    {
        for(int j = 0; j < elem_width; ++j)
            color_printf(CPF_NORMAL,CPF_RED,CPF_BLACK,"-");
            color_printf(CPF_NORMAL,CPF_RED,CPF_BLACK,"+");
    }
    printf("\n");
    for(int h = 0; h < elem_h; ++h)
    {
        color_printf(CPF_NORMAL,CPF_RED,CPF_BLACK,"|");
        for(int w = 0; w < elem_w; ++w)
        {
            print_fn(elems+((h*h_len)+(w*elem_size)));
            if(!((w+1)%group_size))
                color_printf(CPF_NORMAL,CPF_RED,CPF_BLACK,"|");
            else
                color_printf(CPF_NORMAL,CPF_BLUE,CPF_BLACK,"|");
        }
        printf("\n");
        color_printf(CPF_NORMAL,CPF_RED,CPF_BLACK,"+");
        for(int i = 0; i < elem_w; ++i)
        {
            for(int j = 0; j < elem_width; ++j)
            {
                if(!((h+1)%group_size))
                    color_printf(CPF_NORMAL,CPF_RED,CPF_BLACK,"-");
                else
                    color_printf(CPF_NORMAL,CPF_BLUE,CPF_BLACK,"-");
            }
            if((!((i+1)%group_size)) || !((h+1)%group_size))
                color_printf(CPF_NORMAL,CPF_RED,CPF_BLACK,"+");
            else
                color_printf(CPF_NORMAL,CPF_BLUE,CPF_BLACK,"+");
        }
        printf("\n");
    }
}

