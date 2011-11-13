all: bin/randfile bin/bst bin/genhist

bin/randfile: src/randfile.c
	gcc src/randfile.c -o bin/randfile

bin/bst: src/bst.c
	gcc src/bst.c -o bin/bst

bin/genhist: src/genhist.c
	gcc src/genhist.c -o bin/genhist
