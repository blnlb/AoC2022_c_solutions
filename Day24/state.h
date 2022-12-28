#ifndef STATE24
#define STATE24

#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

typedef struct state {
    int numSteps;
    int day;
    int x;
    int y;
} state;

state *createState(int day, int numSteps, int x, int y) {
    state* result = (state*)calloc(1, sizeof(state));
    result->numSteps = numSteps;
    result->x = x;
    result->y = y;
    result->day = day;
    return result;
}

// a lil helper function that is totally unnecessary but helps me write 5 fewer characters
state *createChildstate(state *s, int x, int y) {
    state *result = (state*)calloc(1,sizeof(state));
    result = createState(s->day + 1, s->numSteps + 1, x, y);
    return result;
}

state *updateAdventurer2(grid *map, state *last, int direction, int ***bl, state **seen, int *seenLength) {
    // exit condition(s)
    if (direction == down &&
        last->y + 1 == map->end[1] &&
        last->x == map->end[0]) {
            int y = last->y + 1;
            return createChildstate(last, last->x, y);
    } 
    else if (direction == up &&
        last->y - 1 == map->end[1] &&
        last->x == map->end[0]) {
            int y = last->y - 1;
            return createChildstate(last, last->x, y);
    }

    //run into a wall
    if (direction == right && (last->x + 1 >= map->width - 1 || last->y == 0) ||
        direction == down && last->y + 1 >= map->height - 1 ||
        direction == left && (last->x - 1 <= 0 || last->y == map->height - 1) ||
        direction == up && last->y - 1 <= 0) {
        return NULL;
    }

    // look in this direction
    int potential_x = last->x, potential_y = last->y;
    switch (direction) {
        case -1:
            break;
        case right:
            ++potential_x;
            break;
        case left:
            --potential_x;
            break;
        case down:
            ++potential_y;
            break;
        case up:
            --potential_y;
            break;
    }

    // check the hash map on THIS DAY to see if anything's blocking our path
    state *potential = createChildstate(last, potential_x, potential_y);
    int cycle = (map->width - 2)*(map->height - 2);
    if (bl[potential->day % cycle][potential->y][potential->x]) {
        return NULL;
    }
    // finally, short-circuit the SEEN check before you even add to the queue
    for (int i=0; i < *seenLength; ++i) {
        if (seen[i]->day == (potential->day % cycle) &&
            seen[i]->x == potential->x && seen[i]->y == potential->y) {
            return NULL;
        }
    }
    // if nothing's there, add it to the queue
    seen[(*seenLength)++] = potential;
    return potential;
}

#endif