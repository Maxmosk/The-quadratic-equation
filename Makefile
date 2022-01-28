.PHONY: all clean testprog


#C programming language compiler
CC=gcc
#Compiler flags
CFLAGS=  -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align 
CFLAGS+= -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return 
CFLAGS+= -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code 
CFLAGS+= -Wformat=2 -Werror -Winit-self -Wuninitialized -Wpointer-arith -save-temps 
CFLAGS+= -Wold-style-definition -Wstrict-prototypes -Wmissing-prototypes 
CFLAGS+= -Werror-implicit-function-declaration -Wlogical-op -Wduplicated-cond
CFLAGS+= -Wcast-qual -Wcast-align -Wformat-security 
CFLAGS+= -lasan -fsanitize=address,leak,undefined -fstack-protector 
CFLAGS+= -s -masm=intel -pedantic -std=c99 -lm -o


all: quad


quad: main.o solver.o testing.o
	$(CC) $(CFLAGS) quad main.o solver.o testing.o

main.o: main.c
	$(CC) -c $(CFLAGS) main.o main.c
solver.o: solver.c
	$(CC) -c $(CFLAGS) solver.o solver.c
testing.o: testing.c
	$(CC) -c $(CFLAGS) testing.o testing.c


testprog: main_t.o solver.o testing.o
	$(CC) $(CFLAGS) quad main_t.o solver.o testing.o

main_t.o: main.c
	$(CC) -c -D TESTS_ON $(CFLAGS) main_t.o main.c


clean:
	rm -rf *.o *.i *.s testprog quad

