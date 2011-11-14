CFLAGS=-g -O0

all: bin/randfile bin/bst bin/genhist bin/randomoperations

bin/randfile: src/randfile.c
	gcc ${CFLAGS} src/randfile.c -o bin/randfile

bin/bst: src/bst.c
	gcc ${CFLAGS} src/bst.c -o bin/bst

bin/genhist: src/genhist.c
	gcc ${CFLAGS} src/genhist.c -o bin/genhist

bin/randomoperations: src/randomoperations.c
	gcc ${CFLAGS} src/randomoperations.c -o bin/randomoperations
