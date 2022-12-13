#ifndef GRID
#define GRID

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#define WIDTH 162
#define HEIGHT 41

struct grid;
typedef struct grid grid;

grid *createGrid(int , int );
int testDirection(grid *map, int x, int y, int endx, int endy, int lastEl, int numSteps);
int countSteps(grid* map, int x, int y, int endx, int endy, int numSteps);


#endif