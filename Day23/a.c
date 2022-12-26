#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define MAXELVES 27040000

typedef struct elf {
    int x;
    int y;
    int potential_x;
    int potential_y;
} elf;


bool checkAdjacencies(elf* e, int e_index, elf** elves, int totalElves);
void roundOne(elf* e, int e_index, elf** elves, int totalElves, int directionStart);
void roundTwo(elf* e, int e_index, elf** elves, int totalElves);
bool north(elf* e, int e_index, elf** elves, int totalElves);
bool south(elf* e, int e_index, elf** elves, int totalElves);
bool west(elf* e, int e_index, elf** elves, int totalElves);
bool east(elf* e, int e_index, elf** elves, int totalElves);

// enum startDirection {
//     north = 0,
//     south, west, east,
//     numDirections
// };

elf *createElf(int x, int y) {
    elf* result = calloc(1, sizeof(elf));
    result->x=x;
    result->y=y;
    result->potential_x=x;
    result->potential_y=y;
    return result;
}

int main(int argc, char **argv) {
    const char *filename = argv[1] ? argv[1] : "example.txt";
    FILE *fp = fopen(filename, "r");
    int buff = 5200;
    char *line = malloc(buff);

    elf **elves = calloc(MAXELVES, sizeof(elf*));
    for (int i = 0; i < MAXELVES; ++i) {
        elves[i] = calloc(1, sizeof(elf));
    }

    int elfNumber = 0, i = 0, j = 0;
    while (fgets(line, buff, fp)) {
        i = 0;
        while (line[i] != '\n') {
            if (line[i] == '#') {
                elves[elfNumber++] = createElf(i, j);
            }
            ++i;
        }
        ++j;
    }

    int iterations = 0;
    int rot = 0;
    int numAdjacencies, xMax, yMax, xMin, yMin;
    while (++iterations) {
        // round 1
        numAdjacencies = 0;
        for (i = 0; i < elfNumber; ++i) {
            if (checkAdjacencies(elves[i], i, elves, elfNumber)) {
                ++numAdjacencies;
                continue;
            }
            roundOne(elves[i], i, elves, elfNumber, rot);
        }
        if (numAdjacencies == elfNumber) {
            printf("Part 2: %d\n", iterations);
            break;
        }
        // round 2
        for (i = 0; i < elfNumber; ++i) {
            roundTwo(elves[i], i, elves, elfNumber);
        }
        rot = (rot + 1) % 4;
        if (iterations == 10) {
            xMin = INT_MAX;
            yMin = INT_MAX;
            xMax = INT_MIN;
            yMax = INT_MIN;
            for (i = 0; i < elfNumber; ++i) {
                if (elves[i]->x < xMin) xMin = elves[i]->x;
                if (elves[i]->x > xMax) xMax = elves[i]->x;
                if (elves[i]->y < yMin) yMin = elves[i]->y;
                if (elves[i]->y > yMax) yMax = elves[i]->y;
            }
            int total = (xMax-xMin + 1)*(yMax-yMin + 1) - elfNumber;
            printf("Part 1: %d\n", total);
        }
    }

    return 0;
}

void roundOne(elf* e, int e_index, elf** elves, int totalElves, int directionStart) {
    int total = 4;
    while (total--) {
        switch (directionStart) {
            case 0: 
                if (north(e, e_index, elves, totalElves)) {
                    e->potential_y = e->y - 1;
                    return;
                }
                break;
            case 1:
                if (south(e, e_index, elves, totalElves)) {
                    e->potential_y = e->y + 1;
                    return;
                }
                break;
            case 2:
                if (west(e, e_index, elves, totalElves)) {
                    e->potential_x = e->x - 1;
                    return;
                }
                break;
            case 3:
                if (east(e, e_index, elves, totalElves)) {
                    e->potential_x = e->x + 1;
                    return;
                }
                break;
        }
        directionStart = (directionStart + 1) % 4;
    }
}

bool checkAdjacencies(elf* e, int e_index, elf** elves, int totalElves) {
    for (int i = 0; i < totalElves; ++i) {
        if (i == e_index) continue;
        if (abs(e->x - elves[i]->x) <= 1 && abs(e->y - elves[i]->y) <= 1) return false; 
    }
    return true;
}

bool north(elf* e, int e_index, elf** elves, int totalElves) {
    for (int i = 0; i < totalElves; ++i) {
        if (i == e_index) continue;
        if (e->y == elves[i]->y + 1 && abs(e->x - elves[i]->x) <= 1) 
            return false; 
    }
    return true;
}

bool south(elf* e, int e_index, elf** elves, int totalElves) {
    for (int i = 0; i < totalElves; ++i) {
        if (i == e_index) continue;
        if (e->y == elves[i]->y - 1 && abs(e->x - elves[i]->x) <= 1) 
            return false; 
    }
    return true;
}

bool west(elf* e, int e_index, elf** elves, int totalElves) {
    for (int i = 0; i < totalElves; ++i) {
        if (i == e_index) continue;
        if (e->x == elves[i]->x + 1 && abs(e->y - elves[i]->y) <= 1) 
            return false; 
    }
    return true;
}

bool east(elf* e, int e_index, elf** elves, int totalElves) {
    for (int i = 0; i < totalElves; ++i) {
        if (i == e_index) continue;
        if (e->x == elves[i]->x - 1 && abs(e->y - elves[i]->y) <= 1) 
            return false; 
    }
    return true;
}

void roundTwo(elf* e, int e_index, elf** elves, int totalElves) {
    for (int i = 0; i < totalElves; ++i) {
        if (i == e_index) continue;
        if (elves[i]->potential_x == e->potential_x && elves[i]->potential_y == e->potential_y) {
            elves[i]->potential_x = elves[i]->x;
            elves[i]->potential_y = elves[i]->y;
            e->potential_x = e->x;
            e->potential_y = e->y;
            return;
        }
    }
    e->x = e->potential_x;
    e->y = e->potential_y;
}