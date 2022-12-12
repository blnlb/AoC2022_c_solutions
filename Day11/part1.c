#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../headers/utility.h"
#include "monkey.c"

int cmp(const void* a, const void* b) {
    return *(ulong*)(a) - *(ulong*)(b);
}

// the most shamelessly hard-coded and preprocessed program I've ever created
int main(int argc, char** argv) {
    int i, j;

    // set up the monkeys!!!!
    monkey **monkeys = calloc(8, sizeof(monkey*));
    for (i = 0; i < 8; ++i) {
        monkeys[i] = malloc(sizeof(monkey));
    }
    monkeys[0] = createMonkey(set0, 4, m0, t0);
    monkeys[1] = createMonkey(set1, 8, m1, t1);
    monkeys[2] = createMonkey(set2, 2, m2, t2);
    monkeys[3] = createMonkey(set3, 3, m3, t3);
    monkeys[4] = createMonkey(set4, 1, m4, t4);
    monkeys[5] = createMonkey(set5, 6, m5, t5);
    monkeys[6] = createMonkey(set6, 5, m6, t6);
    monkeys[7] = createMonkey(set7, 7, m7, t7);

    // simulate the rounds!!!
    for (i = 0; i < 10000; ++i) {
        for (j = 0; j < 8; ++j) {
            deQueue(j, monkeys);
        }
    }

    // get the top number of inspections here.
    ulong *topInspections = calloc(2, sizeof(ulong));
    for (j = 0; j < 8; ++j) {
        if (monkeys[j]->numInspected > topInspections[0]) {
            topInspections[0] = monkeys[j]->numInspected;
            qsort(topInspections, 2, sizeof(ulong), cmp);
        }
    }

    // print the absurdly large value
    printf("\n%lu\n", topInspections[0]*topInspections[1]);

    free(topInspections);
    for (i = 0; i < 8; ++i) {
        destroyMonkey(monkeys[i]);
    }
    free(monkeys);

    return 0;
}