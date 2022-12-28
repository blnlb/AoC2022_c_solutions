#ifndef GRID24
#define GRID24

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

enum direction {right = 0, down, left, up};

typedef struct blizzard {
    int x;
    int y;
    int direction;
} blizzard;

blizzard* createBlizzard(int x, int y, int dir) {
    blizzard *result = (blizzard*)calloc(1, sizeof(blizzard));
    result->x=x;
    result->y=y;
    result->direction=dir;
    return result;
}

typedef struct grid {
    blizzard **blizzies;
    int width;
    int height;
    int blizCount;
    int *end;
    int *begin;
} grid;

grid * createGrid(int width, int height, blizzard ** b, int blizCount) {
    grid *result = (grid*)calloc(1, sizeof(grid));
    result->blizCount = blizCount;
    result->width = width;
    result->height = height; 
    result->end = (int*)calloc(2, sizeof(int));
    result->begin = (int*)calloc(2, sizeof(int));
    result->begin[0] = 1; result->begin[1] = 0;
    result->end[0] = width - 2; result->end[1] = height - 1;
    result->blizzies = (blizzard**)calloc(result->blizCount, sizeof(blizzard*));
    for (int i = 0; i < result->blizCount; ++i) {
        result->blizzies[i] = (blizzard*)calloc(1, sizeof(blizzard));
        memcpy(result->blizzies[i], b[i], sizeof(blizzard));
    }
    return result;
}

void swapPositions(int *a, int *b) {
    int temp = a[0];
    a[0] = b[0];
    b[0] = temp;
    temp = a[1];
    a[1] = b[1];
    b[1] = temp;
}

blizzard **initBlizzards(const char *f, int *total) {
    FILE *fp = fopen(f, "r");
    int buff = 126;
    char *line = (char*)malloc(buff);

    // inital pass to find the number
    *total = 0;
    int i;
    while (fgets(line, buff, fp)) {
        i = 0;
        while (line[i] != '\n') {
            if (line[i] != '.' && line[i] != '#') ++(*total);
            ++i;
        }
    }
    
    freopen(f,"r", fp);
    blizzard **result = (blizzard**)calloc(*total, sizeof(blizzard*));
    int blizcount = 0;
    // second pass for exact positions
    int j = 0;
    while (fgets(line, buff, fp)) {
        i = 0;
        while (line[i] != '\n') {
            switch (line[i]) {
                case '>':
                    result[blizcount++] = createBlizzard(i, j, right);
                    break;
                case 'v':
                    result[blizcount++] = createBlizzard(i, j, down);
                    break;
                case '<':
                    result[blizcount++] = createBlizzard(i, j, left);
                    break;
                case '^':
                    result[blizcount++] = createBlizzard(i, j, up);
                    break;
            }
            ++i;
        }
        ++j;
    }
    return result;
}


void *updateBlizzards(grid *newMap) {
    for (int i = 0; i < newMap->blizCount; ++i) {
        switch (newMap->blizzies[i]->direction) {
            case right:
                if (newMap->blizzies[i]->x == newMap->width - 2) {
                    newMap->blizzies[i]->x = 1;
                }
                else {  
                    ++newMap->blizzies[i]->x;
                }
                break;
            case down:
            if (newMap->blizzies[i]->y == newMap->height - 2) {
                    newMap->blizzies[i]->y = 1;
                }
                else {  
                    ++newMap->blizzies[i]->y;
                } 
                break;
            case left:
                if (newMap->blizzies[i]->x == 1) {
                    newMap->blizzies[i]->x = newMap->width - 2;
                }
                else {  
                    --newMap->blizzies[i]->x;
                } 
                break;
            case up:
                if (newMap->blizzies[i]->y == 1) {
                    newMap->blizzies[i]->y = newMap->height - 2;
                }
                else {  
                    --newMap->blizzies[i]->y;
                } 
                break;
        }
    }
    return newMap;
}

// result[t][y][x] stores how many blizzards are in pos=(x,y) and t=day
int *** precalc(grid *map) {
    //the number of days cycles every rownum*colnum
    int cycleLength = (map->width - 2)*(map->height - 2);
    int ***result = (int***)calloc(cycleLength, sizeof(int**));
    int t, i, b;
    for (t = 0; t < cycleLength; ++t) {
        // properly initiate this day to 0s
        result[t] = (int**)calloc(map->height, sizeof(int*));
        for (i = 0; i < map->height; ++i) {
            result[t][i] = (int*)calloc(map->width, sizeof(int));
        }
        // hash the blizzards into the map, moving them by one to fit
        for (b = 0; b < map->blizCount; ++b) {
            ++(result[t][map->blizzies[b]->y][map->blizzies[b]->x]);
        }
        // blizzards move one minute
        updateBlizzards(map);
    }
    return result;
}



#endif