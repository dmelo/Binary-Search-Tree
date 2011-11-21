#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define ERROR 1
#define LEFT 2
#define RIGHT 3
#define PRE_ORDER 1
#define IN_ORDER 2
#define POST_ORDER 3

/**
 * Node structure. Here, it is possible to add more data. E.g, if each node 
 * represents a user, then we can add data regarding his/her name, gender, 
 * birth date and so on.
 */
struct node {
    int value;
    struct node *left;
    struct node *right;
};

/**
 * Allocates memory a new node and fill it's key with the proper value.
 */
struct node *newNode(int value) {
    struct node *n = (struct node *) calloc(1, sizeof(struct node));
    n->value = value;
    n->left = n->right = NULL;

    return n;
}

/**
 * Insert a new node on the tree if the value is not already stored.
 */
int insert(struct node* root, int value) {
    struct node *n;
    if(!root->value) 
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

/**
 * search for a value on the tree.
 */
struct node *search(struct node *root, int value) {
    if(value == root->value)
        return root;
    else if(value < root->value)
        return root->left ? search(root->left, value): NULL;
    else // value > root->value
        return root->right ? search(root->right, value): NULL;
}

/**
 * Gets the pointer to the parent of a specific value if it exists.
 */
struct node *searchParent(struct node *root, int value) {
    if(value == root->value)
        return NULL;
    else if(value < root->value && root->left)
        return root->left->value == value ? root: searchParent(root->left, value);
    else if(value > root->value && root->right)
        return root->right->value == value ? root: searchParent(root->right, value);

    return NULL;
}

/**
 * Find the greatest or the smallest son of a given node.
 */
struct node *findMost(struct node *root, int direction) {
    if(direction == LEFT) 
        return root->left ? findMost(root->left, direction): root;
    else
        return root->right ? findMost(root->right, direction): root;
}

/**
 * Delete a node from the tree.
 */
int delete(struct node *root, int value) {
    struct node *node, *nodeParent, *nodeAux;
    int aux, nChild;

    node = search(root, value);
    if(!node)
        return ERROR;

    nChild = node->left && node->right ? node->left || node->right ? 2 : 1 : 0;
    if(nChild < 2) {
        nodeParent = searchParent(root, value);
        if(nodeParent) {
            if(nodeParent->left && nodeParent->left->value == node->value)
                nodeParent->left = nChild ? node->left ? node->left : node->right : NULL;
            else
                nodeParent->right = nChild ? node->left ? node->left : node->right : NULL;
        }
        else
            node->value = 0;
        free(node);
    }
    else {
        nodeAux = findMost(node->right, LEFT);
        aux = nodeAux->value;
        delete(node, aux);
        node->value = aux;
    }

    return SUCCESS;
}

/**
 * Print the tree structure.
 */
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

/**
 * Print the tree values in pre, in or post order.
 */
void printOrder(struct node *root, int order) {
    if(PRE_ORDER == order)
        printf("%d ", root->value);
    if(root->left)
        printOrder(root->left, order);
    if(IN_ORDER == order)
        printf("%d ", root->value);
    if(root->right)
        printOrder(root->right, order);
    if(POST_ORDER == order)
        printf("%d ", root->value);
}

/**
 * Calculate the tree's height.
 */
int height(struct node* root, int h) {
    int aux_left = 0;
    int aux_right = 0;

    aux_left  = root->left  ? height(root->left , h + 1) : 0;
    aux_right = root->right ? height(root->right, h + 1) : 0;

    return aux_left || aux_right ? aux_left > aux_right ? aux_left : aux_right : h + 1;
}

/**
 * i NUM -- insert number NUM, e.g. "i 10"
 * s NUM -- search for number NUM, e.g. "s 13"
 * d NUM -- delete number NUM, e.g. "d 15"
 * p NUM -- 0 for printing the tree struct. 1, 2 or 3 for printing the numbers
 *       -- in pre, in or post order, respectively.
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
                if(0 == num)
                    printTree(root, 0);
                else
                    printOrder(root, num);
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
