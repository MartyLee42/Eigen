CFLAGS=-mfpmath=sse -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors \
-fstack-protector-all -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute \
-Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long   -Wcast-qual

all:  mainEigen

mainGauss: mainGauss.c solve.c RW.c
	gcc $(CFLAGS) -g -o mainGauss mainGauss.c solve.c RW.c -lm 

mainEigen: mainEigen.c solve.c RW.c
	gcc $(CFLAGS) -g -o mainEigen mainEigen.c solve.c RW.c -lm
