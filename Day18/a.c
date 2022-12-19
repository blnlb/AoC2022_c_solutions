#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

bool checkInSet(int **set, int setLength, int x, int y, int z) {
    for (int i = 0; i < setLength; ++i) {
        if (set[i][0] == x && set[i][1] == y && set[i][2] == z) return true;
    }
    return false;
}

void cubefill(int ***map, int x, int y, int z, int len) {
    if (map[x][y][z]) return;
    map[x][y][z] = 1;
    if (x > 0) cubefill(map, x - 1, y, z, len);
    if (y > 0) cubefill(map, x, y - 1, z, len);
    if (z > 0) cubefill(map, x, y, z - 1, len);
    if (x < len - 1) cubefill(map, x + 1, y, z, len);
    if (y < len - 1) cubefill(map, x, y + 1, z, len);
    if (z < len - 1) cubefill(map, x, y, z + 1, len);
}

// my second much simpler algorithm for this
// the first algorithm I used for part 1 parsed numbers without building a grid
// so it used a lot of edge-case math to achieve a niche result
// as such, it couldn't really handle distinctions from inside versus outside the grid
int countAdj2(int ***map, int len) {
    int total = 0;
    for (int x = 0; x < len; ++x)
    for (int y = 0; y < len; ++y)
    for (int z = 0; z < len; ++z) {
        if (map[x][y][z]) {
            if (z > 0 && !map[x][y][z-1]) ++total;
            if (y > 0 && !map[x][y-1][z]) ++total;
            if (x > 0 && !map[x-1][y][z]) ++total;
            if (z < len-1 && !map[x][y][z+1]) ++total;
            if (y < len-1 && !map[x][y+1][z]) ++total;
            if (x < len-1 && !map[x+1][y][z]) ++total;
        }
    }
    return total;
}

int main(int argc, char **argv) {
    char *filename = argv[1] ? argv[1] : "example.txt";
    FILE *fp = fopen(filename, "r");
    int buff = 21800;
    char *line = (char *)malloc(buff);

    //preprocess the input file length
    int numLines = !strcmp(filename, "example.txt") ? 13 : 2698;
    int i, j, k, num;
    
    int **allCoor = calloc(numLines, sizeof(int*));
    for (i = 0; i < numLines; ++i) {
        allCoor[i] = calloc(3, sizeof(int));
    }
    i = 0;
    // gather all of the input into a 2d array
    while (fgets(line, buff, fp)) {
        for (j = 0; j < 3; ++j) {
            num = 0;
            while (isdigit(*line))
                num = num * 10 + *(line++) - '0';
            allCoor[i][j] = num;
            if (*line == ',')
                ++line;
        }
        ++i;
    }

    // create an empty cube
    int*** map = (int ***)calloc(24, sizeof(int**));
    for (i = 0; i < 24; ++i) {
        map[i] = (int**)calloc(24, sizeof(int*));
        for (j = 0; j < 24; ++j) {
            map[i][j] = calloc(24, sizeof(int));
        }
    }
    
    //generate lava from data
    for (i = 0; i < 23; ++i) {
        for (j = 0; j < 23; ++j) {   
            for (k = 0; k < 23; ++k) {
                if (checkInSet(allCoor, numLines, i, j, k)) {
                    map[i+1][j+1][k+1] = 1;
                }
            }
        }
    }

    // count current adjacencies using recursive call
    int adj1 = countAdj2(map, 24);
    //fill the negative space
    cubefill(map, 0,0,0, 24);
    // count the adjacencies inside the cube
    // (we'll subtract these from the original answer to get part 2)
    int adj2 = countAdj2(map, 24);

    printf("Part 1: %d\n", adj1);
    printf("Part 2: %d\n", adj1 - adj2);
    
}