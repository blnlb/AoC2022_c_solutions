#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "../headers/utility.h"

#define GRID_WIDTH 1200
#define NUM_KNOTS 10

struct grid {
    int * visited;
    int * knots;
};

typedef struct grid grid;
typedef unsigned int uint;


grid *createGrid(int width, int pos_begin) {
    grid *res = malloc(sizeof(grid));
    res->visited = calloc(GRID_WIDTH*GRID_WIDTH, sizeof(int));
    res->visited[pos_begin] = 1;
    res->knots = calloc(NUM_KNOTS, sizeof(int));
    for (int i = 0; i < NUM_KNOTS; ++i) {
        res->knots[i] = pos_begin;
    }
    return res;
}
void destroyGrid(grid *input) {
    free(input->visited);
    free(input);
}

void moveDown(grid *input, int);
void move(grid *input, int, int);
void moveLeft(grid *input, int);
void moveRight(grid *input, int);
bool adjacent(int, int);
int follow(int pos1, int pos2);

int main(int argc, char** argv) {
    FILE *fp = fopen(argv[1], "r");
    char* buff = malloc(6);
    char dir;
    uint steps;

    // create a grid that's... probably big enough
    // and place yourself riiiiiiiggghhtt in the middle
    int pos = GRID_WIDTH*GRID_WIDTH/2+GRID_WIDTH/2;
    grid *tightrope = createGrid(GRID_WIDTH, pos);

    while (fgets(buff, 6, fp)) {
        dir = buff[0];
        steps = atoi(buff+2);
        switch (dir) {
            case 'D':
                move(tightrope, steps, GRID_WIDTH);
                break;
            case 'U':
                move(tightrope, steps, -GRID_WIDTH);
                break;
            case 'L': 
                move(tightrope, steps, -1);
                break;
            case 'R':
                move(tightrope, steps, 1);
                break;
            default:
                printf("You shouldn't see this message.\n");
                break;
        }
    }
    
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            printf("%c", tightrope->visited[i*GRID_WIDTH + j] > 0 ? '#' : '.');
        }
        printf("\n");
    }

    int totalSize = GRID_WIDTH*GRID_WIDTH, sum = 0;
    for (int i = 0; i < totalSize; ++i) {
        if (tightrope->visited[i] > 0) ++sum;
    }
    printf("%d\n", sum);
    destroyGrid(tightrope);
    return 0;
}

void move(grid *input, int steps, int dist) {
    while (steps-- > 0) {
        input->knots[0] += dist;
        for (int i = 0; i < NUM_KNOTS - 1; ++i) {
            input->knots[i+1] = follow(input->knots[i], input->knots[i+1]);
            if ((i + 2) == NUM_KNOTS){ 
                ++(input->visited[input->knots[i+1]]);
                break;
            }
        }
     }
}

int follow(int pos1, int pos2) {
    if (adjacent(pos1, pos2)) return pos2;
    if ((pos1 % GRID_WIDTH) == (pos2 % GRID_WIDTH))  
        return (pos2 < pos1) ? 
                pos2 + GRID_WIDTH: 
                pos2 - GRID_WIDTH;
    else if (floor(pos2/GRID_WIDTH) == floor(pos1/GRID_WIDTH)) 
        return (pos2 < pos1) ? pos2 + 1 : pos2 - 1;
    else {
        int x_diff = ((pos2 % GRID_WIDTH) < (pos1 % GRID_WIDTH)) ? 1 : -1;
        int y_diff = (pos2 < pos1) ? 1: -1;
        return pos2 + x_diff + GRID_WIDTH*y_diff;
    }
}


bool adjacent(int pos1, int pos2) {
    return (pos2 == pos1 ||
            pos2 == pos1 + 1 || pos2 == pos1 - 1 ||
            pos2 == pos1 + GRID_WIDTH || pos2 == pos1 - GRID_WIDTH ||
            pos2 == pos1 + GRID_WIDTH - 1 || pos2 == pos1 + GRID_WIDTH + 1 ||
            pos2 == pos1 - GRID_WIDTH - 1 || pos2 == pos1 - GRID_WIDTH + 1);
}