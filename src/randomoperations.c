#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv) {
    int num, limit, i;
    char command;

    sscanf(argv[1], " %d ", &num);
    sscanf(argv[2], " %d ", &limit);

    srand(time(NULL));

    for(i = 0; i < num; i++) {
        switch(rand() % 4) {
            case 0:
                command = 'i';
                break;
            case 1:
                command = 's';
                break;
            case 2:
                command = 'd';
                break;
            case 3:
                command  = 'p';
                break;
        }

        printf("%c %d\n", command, (rand() % limit) + 1);
    }

    return 0;
}
