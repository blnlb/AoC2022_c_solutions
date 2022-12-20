#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../headers/utility.h"

#define MAX(A,B) ((A) ^ ((A ^ B) & -(A < B)))

#define COLUMNWIDTH 7
#define SNAPSHOTSIZE 30
#define PART2 1

typedef struct map {
    char **coordinate;
    long lowestRock;
    long highestRock;
} map;

typedef struct state {
    map* currMap;
    char *direction;
    int currentShape;
} state;

map* createMap(int size, int high, int low) {
    map* result = calloc(1, sizeof(map));
    result->lowestRock = low;
    result->highestRock = high;
    result->coordinate = calloc(size, sizeof(char*));
    for (int i = 0; i < size; ++i) {
        result->coordinate[i] = malloc(COLUMNWIDTH + 1);
        for (int j = 0; j < COLUMNWIDTH; ++j) {
            result->coordinate[i][j] = ' ';
        }
            result->coordinate[i][COLUMNWIDTH] = '\0';
    }
    strcpy(result->coordinate[0], "#######\0");
    return result;
}

state *createState(map* currMap, char *direction, int t) {
    state *result = calloc(1, sizeof(state));
    result->currMap = createMap(SNAPSHOTSIZE, currMap->highestRock, currMap->lowestRock);
    memcpy(result->currMap, currMap, SNAPSHOTSIZE);
    result->direction = malloc(strlen(direction) + 1);
    memcpy(result->direction, direction, strlen(direction));
    result->currentShape = t;
    return result;
}

char **buildNewRock(int index, int *total, int *width) {
    char **result = calloc(4, sizeof(char*));
    for (int i = 0; i < 4; ++i) {
        result[i] = malloc(8);
    }
    *total = 0;
    switch (index) {
        case 0:
            *total = 1;
            *width = 4;
            strncpy(result[0], "  #### \0", 8);
            break;
        case 1:
            *total = 3;
            *width = 3;
            strcpy(result[2], "   #   \0"); 
            strcpy(result[0], "   #   \0"); 
            strcpy(result[1], "  ###  \0"); 
            break;
        case 2:
            *total = 3;
            *width = 3;
            strcpy(result[2], "    #  \0");
            strcpy(result[1], "    #  \0");
            strcpy(result[0], "  ###  \0");
            break;
        case 3:
            *total = 4;
            *width = 1;
            for (int i = 0; i < 4; ++i) {
                strcpy(result[i], "  #    \0");
            }
            break;
        case 4:
            *total = 2;
            *width = 2;
            for (int i = 0; i < 2; ++i) {
                strcpy(result[i], "  ##   \0");
            }
            break;
        default:
            printf("Not a valid rock index.\n");
            return NULL;
    }
    return result;
}

// signature checks last SNAPSHOTSIZE squares
state * signature(map* currMap, char *direction, int t) {
    int ymax = currMap->highestRock;
    int check = MAX(0, ymax-SNAPSHOTSIZE-20);
    if (check == 0) return NULL;
    state *result = createState(currMap, direction, t);
    return result;
}

