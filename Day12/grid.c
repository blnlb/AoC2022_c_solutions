#include "grid.h"

#define MIN(A,B) ((B) ^ ((A ^ B) & -(A < B)))
#define MAX(A,B) ((A) ^ ((A ^ B) & -(A < B)))

struct grid {
    int ** elevation;
    int width;
    int height;
    bool ** visited;
    int stepsFromHere;
};

grid *createGrid(int width, int height) {
    grid *result = malloc(sizeof(grid));
    result->width = width;
    result->height = height;
    result->elevation = calloc(width, sizeof(int*));
    result->visited = calloc(width, sizeof(bool*));
    for (int i = 0; i < width; ++i) {
        result->elevation[i] = calloc(height, sizeof(int));
        result->visited[i] = calloc(height, sizeof(bool));
    }
    result->stepsFromHere = INT_MAX;

    return result;
}

int heuristic(int *a, int *b) {
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

// next step: incorporate flag that says "DON'T LOOK BACK and cause an endless loop"
// flag turned out to be moving the visited array and creating one for each guy.

int testDirection(grid *map, int x, int y, int endx, int endy, int lastEl, int numSteps) {
    if ((x < WIDTH) && (x >= 0) &&
        (y < HEIGHT) && (y >= 0) &&
        (map->elevation[x][y] <= lastEl + 1) &&
        (map->elevation[x][y] >= lastEl) &&
        !(map->visited[x][y])) {
        return countSteps(map, x, y, endx, endy, numSteps + 1);
    }
    return INT_MAX;
}

int countSteps(grid* map, int x, int y, int endx, int endy, int numSteps) {
    if (x == endx && y == endy) return numSteps;
    map->visited[x][y] = true;
    int currEl = map->elevation[x][y]; 
    int t0, t1, t2, t3;
    // look at every direction
    t0 = testDirection(map, x+1, y, endx, endy, currEl, numSteps);
    t1 = testDirection(map, x-1, y, endx, endy, currEl, numSteps);
    t2 = testDirection(map, x, y+1, endx, endy, currEl, numSteps);
    t3 = testDirection(map, x, y-1, endx, endy, currEl, numSteps);
    
    map->visited[x][y] = false; 
    return MIN(t0, MIN(t1, MIN(t2, t3)));
}


