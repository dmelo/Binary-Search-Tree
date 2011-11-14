CFLAGS=-g -O0

all: bin/randfile bin/bst bin/genhist bin/randoperations

bin/randfile: src/randfile.c
	gcc ${CFLAGS} src/randfile.c -o bin/randfile

bin/bst: src/bst.c
	gcc ${CFLAGS} src/bst.c -o bin/bst

bin/genhist: src/genhist.c
	gcc ${CFLAGS} src/genhist.c -o bin/genhist

bin/randoperations: src/randoperations.c
	gcc ${CFLAGS} src/randoperations.c -o bin/randoperations
