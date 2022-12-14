#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define MIN(A,B) ((B) ^ ((A ^ B) & -(A < B)))
#define MAX(A,B) ((A) ^ ((A ^ B) & -(A < B)))


typedef struct grid {
    int ** isRock;
    bool **isSand;
} grid;

grid *createGrid(int width, int height) {
    grid* result = calloc(1, sizeof(grid));
    result->isRock = (int**)calloc(height, sizeof(int*));
    result->isSand = (bool**)calloc(height, sizeof(bool*));
    for (int i = 0; i < height; ++i) {
        result->isRock[i] = calloc(width, sizeof(int));
        result->isSand[i] = calloc(width, sizeof(bool));
    }
    return result;
}

void createRocks(grid *map, char *filename, int xOffset) {
    FILE *fp = fopen(filename, "r");
    int buff = 350;
    char *line = malloc(buff);

    bool first;

    int x, y, lastx, lasty;
    int least, most, i;
    while (fgets(line, buff, fp)) {
        first = true;
        while (*line != '\0') {
            x = 0;
            y = 0;
            if (!first) {
                while (isdigit(*line))  {           
                    x = x * 10 + *(line++) - '0';
                }
                ++line;
                while (isdigit(*line))  {           
                    y = y * 10 + *(line++) - '0';
                }
                if (x != lastx) {
                    least = MIN(x, lastx);
                    most = MAX(x, lastx);
                    for (i = least; i <= most; ++i) {
                        map->isRock[y][i - xOffset] = 1;
                    }
                } else {
                    least = MIN(y, lasty);
                    most = MAX(y, lasty);
                    for (i = least; i <= most; ++i) {
                        map->isRock[i][x - xOffset] = 1;
                    }
                }
            }
            else {
                while (isdigit(*line))  {           
                    x = x * 10 + *(line++) - '0';
                }
                ++line;
                while (isdigit(*line))  {           
                    y = y * 10 + *(line++) - '0';
                }
                map->isRock[y][x - xOffset] = 1;
                first = false;
            }
            lastx = x; lasty = y;
            while(!isdigit(*line) && *line != '\0') ++line;
        }
    }

    fclose(fp);
}

int* getBearings(char *filename) {
    // int[0] = x_least, int[1] = x_most
    // int[2] = y_least, int[3] = y_most
    int *result = calloc(4, sizeof(int));
    result[0] = 500;
    result[1] = 500;

    FILE *fp = fopen(filename, "r");
    int i = 0;
    int buff = 350;
    char *line = malloc(buff);
    ssize_t len;

    int bigy, bigx;
    while (fgets(line, buff, fp)) {
        while (line[0] != '\n') {
            if (isdigit(*line)){ 
                if (i%2) {
                    bigy = 0;
                    while (isdigit(*line))  {           
                        bigy = bigy * 10 + *(line++) - '0';
                    }
                    if (bigy > result[3]) result[3] = bigy;
                } else {
                    bigx = 0;
                    while (isdigit(*line))  {           
                        bigx = bigx * 10 + *(line++) - '0';
                    }
                    if (bigx > result[1]) result[1] = bigx;
                    else if (bigx < result[0]) result[0] = bigx;
                }
                ++i;
            }
            else line++;
        }
    }
    fclose(fp);
    return result;
}


/* 
so this is an epileptic seizure inducing nightmare
One idea is to incorporate a very basic vsync. But we need a way to swap pages
*/
void showCave(grid *map, int wd, int ht, int initial) {
int total = 0;
char *buff = malloc((wd+1)*ht);
for (int i = 0; i < ht; ++i) {
        for (int j = 0; j <= wd; ++j) {
            if (map->isRock[i][j] == 1) *(buff++) = '#';
            else if (map->isSand[i][j]) {
                *(buff++) = 'o';
                ++total;
            }
            else if (i == 0 && j == initial) *(buff++) = '+';
            else *(buff++) = ' ';
        }
        *(buff++) = '\n';
    } 
    buff -= ((wd+1)*ht);
    printf("%s\n", buff);
    printf("%d\n", total);
}

// strictly for part 2

void createFloor(grid* map, int ht, int wd) {
    for (int i = 0; i <= wd; ++i) {
        map->isRock[ht-1][i] = 1;
    }
}

bool moveSand(grid* map, int wd, int ht, int initialx, int initialy, int endx, int endy) {
    int x = initialx;
    int y = initialy;
    if (map->isSand[endy][endx]) return false;
    if (map->isRock[y+1][x] || map->isSand[y+1][x]) {
        if (!map->isSand[y+1][x-1] && !map->isRock[y+1][x-1]) return moveSand(map,wd,ht, x-1, y+1, endx, endy);
        else if (!map->isSand[y+1][x+1] && !map->isRock[y+1][x+1]) return moveSand(map,wd,ht, x+1, y+1, endx, endy);
        else {
            map->isSand[y][x] = true;
            return true;
        }
    } 
   
    return moveSand(map, wd, ht, x, y+1, endx, endy);
}

// ./a.out input.txt 1000
int main(int argc, char **argv)
{
    char *filename = argv[1];
    int* bearings = getBearings(filename);
    int extraWidth = atoi(argv[2] ? argv[2] : "2");
    int wd = bearings[1] - bearings[0] + extraWidth; // add two columns to the end
    int ht = bearings[3] + 3; //adding a floor, so one more!
    grid *map = createGrid(wd, ht);
    createRocks(map, filename, bearings[0] - extraWidth/2); 
                                                 
    createFloor(map, ht, wd);
    bool sand = true;


    // loop time
    clock_t currTime, elapsedTime;
    do {
        currTime = clock();
        elapsedTime = currTime;
        while (elapsedTime - currTime < 1) elapsedTime = clock();
        system("clear");
        showCave(map, wd, ht, bearings[0] - extraWidth/2 - 1);
    } while (moveSand(map, wd, ht, 500 - bearings[0] + extraWidth/2, 0, 500 - bearings[0] + extraWidth/2, 0));
  

    return 0;
}