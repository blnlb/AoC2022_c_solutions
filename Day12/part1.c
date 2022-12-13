#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "grid.c"

 
int main(int argc, char** argv) {
    FILE *fp = fopen("input.txt", "r");
    char *buff = malloc(WIDTH + 3);

    grid* map = createGrid(WIDTH, HEIGHT);
    int *start = calloc(2, sizeof(int));
    int *end = calloc(2, sizeof(int));
    int row = 0, col;

    while (fgets(buff, WIDTH + 3, fp)) {
        for (col = 0; strncmp(buff + col, "\n", 1) && strncmp(buff + col, "\0", 1); ++col) {
            if (!strncmp(buff + col, "S", 1)) {
                start[0] = col, start[1] = row;
                map->elevation[col][row] = 0;
            }
            else if (!strncmp(buff + col, "E", 1)) {
                end[0] = col, end[1] = row;
                map->elevation[col][row] = 25;
            }
            else {
                map->elevation[col][row] = buff[col] - 'a';
            }
        }
        ++row;
    }
    fclose(fp);

    while (sizeof(map->visited) != map->)
    int shortest = countSteps(map, start[0], start[1], end[0], end[1], 0);

    printf("%d\n", shortest);

    return 0;
}