#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/utility.h"

#define MAX_DIR_SIZE 100000
#define MAX_SUBDIRS 20
#define TOTAL_DISK_SPACE 70000000
#define SPACE_NEEDED 30000000

struct node {
    int sum;
    int numChildren;
    struct node **children;
} node;
typedef struct node nod;

nod *createNode(int);
int createTree(nod*, FILE **fp);
int getBest(nod*, int, int*);
void deleteNode(nod*);

int main(int argc, char** argv) {
    FILE *fp = fopen(argv[1], "r");

    // This logic remains the same.
    nod *root = createNode(0);
    int rootSum = createTree(root, &fp);
    fclose(fp);

    // Get the total amount of memory being used currently.
    int memTotal = root->sum;
    int memUnused = TOTAL_DISK_SPACE - memTotal;
    int memToFree = SPACE_NEEDED - memUnused;

    int free = getBest(root, memToFree, &memTotal);
    printf("\n@ Best candidate is of size: %d <--------\n\n", free);

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

int getBest(nod* root, int numToBeat, int *bestSoFar) {
    int newBest = *bestSoFar;
    if (root->sum > numToBeat && root->sum < *bestSoFar) newBest = root->sum;
    for (int i = 0; i < root->numChildren; ++i) {
        newBest = getBest((root->children)[i], numToBeat, &newBest);
    }
    return newBest;
}

void deleteNode(nod* root) {
    for (int i = 0; i < root->numChildren; ++i) {
        deleteNode(root->children[i]);
    }
    free(root);
}