#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define ERROR 1
#define LEFT 2
#define RIGHT 3

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

int insert(struct node* root, int value) {
    struct node *n;
    if(root->value == 0) 
        root->value = value;
    else {
        if(value == root->value)
            return ERROR;
        else if(value > root->value) {
            if(root->right)
                return insert(root->right, value);
            else 
                root->right = newNode(value);
        }
        else { // ( value < root->value) 
            if(root->left)
                return insert(root->left, value);
            else 
                root->left = newNode(value);
        }
    }

    return SUCCESS;
}

struct node *search(struct node *root, int value) {
    if(value == root->value)
        return root;
    else if(value < root->value)
        return root->left ? search(root->left, value): NULL;
    else // value > root->value
        return root->right ? search(root->right, value): NULL;
}

struct node *searchParent(struct node *root, int value) {
    if(value == root->value)
        return NULL;
    else if(value < root->value) {
        if(!root->left)
            return NULL;
        else if(root->left->value == value)
            return root;
        else
            return searchParent(root->left, value);
    }
    else if(value > root->value) {
        if(!root->right)
            return NULL;
        else if(root->right->value == value)
            return root;
        else
            return searchParent(root->right, value);
    }
}

struct node *findMost(struct node *root, int direction) {
    if(direction == LEFT) 
        return root->left ? findMost(root->left, direction): root;
    else
        return root->right ? findMost(root->right, direction): root;
}

int numOfChild(struct node *root) {
    int num = 0;
    if(root->left)
        num++;
    if(root->right)
        num++;

    return num;
}

int delete(struct node *root, int value) {
    struct node *node, *nodeParent, *nodeAux;
    int aux;

    node = search(root, value);
    if(!node)
        return ERROR;
    nodeParent = searchParent(root, value);

    switch(numOfChild(node)) {
        case 0:
            if(nodeParent) {
                if(nodeParent->right && nodeParent->right->value == node->value)
                    nodeParent->right = NULL;
                else
                    nodeParent->left = NULL;
                free(node);
            }
            else 
                node->value = 0;
            break;
        case 1:
            if(nodeParent) {
                if(nodeParent->left && nodeParent->left->value == node->value)
                    nodeParent->left = node->left ? node->left: node->right;
                else
                    nodeParent->right = node->left ? node->left: node->right;
            }
            else {
                if(node->left)
                    root = root->left;
                else
                    root = root->right;
            }
            free(node);

            break;
        case 2:
            nodeAux = findMost(node->right, LEFT);
            aux = nodeAux->value;
            delete(node, aux);
            node->value = aux;
            break;
    }

    return SUCCESS;
}

void printTree(struct node* root, int height) {
    int i;

    if(root) {
        printTree(root->left, height + 1);
        for(i = 0; i < height; i++)
            printf("  ");
        printf("%d\n", root->value);
        printTree(root->right, height + 1);
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

/**
 * i NUM -- insert number NUM, e.g. "i 10"
 * s NUM -- search for number NUM, e.g. "s 13"
 * d NUM -- delete number NUM, e.g. "d 15"
 * p -- print the tree
 **/
int main(int argc, char **argv) {
    int num, i, aux;
    char command;
    struct node *root = NULL, *auxNode;
    FILE *fd, *fout;
    char namefout[1000];

    root = newNode(0);

    if((fd = fopen(argv[1], "r")) == NULL) {
        printf("error: couldn't open file");
        return ERROR;
    }

    while(!feof(fd)) {
        fscanf(fd, " %c %d ", &command, &num);
        switch(command) {
            case 'i':
                aux = insert(root, num);
                printf("insert %d: ", num);
                SUCCESS == aux ? printf("OK\n"): printf("ERROR\n");
                break;
            case 's':
                auxNode = search(root, num);
                printf("search %d: ", num);
                auxNode ? printf("FOUND\n"): printf("NOT FOUND\n");
                break;
            case 'd':
                printf("delete %d: ", num);
                delete(root, num) == SUCCESS ? printf("DELETED\n") : printf("NOT DELETED\n");
                break;
            case 'p':
                printTree(root, 0);
                break;
            default:
                printf("error: command not found!\n");
        }
    }

    strcpy(namefout, argv[1]);
    strcat(namefout, ".out");
    fout = fopen(namefout, "w");
    fprintf(fout, "%d\n", height(root, 0));

    return SUCCESS;
}