state * seen(state **allSignatures, int sigLength, state* curr) {
    for (int i = 0; i < sigLength; ++i) {
        if (curr->currentShape % 5 != allSignatures[i]->currentShape % 5 ||
            strcmp(curr->direction, allSignatures[i]->direction)) {
            continue;
        }
        for (int j = 0; j < 30; j++) {
            if (strncmp(curr->currMap->coordinate[j], allSignatures[i]->currMap->coordinate[j], 7))
                break;
            if (j == 29) return allSignatures[i];
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    char *filename = argv[1] ? argv[1] : "input.txt";
    FILE *fp = fopen(filename, "r");
    int buff = 10100;
    char *direction = malloc(buff);
    // input file is just one line
    fgets(direction, buff, fp);

    // when we get to the end of the input file, we'll need to loop back.
    // instead of making a linked loop, i'll just update the address
    // by subtracting the string length
    int totalDirectionCount = strlen(direction) - 1;

    //build map to fall from. Our falling will go from bottom to top,
    // so that the floor is at y = 0
    map* vent = createMap(2000000, 0, 4);

    // will need to track several branches using booleans
    bool rockFalling = false, touchingWall;
    int i = 0, j, k;
    int totalColumns = 1;
    long total = 0;
    char **currRock = calloc(5, sizeof(char*));
    for (int i = 0; i < 5; ++i) {
        currRock[i] = "       \0";
    }
    int neg = 1;

    // PART 2 CAVEATS
    bool jumpedAhead = false;
    long offset = 0;
    int width;
    state ** signatures = calloc(20000, sizeof(state*));
    state *sig = calloc(1, sizeof(state)), *found = calloc(1, sizeof(state));
    int signaturesLength = 0;
    long added = 0;

    // GAME LOOP
    long maxLoopage = 1000000000000;
    while (total < maxLoopage) {
        touchingWall = false;
        if (*direction == '\n') {
            direction -= totalDirectionCount;
        } 
        // If there is no rock falling, let's create a new rock and update some values
        if (!rockFalling) {
            currRock = buildNewRock(i++, &totalColumns, &width);
            i %= 5;
            rockFalling = true;
        }

        //get the wind direction
        neg = *direction == '<' ? -1 : 1;
        // find out if touching wall.
        for (j = 0; j < totalColumns; ++j) {
            if ((neg == -1 && currRock[j][0] == '#') ||
                (neg == 1 && currRock[j][COLUMNWIDTH - 1] == '#')) {
                touchingWall = true;
                break;
            }
        }
        // we also could be touching another rock, so...
        for (j = 0; j < totalColumns; ++j) {
            
            if (neg == 1) {
                k = 0;
                while (currRock[j][k] != '#') ++k;
                while (currRock[j][k] == '#') ++k;
                if (vent->coordinate[vent->lowestRock + j][k] == '#') {
                    touchingWall = true;
                    break;
                }
            }
            else {
                k = COLUMNWIDTH - 1;
                while (currRock[j][k] != '#') --k;
                while (currRock[j][k] == '#') --k;
                if (vent->coordinate[vent->lowestRock + j][k] == '#') {
                    touchingWall = true;
                    break;
                }
            }
            
        }

        // if we're not touching the wall, we need to move left or right (works when not intersecting prev map)
        if (!touchingWall) {
            if (neg == -1) {
                for (j = 0; j < totalColumns; ++j) {
                    for (k = 0; k < 6; ++k) {
                        currRock[j][k] = currRock[j][k + 1];
                    }
                    currRock[j][6] = ' ';
                }
            }
            else {
                for (j = 0; j < totalColumns; ++j) {
                    for (k = COLUMNWIDTH - 1; k > 0; --k) { 
                        currRock[j][k] = currRock[j][k - 1];
                    }
                    currRock[j][0] = ' ';
                }
            }
        }
        // have we landed on a rock yet?
        if (vent->lowestRock <= vent->highestRock + 1) {
            for (j = 0; j < totalColumns; ++j) {
                for (k = 0; k < COLUMNWIDTH; ++k) {
                    if (currRock[j][k] == '#' && vent->coordinate[vent->lowestRock + j - 1][k] == '#') {
                        rockFalling = false;
                        break;
                    } 
                }
                if (!rockFalling) break;
            }
        }   

        // condition 1: keep falling.
        if (rockFalling) {
            --(vent->lowestRock);
        }
        // condition 2: drop the rock and move on
        else {
            for (j = 0; j < totalColumns; ++j) {
                for (int k = 0; k < COLUMNWIDTH; ++k) {
                    if (currRock[j][k] == '#')
                        vent->coordinate[vent->lowestRock + j][k] = '#';
                }
            }
            // calculate new rock total, highest rock, and where the next rock will fall from
            ++total; 
            vent->highestRock = MAX(vent->lowestRock + totalColumns - 1, vent->highestRock);
            vent->lowestRock = vent->highestRock + 4;

            if (!jumpedAhead) {
                state *sig = signature(vent, direction, total);
                if (sig) {
                    if ((found = seen(signatures, signaturesLength, sig))) {
                        int dy = vent->highestRock - found->currMap->highestRock;
                        long dt = total - found->currentShape;
                        long amt = (maxLoopage - total)/dt;
                        added = amt * (long)dy;
                        total += amt*dt;
                        printf("This is the total after jumping: %ld\n", total);
                        jumpedAhead = true;
                        for (j = 0; j < signaturesLength; ++j) {
                            free(signatures[j]->currMap);
                            free(signatures[j]);
                        }
                    }
                    else {
                        signatures[signaturesLength++] = sig;
                    }
                }
            }
        }
        ++direction;
    }

    printf("vent got to : %ld\nwe added: %ld\nfinal: %ld\n", (vent->highestRock), added, (vent->highestRock) + added);

    return 0;
}
