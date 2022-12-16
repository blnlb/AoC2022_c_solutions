#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/utility.h"

int dist(int *a, int *b) {
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

unsigned long process(int *coor, int total, int upperBound) {
    int d, d_temp;
    int i, j, pt[2];
    for (i = 0; i < total; i +=4) {
        // get the distance between THIS sensor and ITS beacon
        d = dist(coor + i, coor + i + 2) + 1;
        // okay so we calculate 4 line segments, but remember y is backwards.
        // first up... y = -x + b 
        for (*pt = *(coor + i) - d; *pt < *(coor + i); ++(*pt)) {
            if (*pt < 0 || *pt > upperBound) continue; 
            *(pt + 1) = *(coor + i + 1) - d - (*pt - *(coor + i)); 
            if (*(pt + 1) < 0 || *(pt + 1) > upperBound) continue;
            
            // go through all the others too. yeesh.
            for (j = 0; j < total; j += 4) {
                if (j == i) continue;
                d_temp = dist(coor + j, coor + j + 2);
                if (dist(pt, coor + j) <= d_temp || dist(pt, coor + j + 2) == 0) break;
                if (j + 4 >= total) 
                    return (unsigned long)pt[0]*4000000 + pt[1];
            }
        }
        // y = x + b
        for (*pt = *(coor + i); *pt < *(coor + i) + d; ++(*pt)) {
            if (*pt < 0 || *pt > upperBound) continue; 
            *(pt + 1) = *(coor + i + 1) - d + (*pt - *(coor + i)); 
            if (*(pt + 1) < 0 || *(pt + 1) > upperBound) continue;
            for (j = 0; j < total; j += 4) {
                if (j == i) continue;
                d_temp = dist(coor + j, coor + j + 2);
                if (dist(pt, coor + j) <= d_temp || dist(pt, coor + j + 2) == 0) break;
                else if (j + 4 >= total) 
                    return (unsigned long)pt[0]*4000000 + pt[1];
            }
        }
        // y = -x + b + 2d
        for (*pt = *(coor + i) + d; *pt > *(coor + i); --(*pt)) {
            if (*pt < 0 || *pt > upperBound) continue; 
            *(pt + 1) = *(coor + i + 1) + d - (*pt - *(coor + i)); 
            if (*(pt + 1) < 0 || *(pt + 1) > upperBound) continue;
            for (j = 0; j < total; j += 4) {
                if (j == i) continue;
                d_temp = dist(coor + j, coor + j + 2);
                if (dist(pt, coor + j) <= d_temp || dist(pt, coor + j + 2) == 0) break;
                else if (j + 4 >= total) 
                    return (unsigned long)pt[0]*4000000 + pt[1];
            }
        }
        // y = x + b + 2d
        for (*pt = *(coor + i); *pt > *(coor + i) - d; --(*pt)) {
            if (*pt < 0 || *pt > upperBound) continue; 
            *(pt + 1) = *(coor + i + 1) + d + (*pt - *(coor + i)); 
            if (*(pt + 1) < 0 || *(pt + 1) > upperBound) continue;
            for (j = 0; j < total; j += 4) {
                if (j == i) continue;
                d_temp = dist(coor + j, coor + j + 2);
                if (dist(pt, coor + j) <= d_temp || dist(pt, coor + j + 2) == 0) break;
                else if (j + 4 >= total) 
                    return (unsigned long)pt[0]*4000000 + pt[1];
            }
        }
    }
    return 0;
}


int main(int argc, char **argv) {
    char *filename = argv[1] ? argv[1] : "example.txt";
    int total;
    int *coordinates = NULL;
    coordinates = getNums(filename, &total);
    if (!coordinates) {
        printf("Please provide a proper file name in this folder.");
        return -1;
    }
    int width = 4000000;
    unsigned long p2 = process(coordinates, total, width);
    printf("%lu\n", p2); // 12625383204261, which is correct yay
    return 0;

}