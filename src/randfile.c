#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv) {
    int num, i, *used, aux;

    sscanf(argv[1], " %d ", &num);
    printf("%d\n", num);
    srand(time(NULL));
    used = (int *) calloc(num, sizeof(int));

    for(i = 0; i < num; i++) {
        do {
            aux = rand();
            aux %= num;
        } while(used[aux] != 0);
        printf("%d\n", aux);
        used[aux] = 1;
    }

    return 0;
}
