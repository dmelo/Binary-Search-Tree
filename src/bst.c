#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    int value;
    struct node *left;
    struct node *right;
};

struct node *newNode(int value) {
    struct node *n = (struct node *) calloc(1, sizeof(struct node));
    n->value = value;
    n->left = n->right = NULL;

    return n;
}

void insert(struct node* root, int value) {
    struct node *n;
    if(value > root->value) {
        if(NULL != root->right)
            insert(root->right, value);
        else 
            root->right = newNode(value);
    }
    else if( value < root->value) {
        if(NULL != root->left)
            insert(root->left, value);
        else 
            root->left = newNode(value);
    }
}

struct node *search(struct node *root, int value) {
    if(value == root->value)
        return root;
    else if(value < root->value)
        return root->left ? search(root->left, value): NULL;
    else // value > root->value
        return root->right ? search(root->right, value): NULL;
}

void printInOrder(struct node* root) {
    if(NULL != root->left)
        printInOrder(root->left);
    printf("%d ", root->value);
    if(NULL != root->right)
        printInOrder(root->right);
}

void printPreOrder(struct node* root) {
    printf("%d ", root->value);
    if(NULL != root->left)
        printInOrder(root->left);
    if(NULL != root->right)
        printInOrder(root->right);
}

int height(struct node* root, int h) {
    int aux_left = 0;
    int aux_right = 0;

    aux_left  = NULL != root->left  ? height(root->left , h + 1) : 0;
    aux_right = NULL != root->right ? height(root->right, h + 1) : 0;

    return aux_left || aux_right ? aux_left > aux_right ? aux_left : aux_right : h + 1;
}


int main(int argc, char **argv) {
    int num, i, aux;
    struct node root;
    FILE *fd, *fout;
    char namefout[1000];
    root.right = root.left = NULL;

    fd = fopen(argv[1], "r");

    fscanf(fd, " %d ", &num);
    for(i = 0; i < num; i++) {
        fscanf(fd, " %d ", &aux);
        if(0 == i % 100000)
            printf("Inserting %d from %s...\n", i, argv[1]);

        if(0 == i)
            root.value = aux;
        else
            insert(&root, aux);
    }
    fclose(fd);

    strcpy(namefout, argv[1]);
    strcat(namefout, ".out");
    fout = fopen(namefout, "w");
    fprintf(fout, "%d\n", height(&root, 0));

    return 0;
}
