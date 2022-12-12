#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../headers/utility.h"

#define STOPANDCHECK 20

void checkCycle(int reg, int cycle, int *toCheck, int* nums, int *ind);

int main(int argc, char** argv) {
    FILE *fp = fopen(argv[1], "r");
    char* buff = malloc(11);

    int cycle = 1, len;
    int reg = 1;
    int *allSums = calloc(100, sizeof(int));
    int stopAndCheck[6] = {20, 60, 100, 140, 180, 220};
    int allSumsIndex = 0;
    printf("Cycle #\t\t Register\n");
    while(fgets(buff, 11, fp)) {
        if (!strncmp(buff, "n", 1)) {
            checkCycle(reg, cycle, stopAndCheck, allSums, &allSumsIndex);
            ++cycle;
        }
        else {
            buff += 5;
            len = 0;
            while(!strncmp(buff, "-", 1) || isdigit((buff)[0])) {
                ++len;
                ++buff;
            }
            buff -= len;
            checkCycle(reg, cycle, stopAndCheck, allSums, &allSumsIndex);
            ++cycle;
            checkCycle(reg, cycle, stopAndCheck, allSums, &allSumsIndex);
            reg += convertToNumber(buff, len);
            ++cycle;
        }
    }
    int sum = 0;
    for (int i = 0; i < 6; ++i) {
        sum += allSums[i];
    }

    printf("%d\n", sum);
    return 0;
}

void checkCycle(int reg, int cycle, int* toCheck, int* nums, int *ind) {
    for (int i = 0; i < 6; ++i) {
        if (cycle == toCheck[i]) {
            nums[(*ind)++] = reg*cycle; 
            break;
        } 
    }
    printf("%d\t\t%d\n", cycle, reg);
}