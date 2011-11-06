#include<stdio.h>
#include<stdlib.h>

struct node {
    int value;
    struct node *right;
    struct node *left;
};

struct node *newNode(int value) {
    struct node *n = (struct node *) calloc(1, sizeof(struct node));
    n->value = value;
    n->right = n->left = NULL;

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


int main() {
    int num, i, aux;
    struct node root;
    root.right = root.left = NULL;

    scanf(" %d ", &num);
    for(i = 0; i < num; i++) {
        scanf(" %d ", &aux);
        printf("Inserting %d...\n", i);
        if(0 == i)
            root.value = aux;
        else
            insert(&root, aux);
    }

    printf("%d\n", height(&root, 0));

    return 0;
}
