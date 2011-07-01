CC=gcc
NVCC=nvcc

CFLAGS=-ggdb        \
       -std=gnu99   \
       -O0          \
       -Wall        \
       -Wextra      \
       -Werror      \
       -Wno-unused  \
       -DUSE_COLOR  

LFLAGS=-lm \
       -L/home/miyako/projects/MagicMapper/deps/lib \
       -ljpeg \
       -lcuda \
       -lcudart

MAT_OBJ=color_print.o        \
	matrix_utils.o       \
        cuda_itop.o          \
        test_matrix_utils.o  

%.o:%.c
	$(CC) $(ECFLAGS) $(CFLAGS) -c $< -o $(@)

%.o:%.cu
	$(NVCC) -c --compiler-options -fpermissive $< -o $(@)

all: matrix

matrix:$(MAT_OBJ)
	$(CC) $(LFLAGS) -o $(@) $(MAT_OBJ)

clean:
	-rm -f *.o
	-rm -f matrix

.PHONY: all clean
