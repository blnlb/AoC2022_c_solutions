#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int cmp(const void *a, const void *b) {
   return (int)(*(char*)a - *(char*)b);
}

int main(int argc, char** argv) {
    char buff[70];
    const char* filename = argv[1];
    FILE *fp = fopen(filename, "r");

    int sum = 0, len;
    
    int ctr = 1;
    bool getOut;
    while(fgets(buff, 70, fp) != NULL) {
        printf("%d", ctr++);
        char *comp1, *comp2;
        getOut = false;
        len = strlen(buff)>>1;
        comp1 = malloc(len + 1);
        comp2 = malloc(len + 1);
        strncpy(comp1, buff, len);
        strncpy(comp2, buff+len, len);
        comp1[len] = '\0'; comp2[len] = '\0';

        for (int i = 0; i < len; ++i) {
            if (getOut) break;
            for (int j = 0; j < len; ++j) {
                if (getOut) break;
                if (!strncmp(comp1 + i, comp2 + j, 1)) {
                    printf(": %c\n", comp1[i]);
                    sum += islower(comp1[i]) ? comp1[i] - 'a' + 1 : comp1[i] - 'A' + 27;
                    getOut = true;
                }
            }
        }
        free(comp1); free(comp2);
    }
    printf("%d\n", sum);
    fclose(fp);

    return 0;
}