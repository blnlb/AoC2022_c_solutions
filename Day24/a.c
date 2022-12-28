#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "grid.h"
#include "state.h"
#include "queue.h"

#define PART1 0
#define EXAMPLE 0
#define SHOWGRID 0
#define MIN(A,B) ((B) ^ ((A ^ B) & -(A < B)))

int main(int argc, char** argv) {
    int width = !EXAMPLE ? 122 : 8;
    int height = !EXAMPLE ? 27 : 6;
    const char *filename = argv[1] ? argv[1] : "example.txt";
    int numBlizzards;

    // obtain all the initial blizzard information
    blizzard **initialBlizzies = initBlizzards(filename, &numBlizzards);

    //collect this information and spawn the begin and end positions
    grid *map = createGrid(width, height, initialBlizzies, numBlizzards);
    int ***blizzardsPrecalced = precalc(map);
    
    // places we've been, up to a million
    state **seen = calloc(1000000, sizeof(state*));
    int seenLength = 0;


    // iterations is 1 or 3, depending on which puzzle is being solved
    int iterations = 0;
    int totalSteps = 0;
    // The day and step counters have been separated.
    // lastDay will help us determine which cycle we should start on each iteration
    int lastDay = 0;
    while (iterations++ < (PART1 ? 1 : 3)) {
        // create a state with the day and beginning position
        state *initialState = createState(lastDay, 0, map->begin[0], map->begin[1]);
        queue *q = queueInit();
        enqueue(q, initialState);
        seenLength = 0;

        // height cubed is my guess on an upper limit for the minimum
        int minSteps = map->height*map->height*map->height;
        // common bfs
        while (!isEmpty(q)) {
            state *c = dequeue(q);
            printf("Queue Length: %d\tNum Steps: %d\t Best so far: %d\n", q->back, c->numSteps, minSteps);
            if (c->numSteps >= minSteps) continue;
            if (c->x == map->end[0] && c->y == map->end[1]) {
                minSteps = MIN(c->numSteps, minSteps);
                lastDay = c->day;
                continue;
            }
            state *doNothing = updateAdventurer2(map, c, -1, blizzardsPrecalced, seen, &seenLength);
            state *moveRight = updateAdventurer2(map, c, right, blizzardsPrecalced, seen, &seenLength);
            state *moveDown = updateAdventurer2(map, c, down, blizzardsPrecalced, seen, &seenLength);
            state *moveLeft = updateAdventurer2(map, c, left, blizzardsPrecalced, seen, &seenLength);
            state *moveUp = updateAdventurer2(map, c, up, blizzardsPrecalced, seen, &seenLength);
            if (doNothing) enqueue(q, doNothing);
            if (moveRight) enqueue(q, moveRight);
            if (moveDown) enqueue(q, moveDown);
            if (moveLeft) enqueue(q, moveLeft);
            if (moveUp) enqueue(q, moveUp);
        }
        totalSteps += minSteps;
        swapPositions(map->begin, map->end);
    }
    
    printf("Total: %d\n", totalSteps);
    return 0;
}