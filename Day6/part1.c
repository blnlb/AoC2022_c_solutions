#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAXCHARS 4100

int main(int argc, char** argv) {
    const char* filename = argv[1];
    char *buff = malloc(MAXCHARS);
    FILE *fp = fopen(filename, "r");
    fgets(buff, MAXCHARS, fp);

    int i = 0;
    char* window = malloc(5);
    for (i; i < MAXCHARS;) {
        strncpy(window, buff + i, 4);
        if (!strncmp(window, window + 1, 1) ||
            !strncmp(window, window + 2, 1) ||
            !strncmp(window, window + 3, 1)) ++i;
        else if (!strncmp(window + 1, window + 2, 1) ||
                 !strncmp(window + 1, window + 3, 1)) i += 2;
        else if (!strncmp(window + 2, window + 3, 1)) i += 3;
        else {
            printf("%d\n", i + 4);
            break;
        }
    }


    return 0;
}
