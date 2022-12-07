#include "stack.h"
#include "../headers/utility.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int *collectDigits(char* str, int numToProcess) {
    int* res = calloc(3, sizeof(int));
    int ct = 0, len;
    for (int i = 0; i < numToProcess; ++i) {
        len = 0;
        while (!isdigit(str[ct])) {
            ++ct;
        }
        while (isdigit(str[ct+len])) {
            ++len;
        }
        res[i] = convertToNumber(str+ct, len);
        ct+=len;
    }
    return res;
}

int main(int argc, char** argv) {
    char buff[70];
    const char* filename = argv[1];
    FILE *fp = fopen(filename, "r");
    
    int numStacks = 9;
    bool pastCrates = false, oneMore = false;
    char *curr = malloc(5);
    curr[4] = '\0';

    int *directions = calloc(3, sizeof(int));

    char* final = malloc(numStacks+1);
    final[numStacks] = '\0';
    int i;

    st **s = calloc(numStacks, sizeof(st*));
    for (i = 0; i < numStacks; ++i) {
        s[i] = malloc(sizeof(st));
        s[i] = initStack();
    }

    st *midStack = malloc(sizeof(st));
    midStack = initStack();

    while (fgets(buff, 70, fp)) {
        if (!pastCrates) {
            if (isdigit(buff[1])) {
                pastCrates = true;
                continue;
            }
            int col = 0;
            while (col < numStacks) {
                memcpy(curr, buff+col*4, 4);
                if (!strncmp(curr, " ", 1)) {
                    ++col;
                    continue;
                }
                else {
                    insertAtBottom(s[col++], curr[1]);
                }
            }
        }
        else {
            if (!oneMore) {
            oneMore = true;
            continue;
        }  
            directions = collectDigits(buff, 3);
            // We're just using a completely different stack in the interim
            for (i = 0; i < directions[0]; ++i) {
                push(midStack, pop(s[directions[1]-1]));
            }
            for (i = 0; i < directions[0]; ++i) {
                push(s[directions[2] - 1], pop(midStack));
            }
        }
    }

    for (i = 0; i < numStacks; ++i) {
        final[i] = pop(s[i]);
    }

    printf("%s\n", final);
    fclose(fp);
    free(final); free(directions); free(curr); free(midStack);
    for (i = 0; i < numStacks; ++i) {
        free(s[i]);
    } free(s);
    return 0;
}
