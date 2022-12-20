#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define INPUTFILESIZE 5000
#define EXAMPLEFILESIZE 7
#define PART2 1

typedef struct node {
    int val;
    int order;
    struct node *next;
    struct node *mom;
} node;

node *createNode(int val, node* prev, int order) {
    node *result = (node*)calloc(1, sizeof(node));
    result->val = val;
    result->order = order;
    result->mom = prev;
    result->next = NULL;
    return result;
}

void insertNextTo(node *a, node*b) { // a to b
    if (a==b) printf("This is bad, fam.\n");
    a->mom->next = a->next;
    a->next->mom = a->mom;
    a->mom = b->mom;
    b->mom->next = a;
    b->mom = a;
    a->next = b;

}

void moveNode(node* root, int listSize, int decKey) {
    int val = (long)root->val;
    int neg = 1;
    if (val < 0) {
        val = -val;
        neg = listSize - 1;
    }
    val = (((neg*(val%listSize)%listSize)*(decKey%listSize))) % listSize;

    if (val == 0) return;
    node* ptr = root->next;
    for (int i = 0; i < val; ++i) {
        ptr = ptr->next;
    }
    insertNextTo(root, ptr);
}

int main(int argc, char** argv) {
    const char *filename = argv[1] ? argv[1] : "example.txt";
    FILE *fp = fopen(filename, "r");
    int listsize = strcmp(filename, "example.txt") ? INPUTFILESIZE : EXAMPLEFILESIZE;
    int buff = 20000;
    char* line = malloc(buff);

    struct node* ptr = NULL, *head = NULL;

    int decryptKey = PART2 ? 811589153 : 1;

    int num;
    long neg;
    int total = 0;
    while (fgets(line, buff, fp)) {
        num = 0, neg = 1;
        if (*line == '-') {
            neg = -1;
            ++line;
        }
        while (isdigit(*line)) {
            num = num * 10 + *line++ - '0';
        }
        num *= neg;
        if (ptr != NULL) {
            ptr->next = createNode(num, ptr, total++);
            ptr = ptr->next;
        }
        else {
            head = createNode(num, NULL, total++);
            ptr = head;
        }
    }
    head->mom = ptr;
    ptr->next = head;
    ptr = ptr->next;

    int found = 0;
    int numTimes = 10;
    while (numTimes--) {
        printf("\n");
        while (found < total) {
            while (ptr->order != found) {
                ptr = ptr->next;
            }
            moveNode(ptr, listsize - 1, decryptKey);
            ++found;
        }
        found = 0;
    }

    while (ptr->val != 0) ptr=ptr->next;
    int numsToGet = 3;
    int offby = 1000;
    long x, y, z;
    while (offby--) ptr = ptr->next;
    x = (long)ptr->val*decryptKey; offby = 1000;
    while (offby--) ptr = ptr->next;
    y = (long)ptr->val*decryptKey; offby = 1000;
    while (offby--) ptr = ptr->next;
    z = (long)ptr->val*decryptKey;
    
    printf("%ld + %ld + %ld = %ld\n",x, y, z, x+y+z);

    return 0;
}