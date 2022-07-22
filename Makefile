.PHONY: all clean

include CMakefile

#C programming language compiler
CC=gcc
#Compiler flags
CFLAGS=$(CFLAGS_WARNINGS) $(CFLAGS_FLAGS) $(CFLAGS_SYNTAX) $(CFLAGS_DEBUG)
LDFLAGS=-lm $(CFLAGS_LINK)


OBJFILES=main.o solver.o testing.o
HEADFILES=solver.h testing.h

all: quad


quad: $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $?

%.o: %.c $(HEADFILES)
	$(CC) -c $(CFLAGS) -o $@ $<


clean:
	rm -rf *.o *.i *.s quad

