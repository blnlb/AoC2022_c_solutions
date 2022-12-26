#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX(A,B) ((A) ^ ((A ^ B) & -(A < B)))
#define LINELENGTHMAX 30000
#define PART2 1

typedef struct person {
    int x;
    int y;
    int direction;
} person;

typedef struct map {
    char **coordinate;
    int width;
    int height;
    int rightCube;
    int upCube;
    int leftCube;
    int downCube;
} map;

person *createPerson(int x, int y, int direction) {
    person *result = calloc(1, sizeof(person));
    result->x = x;
    result->y = y;
    result->direction = direction;
    return result;
}

map *createMap(int width, int height) {
    map *result = calloc(1, sizeof(map));
    result->width = width;
    result->height = height;
    result->coordinate = (char**)calloc(height, sizeof(char*));
    for (int i = 0; i < height; ++i) {
        result->coordinate[i] = malloc(width + 1);
        for (int j = 0; j < width; ++j) {
            result->coordinate[i][j] = ' ';
        }
    }
    return result;
}

map *getBearings(const char *f) {
    FILE *fp = fopen(f, "r");
    int buff = LINELENGTHMAX;
    char *line = malloc(buff);
    
    int xmax = 0, ymax = 0, lastx, currx;
    while (fgets(line, buff, fp)) {
        if (isdigit(*line)) break;
        currx = 1, lastx = 0;
        while (*line) {
            if (*line == '#' || *line == '.') lastx = currx;
            ++currx;
            ++line;
        }
        if (!lastx) break;
        xmax = MAX(lastx, xmax);
        ++ymax;
    }
    fclose(fp);
    return createMap(xmax, ymax);
}

map **getBearings2(const char *f, int maxSize) {
    FILE *fp = fopen(f, "r");
    int buff = LINELENGTHMAX;
    char *line = malloc(buff);
    int i, j = 0;
    int complete = 0;
    map **allSides = calloc(6, sizeof(map*));
    for (i = 0; i < 6; ++i) {
        allSides[i] = createMap(maxSize, maxSize);
    }
    while (fgets(line, buff, fp)) {
        
        if (j == maxSize) {
            j = 0;
            complete = 0;
            for (int k = 0; k < 6; ++k) {
                if (allSides[k]->coordinate[0][0] != ' ') {
                    ++complete;
                } 
            }
        }
        while (*line != '\n') {
            i = complete;
            if (isdigit(*line)) return allSides;
            if (*line == ' ') {
                line += maxSize;
                continue;
            }
            strncpy(allSides[i]->coordinate[j], line, maxSize); 
            ++i;
        }
        ++j;
    }
    return allSides;
}

void populateMap(map* m, const char *f) {
    FILE *fp = fopen(f, "r");
    int buff = LINELENGTHMAX;
    char *line = malloc(buff);
    int i, j = 0;
    while (fgets(line, buff, fp)) {
        if (isdigit(*line)) return;
        i = 0; 
        while (*line != '\n' && *line != EOF && i < m->width) {
            m->coordinate[j][i++]= *line++;
        }
        ++j;
    }
    fclose(fp);
}

char *getDirections(const char *f) {
    FILE *fp = fopen(f, "r");
    int buff = LINELENGTHMAX;
    char *line = malloc(buff);
    while (fgets(line, buff, fp)) {
        if (isdigit(*line)) break;
    }
    fclose(fp);
    char* l = malloc(strlen(line));
    strncpy(l, line, strlen(line));
    l[strlen(l) - 1] = '\0';
    return l;
}

void move(person* p, int dist, map* grid) {
    int steps = 0;
    int h = grid->height;
    int eachStep = (p->direction % 2) ? (p->direction == 1 ? grid->width : grid->width*(grid->height-1)) : (p->direction % 4) ? grid->width - 1 : 1;
    int pos;
    int pos_potential;
    if (p->direction % 2) {// is odd (so up and down)
        eachStep = (p->direction == 1 ? 1 : (grid->height-1));
        while (dist) {
            if (grid->coordinate[(p->y + (1 + steps)*eachStep) % grid->height][p->x] == '#') { break; }
            if (grid->coordinate[(p->y + (1+steps)*eachStep) % grid->height][p->x] == ' ') {
                ++steps;
            }
            if (grid->coordinate[(p->y + (1+steps)*eachStep) % grid->height][p->x] == '.') {
                p->y = (p->y + (1 + steps)*eachStep) % grid->height;
                steps = 0;
                --dist;
            }
        }
    }
    else { // is even (right or left)
        eachStep = (p->direction % 4) ? grid->width - 1 : 1;
        while (dist) {
            if (grid->coordinate[p->y][(p->x + (1+steps)*eachStep) % grid->width] == '#') { break; }
            if (grid->coordinate[p->y][(p->x + (1+steps)*eachStep) % grid->width] == ' ') {
                ++steps;
            }
            if (grid->coordinate[p->y][(p->x + (1+steps)*eachStep) % grid->width] == '.') {
                p->x = (p->x + (1 + steps)*eachStep) % grid->width;
                steps = 0;
                --dist;
            }
        }
    }
        
    printf("Going %d steps %s: landed at (%d,%d)\n", dist, (p->direction % 2 ? (p->direction == 1 ? "down" : "up") : (p->direction % 4) ? "left" : "right"), p->x, p->y);
}

void turn(person* p, char r) {
    switch (r) {
        case 'L': 
            p->direction = (p->direction + 3) % 4;
            break;
        default:
            p->direction = (p->direction + 1) % 4;
    }
}

int findStartx(const char* f) {
    FILE *fp = fopen(f, "r");
    int buff = LINELENGTHMAX;
    char *line = malloc(buff);
    fgets(line, buff, fp);
    int x = 0;
    while (line[x] != '.') ++x;
    fclose(fp);
    return x;
}

int main(int argc, char **argv) {
    const char *filename = argv[1] ? argv[1] : "input.txt";

    map** allMaps = getBearings2(filename, 50);
    char *directions = getDirections(filename);
    int x = findStartx(filename);
    person* me = createPerson(x, 0, 0);

    int dist;
    char r;
    // PART 1
    // while (*directions) {
    //     dist = 0;
    //     while (isdigit(*directions)) 
    //         dist = dist * 10 + *directions++ - '0';
    //     move(me, dist, grid);
    //     if (*directions) {
    //         r = *directions++;
    //         turn(me, r);
    //     } 
    // }

    for (int i = 0; i < allMaps[5]->height; ++i) {
        for (int j = 0; j < allMaps[5]->width; ++j)
            printf("%c", allMaps[5]->coordinate[i][j]);
        printf("\n");
    }

    // int finalAmount = 0;
    // finalAmount = ((me->y)+1)*1000 + (me->x + 1)*4 + me->direction;

    // printf("Part 1: %d\n", finalAmount);
    
    return 0;
}