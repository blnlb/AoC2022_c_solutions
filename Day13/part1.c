#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "../headers/utility.h"

#define MAX(A,B) ((A) ^ ((A ^ B) & -(A < B)))
#define MAXLINESIZE 330

typedef struct node {
    struct node* next; 
    struct node* list;  
    int value;  
    bool divider;
} node;

node* allLines[MAXLINESIZE];  
int nodeCount;

node* createNode(node* parent, int value) {
    node* result = calloc(1, sizeof(node));
    ++nodeCount;
    if (parent) parent->next = result; 
    result->value = value;
    return result;
}

void destroyNode(node* e) {
    if (e == NULL) return;
    destroyNode(e->list);
    destroyNode(e->next);
    free(e);
    --nodeCount;
}

node* parseInput(char** input) {
    node* root = createNode(NULL, 2);              
    node* curr = root, *prev = NULL;

    int val, len = 0;
    while (**input != '\n' && **input != '\0') {
        char currentCharacter = *((*input)++);
        if (currentCharacter == '[') {                                            
            ++len;
            if (!(curr->list = parseInput(input))) curr->value = -1; 
        }
        else if (currentCharacter == ']') {         
            if (len == 0) {
                free(root);
                --nodeCount;
                return NULL;
            }
            return root; 
        }
        else if (currentCharacter == ',') {
            prev = curr;                       
            curr = createNode(prev, 2);             
            if (!curr) return root;
        }                                        
        else {                         
            ++len;
            val = *(*input - 1);             
            while (isdigit(**input))  {           
                val = val * 10 + *(*input)++;
            }
            curr->value = val;
        }
    }
    return root;        
}

void makeList(node* root) {
    if (!root) return;
    if (root->list || root->value == -1) return;
    root->list = createNode(NULL, root->value);
    root->value = 0;
}

int cmp(node* left, node* right)
{
    if (!left && !right) return 0;   
    else if (!left && right) return -1;
    else if (left && !right) return 1; 

    bool leftList = left->list || (left->value == -1);
    bool rightList = right->list || (right->value == -1);

    if (!leftList && rightList) {
        makeList(left);
        leftList = true;
    } else if (leftList && !rightList) { 
        makeList(right); 
        rightList = true;
    }

    if (leftList && rightList) { 
        int c = cmp(left->list, right->list);
        if (c) return c;
    } else {
        if (left->value < right->value)
            return -1;
        else if (left->value > right->value)
            return 1;
    }
    return cmp(left->next, right->next);
}

int read(char* filename)
{
    FILE* fp = fopen(filename, "r");
    int i = 0;
    char* line = NULL;
    size_t buff = 0;
    ssize_t len;
    while (i < MAXLINESIZE && (len = getline(&line, &buff, fp)) > 0) {
        if (len == 1) continue; // blank line
        char* s = line;
        allLines[i++] = parseInput(&s);
    }
    fclose(fp);
    free(line);
    return i;
}

int compareInput2(char* left, char* right, int beginL, int endL, int beginR, int endR, int, int);

int main(int argc, char **argv)
{
    int numLines = read(argv[1]);
    int sum = 0;
    for (int i = 0; i < numLines; i += 2) {
        if (cmp(allLines[i], allLines[i + 1]) == -1) {
            sum += (i >> 1) + 1;
        }
    }

    printf("%d\n", sum);

    return 0;
}

// int compareInput2(char* left, char* right, int beginL, int endL, int beginR, int endR, int numItemsL, int numItemsR) {
//     int isSmaller = -1;
//     int newEndL, newEndR;
//     int numOpen, offsetL, offsetR;

//     while (beginL < endL) {
//         newEndL = endL;
//         newEndR = endR;
//         numOpen = 0;
//         offsetL = 0;
//         offsetR = 0;
        
//         if (beginR > endR)  return 0;
//         if (left[beginL] == '[' || right[beginR] == '[') {
//             if (left[beginL] == '[') {
//                 numItemsL = 0;
//                 newEndL = beginL;
//                 ++offsetL;
//                 ++numOpen;
//                 while (numOpen > 0) {
//                     ++newEndL;
//                     if (left[newEndL] == '[') {
//                         ++numOpen;
//                     }
//                     else if (left[newEndL] == ']') --numOpen;
//                     else if (isdigit(left[newEndL])) ++numItemsL;
//                 }
//             }
//             if (right[beginR] == '[') {
//                 numItemsR = 0;
//                 newEndR = beginR;
//                 ++offsetR;
//                 ++numOpen;
//                 while (numOpen > 0) {
//                     ++newEndR;
//                     if (right[newEndR] == '[') {
//                         ++numOpen;
//                     }
//                     else if (right[newEndR] == ']') --numOpen;
//                     else if (isdigit(right[newEndR])) ++numItemsR;
//                 }
//             }
//             if (numItemsR == 0 && numItemsL > 0) return 0;
//             if (numItemsL == 0 && numItemsR > 0) return 1;
//             isSmaller = compareInput2(left, right, beginL + offsetL, newEndL, beginR + offsetR, newEndR, numItemsL, numItemsR);
//             if (isSmaller != -1) return isSmaller;
//             else {
//                 beginL = newEndL + 2;
//                 beginR = newEndR + 2;
//                 continue;
//             }
//         }
//         if (isdigit(left[beginL]) && isdigit(right[beginR])) {
//             int lenL = 1;
//             int lenR = 1;
//             while (isdigit(left[beginL + lenL])) ++lenL;
//             while (isdigit(right[beginR + lenR])) ++lenR;
//             int leftToNumber = convertToNumber(left + beginL, lenL);
//             int rightToNumber = convertToNumber(right + beginR, lenR);
//             if (leftToNumber < rightToNumber) return 1;
//             else if (leftToNumber > rightToNumber) return 0;
//             beginL += 1 + lenL;
//             beginR += 1 + lenR;
//         }
        
//     }
//     if (beginR < endR) return 1;
//     if (beginR == endR) return 0;
//     return -1;
// }