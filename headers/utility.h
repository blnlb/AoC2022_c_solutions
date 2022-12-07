#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int convertToNumber(char* str, int n) {
    int result = 0;
    int ct = 0;
    while (n > 0) {
        if (!isdigit(str[ct])) {
            printf("Encountered a nondigit!");
            return result;
        }
        result += (str[ct++] - '0')*pow(10,--n);
    }

    return result;
}