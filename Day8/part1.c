#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../headers/utility.h"

#define GRID_WIDTH 99

int **createGrid(int row_length, int col_length);
void destroyGrid(int **grid, int col_length);
bool isVisible(int ** grid, int row, int col);
bool checkLeft(int **grid, int row, int col);
bool checkRight(int **grid, int row, int col);
bool checkUp(int **grid, int row, int col);
bool checkDown(int **grid, int row, int col);

int main(int argc, char** argv) {
    FILE *fp = fopen("input.txt", "r");
    char* buff = malloc(103);
    
    int **grid = createGrid(GRID_WIDTH, GRID_WIDTH);

    int col, row = 0;
    while (fgets(buff, 103, fp)) {
        for (col = 0; col < GRID_WIDTH; ++col) {
            grid[row][col] = buff[col] - '0';
        }
        ++row;
    }
    fclose(fp);
    free(buff);

    int numVisible = 0;
    for (row = 0; row < GRID_WIDTH; ++row) {
        for (col = 0; col < GRID_WIDTH; ++col) {
            if (isVisible(grid, row, col)) ++numVisible;
        }
    }

    printf("%d\n", numVisible);
    destroyGrid(grid, GRID_WIDTH);
    return 0;
}

int **createGrid(int row_length, int col_length) {
    int **grid = calloc(col_length, sizeof(int*));
    for (int row = 0; row < col_length; ++row) {
        grid[row] = calloc(row_length, sizeof(int));
    }
    return grid;
}

void destroyGrid(int **grid, int col_length) {
    for (int row = 0; row < col_length; ++row) {
        free(grid[row]);
    }
    free(grid);
}

bool isVisible(int ** grid, int row, int col) {
    if (row == 0 || row == GRID_WIDTH - 1 ||
        col == 0 || col == GRID_WIDTH - 1) return true;
    return checkUp(grid, row, col) || checkDown(grid, row, col) ||
            checkLeft(grid, row, col) || checkRight(grid, row, col);
}

bool checkLeft(int **grid, int row, int col) {
    for (int i= 0; i < col; ++i) {
        if (grid[row][i] >= grid[row][col]) return false;
    }
    return true;
}

bool checkRight(int **grid, int row, int col) {
    for (int i = GRID_WIDTH - 1; i > col; --i) {
        if (grid[row][i] >= grid[row][col]) return false;
    }
    return true;
}

bool checkUp(int **grid, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (grid[i][col] >= grid[row][col]) return false;
    }
    return true;
}

bool checkDown(int **grid, int row, int col) {
    for (int i = GRID_WIDTH - 1; i > row; --i) {
        if (grid[i][col] >= grid[row][col]) return false;
    }
    return true;
}