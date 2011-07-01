CPP=g++

CFLAGS=-g           \
       -O0          \
       -Wall        \
       -Wextra      \
       -DUSE_COLOR

LFLAGS=-lm

MAT_OBJ=color_print.o        \
	matrix_utils.o       \
        test_matrix_utils.o

IMG_LOADER=jpeg_utils.o\
           matrix_utils.o\
           load_tester.o


%.o:%.c
	$(CPP) $(ECFLAGS) $(CFLAGS) -c $< -o $(@)

all: matrix img_loader

matrix:$(MAT_OBJ)
	$(CPP) $(LFLAGS) -o $(@) $(MAT_OBJ)

matrix:$(MAT_OBJ)
	$(CPP) $(LFLAGS) -o $(@) $(MAT_OBJ)

clean:
	-rm -f *.o

.PHONY: all clean
