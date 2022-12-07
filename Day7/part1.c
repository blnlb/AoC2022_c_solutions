#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/utility.h"

#define MAX_DIR_SIZE 100000
#define MAX_SUBDIRS 20

struct node {
    int sum;
    int numChildren;
    struct node **children;
} node;
typedef struct node nod;

nod *createNode(int);
void deleteNode(nod*);
int createTree(nod*, FILE **fp);
int navigate(nod*);

int main(int argc, char** argv) {
    FILE *fp = fopen(argv[1], "r");

    // First I need to create the structure,
    // then navigate it recursively to store the sums.
    nod *root = createNode(0);
    int rootSum = createTree(root, &fp);
    fclose(fp);

    // Now that we have a large tree, we need to go back through
    // and check the sum on our condition
    int sum = navigate(root);
    printf("%d\n", sum);

    // wow I cannot believe that worked.
    deleteNode(root);
    return 0;
}

nod *createNode(int n) {
    nod *newGuy = malloc(sizeof(nod));
    newGuy->sum = n;
    newGuy->children = calloc(MAX_SUBDIRS, sizeof(nod*));
    newGuy->numChildren = 0;
    return newGuy;
}

int createTree(nod* root, FILE **fp) {
    char *buff = malloc(30);
    while(fgets(buff, 30, *fp)) {
        if (!strncmp(buff, "$ cd", 3)) {
            if (!strncmp(buff + 5, "..", 2)) break;
            root->children[root->numChildren] = createNode(0);
            root->sum += createTree(root->children[(root->numChildren)++], fp);
        } else if (isdigit(buff[0])) {
            int len = 1;
            while (strncmp(++buff, " ", 1)) ++len;
            buff -= len;
            root->sum += convertToNumber(buff, len);
            continue;
        } 
    }
    free(buff);
    return root->sum;
}

int navigate(nod* root) {
    int tally = 0;
    if (root->sum <= MAX_DIR_SIZE) tally += root->sum;
    for (int i = 0; i < root->numChildren; ++i) {
        tally += navigate((root->children)[i]);
    }
    return tally;
}

void deleteNode(nod* root) {
    for (int i = 0; i < root->numChildren; ++i) {
        deleteNode(root->children[i]);
    }
    free(root);
}