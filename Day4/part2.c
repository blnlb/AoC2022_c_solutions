#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char** argv) {
    char buff[70];
    const char* filename = argv[1];
    FILE *fp = fopen(filename, "r");
    char *mid = malloc(5);
    long *range1 = calloc(2, sizeof(long)), *range2 = calloc(2, sizeof(long));

    int howmany = 0;
    while (fgets(buff, 14, fp)) {
        mid = strtok(buff, "-");
        range1[0] = strtol(mid, NULL, 10);
        mid = strtok(NULL, ",");
        range1[1] = strtol(mid, NULL, 10);
        mid = strtok(NULL, "-");
        range2[0] = strtol(mid, NULL, 10);
        mid = strtok(NULL, "\n");
        range2[1] = strtol(mid, NULL, 10);
        if ((range1[0] >= range2[0] && range1[0] <= range2[1]) ||
            (range2[0] >= range1[0] && range2[0] <= range1[1])) {
                ++howmany;
            } 
    }

    printf("%d\n", howmany);
    fclose(fp);
    free(mid); free(range1); free(range2);
    return 0;
}
