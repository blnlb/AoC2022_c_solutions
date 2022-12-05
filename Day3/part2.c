#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    char buff1[70], buff2[70], buff3[70];
    const char* filename = argv[1];
    FILE *fp = fopen(filename, "r");

    int sum = 0, len1, len2, len3, i, j, k;
    char theChosenOne;
    
    int ctr = 1;
    bool getOut;
    while(fgets(buff1, 70, fp) != NULL) {
        fgets(buff2, 70, fp);
        fgets(buff3, 70, fp);
        getOut = false;
        len1 = strlen(buff1);
        len2 = strlen(buff2);
        len3 = strlen(buff3);

        getOut = false;
        for (i = 0; i < len1 && !getOut; ++i) {
            for (j = 0; j < len2 && !getOut; ++j) {
                if (!strncmp(buff1 + i, buff2 + j, 1)) {
                    for (k = 0; k < len3; ++k) {
                        if (!strncmp(buff2 + j, buff3 + k, 1)) {
                            theChosenOne = *(buff3 + k);
                            getOut = true;
                            break;
                        }
                    }
                }
            }
        }
        sum += islower(theChosenOne) ? theChosenOne - 'a' + 1 : theChosenOne - 'A' + 27;
    }
    printf("%d\n", sum);
    fclose(fp);

    return 0;
}