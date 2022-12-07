#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/utility.h"

#define MAX_DIR_SIZE 100000
#define MAX_SUBDIRS 20 //this was enough for the input
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

int main(int argc, char** argv) {
    const char *filename = argv[1];
    FILE *fp = fopen(filename, "r");

    // This logic remains the same.
    nod *root = createNode(0);
    int rootSum = createTree(root, &fp);

    // Get the total amount of memory being used currently.
    int memTotal = root->sum;
    int memUnused = TOTAL_DISK_SPACE - memTotal;
    int memToFree = SPACE_NEEDED - memUnused;

    printf("Space used by root directory: %d\n", memTotal);
    printf("Space not in use: %d\n", memUnused);
    printf("Space to be freed: %d\n", memToFree);

    int free = getBest(root, memToFree, &memTotal);
    printf("Best candidate is of size: %d\n", free);
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
            if (!strncmp(buff + 5, "..", 2)) return root->sum;
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