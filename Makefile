.PHONY: all clean

include CMakefile

#C programming language compiler
CC=gcc
#Compiler flags
CFLAGS=$(CFLAGS_WARNINGS) $(CFLAGS_FLAGS) $(CFLAGS_SYNTAX) $(CFLAGS_DEBUG)
LDFLAGS=-lm $(CFLAGS_LINK)


SOURCEDIR=src/code
HEADERDIR=src/head
BUILDDIR=build
TESTSDIR=tests
CIDIR=ci-scripts
DOCKERIMAGE=alipnetest
SOURCES=$(wildcard src/code/*.c)
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
HEADFILES=$(wildcard $(HEADERDIR)/*.h)
OBJFILES=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
EXECUTABLE=$(BUILDDIR)/quad


all: dir $(EXECUTABLE)

tests: build_tests
	docker run --rm -t $(DOCKERIMAGE) 

build_tests: $(CIDIR)/Dockerfile
	docker build -t $(DOCKERIMAGE) $(CIDIR)

dir:
	mkdir $(BUILDDIR)

$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $?

$(OBJFILES): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c $(HEADFILES)
	$(CC) -c $(CFLAGS) -o $@ $<


clean:
	rm -rf $(BUILDDIR)

