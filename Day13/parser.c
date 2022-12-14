#include "parser.h"


node* createNode(node* parent, int value) {
    node* result = calloc(1, sizeof(node));
    if (parent) parent->next = result; 
    result->value = value;
    result->divider = false;
    return result;
}

void destroyNode(node* root) {
    if (root == NULL) return;
    destroyNode(root->list);
    destroyNode(root->next);
    free(root);
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

int cmp(node* left, node* right) {
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

int sort(const void* a, const void* b) {
    node* left = *(node**)a;
    node* right = *(node**)b;
    return cmp(left, right);
}

int read(char* filename) {
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

//dumb
node* insertDumbDivider(int val)
{
    node* result = createNode(NULL, INT_MAX);
    result->divider = true;
    result->list = createNode(NULL, INT_MAX);
    result->list->list = createNode(NULL, val);
    return result;
}