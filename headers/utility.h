#ifndef UTILITY
#define UTILITY

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int convertToNumber(char* str, int n) {
    int result = 0;
    int ct = 0;
    int neg = 1;
    if (!strncmp(str, "-", 1)) {
        neg = -1;
        ++ct; --n;
    }
    while (n > 0) {
        if (!isdigit(str[ct])) {
            printf("Encountered a nondigit!");
            return result;
        }
        result += (str[ct++] - '0')*pow(10,--n);
    }

    return neg*result;
}

int* getNums(char* p, int *total) {
    FILE *fp = fopen(p, "r");
    if (!fp) {
        printf("No file found.\n");
        return NULL;
    }
    int buff = 1900;
    char* line = malloc(buff);

    int *result = calloc(101, sizeof(int));
    int neg = 1;
    int num, i = 0;
    while (fgets(line, buff, fp)) {
            while (*line != '\n') {
            if (isdigit(*line)) {
                num = 0;
                while (isdigit(*line)) {
                    num = num * 10 + *(line++) - '0';
                }
                result[i++] = num*neg;
                neg = 1;
            }
            else if (*line == '-') {
                neg = -1;
                ++line;
            }
            else {
                while (!isdigit(*line) && *line != '-' && *line != '\n') ++line;
            }
        }
    }
    *total = i;

    fclose(fp);
    return result;
}


#endif