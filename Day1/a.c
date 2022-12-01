#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b);
}

int main(int argc, char** argv) {
    int tally = 0;
    char buff[10];
    int *top3 = calloc(3, sizeof(int));
    const char* filename = argv[1];

    FILE *fp;
    fp = fopen(filename, "r");

    while(fgets(buff, 10, fp)) {
        if (strcmp(buff, "\n")) {
            tally += atoi(buff);
        } else {
            if (tally > top3[0]){ 
                top3[0] = tally;
                qsort(top3, 3, sizeof(int), cmpfunc);
            }
            tally = 0;
        }
    }

    int sum = top3[0] + top3[1] + top3[2];
    printf("%d.\n", sum);

    return 0;
}