#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv) {
    FILE *fd;
    int hist[1000], i, aux;

    fd = fopen(argv[1], "r");

    memset(hist, 0, 1000 * sizeof(int));
    while(!feof(fd)) {
        fscanf(fd, " %d ", &aux);
        printf("%d\n", aux);
        hist[aux]++;
    }

    for(i = 0; i < 1000; i++)
        printf("%d %d\n", i, hist[i]);

    return 0;
}
