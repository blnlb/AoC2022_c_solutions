#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../headers/utility.h"

#define GRID_WIDTH 600

struct grid {
    int * visited;
    int pos_T, pos_H;
};

typedef struct grid grid;
typedef unsigned int uint;


grid *createGrid(int width, int pos_begin) {
    grid *res = malloc(sizeof(grid));
    res->visited = calloc(GRID_WIDTH*GRID_WIDTH, sizeof(int));
    res->pos_H = pos_begin;
    res->pos_T = pos_begin;
    return res;
}
void destroyGrid(grid *input) {
    free(input->visited);
    free(input);
}

void moveDown(grid *input, int);
void moveUp(grid *input, int);
void moveLeft(grid *input, int);
void moveRight(grid *input, int);
bool adjacent(int, int);

int main(int argc, char** argv) {
    FILE *fp = fopen("input.txt", "r");
    char* buff = malloc(6);
    char dir;
    uint steps;

    // create a grid that's... probably big enough
    // and place yourself riiiiiiiggghhtt in the middle
    int pos = GRID_WIDTH*GRID_WIDTH/2+GRID_WIDTH/2;
    grid *tightrope = createGrid(GRID_WIDTH, pos);
    tightrope->visited[pos] = 1;

    while (fgets(buff, 6, fp)) {
        dir = buff[0];
        steps = atoi(buff+2);
        switch (dir) {
            case 'D':
                moveDown(tightrope, steps);
                break;
            case 'U':
                moveUp(tightrope, steps);
                break;
            case 'L': 
                moveLeft(tightrope, steps);
                break;
            case 'R':
                moveRight(tightrope, steps);
                break;
            default:
                printf("You shouldn't see this message.\n");
                break;
        }
    }

    int totalSize = GRID_WIDTH*GRID_WIDTH, sum = 0;
    for (int i = 0; i < totalSize; ++i) {
        if (tightrope->visited[i] > 0) ++sum;
    }
    
    printf("%d\n", sum);
    destroyGrid(tightrope);
    return 0;
}

void moveDown(grid *input, int steps) {
    int lastPos;
    while (steps-- > 0) {
        lastPos = input->pos_H;
        input->pos_H = lastPos + GRID_WIDTH;
        if (!adjacent(input->pos_H, input->pos_T)) {
            input->pos_T = lastPos;
            ++(input->visited[input->pos_T]);
        }
    }
}

void moveUp(grid *input, int steps) {
    int lastPos;
    while (steps-- > 0) {
        lastPos = input->pos_H;
        input->pos_H = lastPos - GRID_WIDTH;
        if (!adjacent(input->pos_H, input->pos_T)) {
            input->pos_T = lastPos;
            ++(input->visited[input->pos_T]);
        }
    }
}

void moveLeft(grid *input, int steps) {
    int lastPos;
    while (steps-- > 0) {
        lastPos = input->pos_H;
        input->pos_H = lastPos - 1;
        if (!adjacent(input->pos_H, input->pos_T)) {
            input->pos_T = lastPos;
            ++(input->visited[input->pos_T]);
        }
    }
}

void moveRight(grid *input, int steps) {
    int lastPos;
    while (steps-- > 0) {
        lastPos = input->pos_H;
        input->pos_H = lastPos + 1;
        if (!adjacent(input->pos_H, input->pos_T)) {
            input->pos_T = lastPos;
            ++(input->visited[input->pos_T]);
        }
    }
}

bool adjacent(int pos1, int pos2) {
    return (pos2 == pos1 ||
            pos2 == pos1 + 1 || pos2 == pos1 - 1 ||
            pos2 == pos1 + GRID_WIDTH || pos2 == pos1 - GRID_WIDTH ||
            pos2 == pos1 + GRID_WIDTH - 1 || pos2 == pos1 + GRID_WIDTH + 1 ||
            pos2 == pos1 - GRID_WIDTH - 1 || pos2 == pos1 - GRID_WIDTH + 1);
}