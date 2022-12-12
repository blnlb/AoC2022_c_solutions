#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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