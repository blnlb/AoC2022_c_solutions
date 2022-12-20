#ifndef DAY19QUEUE
#define DAY19QUEUE

#include <stdlib.h>
#include <string.h>

typedef struct state {
    int timeLeft;
    int r1, r2, r3, r4;
    int ore, clay, obsidian, geode;
} state;

state *createState(int ge, int r1, int r2, int r3, int r4, int ore, int clay, int obsidian, int geode) {
    state* result = (state*)calloc(1, sizeof(state));
    result->timeLeft = ge;
    result->r1=r1;
    result->r2=r2;
    result->r3=r3;
    result->r4=r4;
    result->ore = ore;
    result->clay = clay;
    result->obsidian=obsidian;
    result->geode=geode;
    return result;
}

void destroyState(state* s) {
    free(s);
}

#endif