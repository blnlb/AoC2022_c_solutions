#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../headers/utility.h"

void drawPixel(int*, int, int);

int main(int argc, char** argv) {
    FILE *fp = fopen(argv[1], "r");
    char* buff = malloc(11);

    int cycle = 0, len;
    int reg = 1;
    int *crt = calloc(240, sizeof(int));

    while(fgets(buff, 11, fp)) {
        if (!strncmp(buff, "n", 1)) {
            drawPixel(crt, cycle++, reg);
        }
        else {
            buff += 5;
            len = 0;
            while(!strncmp(buff, "-", 1) || isdigit((buff)[0])) {
                ++len;
                ++buff;
            }
            buff -= len;
            drawPixel(crt, cycle++, reg);
            drawPixel(crt, cycle++, reg);
            reg += convertToNumber(buff, len);
        }
    }
    fclose(fp);

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 40; ++j) {
            printf("%c", (crt[j + i*40] == 1) ? '#' : ' ');
        }
        printf("\n");
    }
    free(crt);
    return 0;
}

void drawPixel(int* g, int cycle, int reg) {
    if ((reg >= ((cycle%40) - 1)) && (reg <= ((cycle%40) + 1))) {
        g[cycle] = 1;
    }
}