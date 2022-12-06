#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAXCHARS 4100
#define DISTINCT_CHAR 14

int main(int argc, char** argv) {
    const char* filename = argv[1];
    char *buff = malloc(MAXCHARS);
    FILE *fp = fopen(filename, "r");
    fgets(buff, MAXCHARS, fp);

    int i = 0;
    int j, k;
    char* window = malloc(DISTINCT_CHAR + 1);
    bool found = true;
    bool same;
    while (i < MAXCHARS) {
        same = false;
        strncpy(window, buff + i, DISTINCT_CHAR);
        for (j = 0; j < DISTINCT_CHAR - 1; ++j) {
            if (same) break;
            for (k = j + 1; k < DISTINCT_CHAR; ++k) {
                if (!strncmp(window + j, window + k, 1))  {
                    i += j + 1;
                    same = true;
                    break;
                }
                if (j == DISTINCT_CHAR - 2 && k == DISTINCT_CHAR - 1) {
                    printf("%d\n", i + DISTINCT_CHAR);
                    fclose(fp); free(window); free(buff);
                    return 0;
                }
            }
        }
    }
    fclose(fp); free(window); free(buff);
    printf("No message found.\n");
    return -1;
}
