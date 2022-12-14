#ifndef PARSER
#define PARSER

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAXLINESIZE 330

typedef struct node {
    struct node* next; 
    struct node* list;  
    int value;  
    bool divider;
} node;
node* allLines[MAXLINESIZE]; 

node* createNode(node*, int);
void destroyNode(node*);
node* parseInput(char** input);
void makeList(node* root);

int cmp(node* left, node* right);
int sort(const void* a, const void* b);

int read(char* filename);
node* insertDumbDivider(int val);


#endif