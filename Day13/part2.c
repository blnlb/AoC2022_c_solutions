#include <stdlib.h>
#include <stdio.h>


#include "parser.c"

int main(int argc, char **argv)
{
    int numLines = read(argv[1]);
    allLines[numLines++] = insertDumbDivider(2 + '0');
    allLines[numLines++] = insertDumbDivider(6 + '0');
    qsort(allLines, numLines, sizeof(*allLines), sort);

    int index_mult = 1;
    for (int i = 0; i < numLines; ++i) {
        if (allLines[i]->divider) {
            index_mult *= (i + 1);
        }
    }

    printf("%d\n", index_mult);
    for (int i = 0; i < numLines; ++i) {
        destroyNode(allLines[i]);
    }

    return 0;
}