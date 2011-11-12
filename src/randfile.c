#include<stdio.h>
#include<stdlib.h>

/**
 * ./randfile 100 output 100 and then the numbers from 0 to 99 randomly sorted.
 **/
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
        } while(used[aux]);
        printf("%d\n", aux);
        used[aux] = 1;
    }

    return 0;
}
