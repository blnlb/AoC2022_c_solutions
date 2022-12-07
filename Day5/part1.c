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
    
    // INITIALIZE AREA* * * * * * * * * * * * * * * * 
    // Pre-logic area
    int numStacks = 9;
    bool pastCrates = false, oneMore = false;
    char *curr = malloc(5);
    curr[4] = '\0';
    int i;

    // Now we read the logic into these variables
    int *directions = calloc(3, sizeof(int));

    // And then just put the results into a final guy.
    char* final = malloc(numStacks+1);
    final[numStacks] = '\0';
    //***********************************************
    
    // START ************************************
    //Create an array of STACKS!
    st **s = calloc(numStacks, sizeof(st*));
    for (i = 0; i < numStacks; ++i) {
        s[i] = malloc(sizeof(st));
        s[i] = initStack();
    }

    while (fgets(buff, 70, fp)) {
        // gather all the stacks onto... stacks
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
        // then find out what each direction is and process it with
        // stack operations
        else {
            if (!oneMore) {
            oneMore = true;
            continue;
        }  
            directions = collectDigits(buff, 3);
            for (i = 0; i < directions[0]; ++i) {
                push(s[directions[2]-1], pop(s[directions[1]-1]));
            }
        }
    }

    for (i = 0; i < numStacks; ++i) {
        final[i] = pop(s[i]);
    }

    printf("%s\n", final);
    fclose(fp);
    free(final); free(directions); free(curr);
    for (i = 0; i < numStacks; ++i) {
        free(s[i]);
    } free(s);
    return 0;
}
