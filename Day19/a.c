#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "../headers/state.h"
#include "../headers/queue.h"

#define MAX(A,B) ((A) ^ ((A ^ B) & -(A < B)))
#define MIN(A,B) ((B) ^ ((A ^ B) & -(A < B)))

typedef struct blueprint {
    int oreCost; // ore
    int clayCost; // ore
    int obsidianCost[2]; // ore and clay
    int geodeCost[2]; // ore and obsidian
} bprint;

int solve(bprint * bloop) {
    int maxOreCost = MAX(bloop->clayCost, MAX(bloop->oreCost, MAX(bloop->obsidianCost[0], bloop->geodeCost[0])));
    int best = 0;
    int robots[4] = {1, 0, 0, 0};
    int resources[4] = {0, 0, 0, 0};
    int t = 24;
    state *start = createState(t, 1, 0, 0, 0, 0, 0, 0, 0);
    queue *q = queueInit();
    state ** seen = (state**)calloc(10000000, sizeof(state*));
    for (int i = 0; i < 10000000; ++i) {
        seen[i] = (state*)calloc(1, sizeof(state));
    }
    int seenLength = 0;
    bool getOut;
    enqueue(q, start);
    while (!isEmpty(q)) {
        getOut = false;
        // printf("%d\n", q->back);
        state *c = dequeue(q); 
        // printf("Ore Totals: %d, %d, %d, %d\nRobot Totals: %d, %d, %d, %d\n", c->ore, c->clay, c->obsidian, c->geode, c->r1, c->r2, c->r3, c->r4);
        if (t == 1) {
            best = MAX(best, c->geode + c->r4);
            continue;
        }
        for (int i = 0; i < seenLength; ++i) {
            if (seen[i]->clay == c->clay &&
                seen[i]->ore == c->ore &&
                seen[i]->obsidian == c->obsidian &&
                seen[i]->r1 == c->r1 && seen[i]->r2 == c->r2 &&
                seen[i]->r3 == c->r3 && seen[i]->r4 == c->r4)  {
                    getOut = true;
                    break;
                }
        }
        if (getOut) continue;
        // if (c->r1 >= bloop->geodeCost[0] && c->r3 >= bloop->geodeCost[1])  {
        //     int more = c->geode + c->r4*(t-1);
        //     best = MAX(best, more);
        //     continue;
        // }
        if (2 * best > 2 * c->geode + c->r4*t + pow(t,2) - t) continue;

        seen[seenLength++] = c;
        //best = MAX(best, c->geode);
        state *doNothing = createState(t-1, c->r1, c->r2, c->r3, c->r4, c->ore + c->r1, c->clay + c->r2, c->obsidian + c->r3, c->geode + c->r4);
        enqueue(q, doNothing);
        if (bloop->oreCost <= c->ore && c->r1 < maxOreCost) {
            state *buyOre = createState(t-1, c->r1 + 1, c->r2, c->r3, c->r4, c->ore + c->r1 - bloop->oreCost, c->clay + c->r2, c->obsidian + c->r3, c->geode + c->r4);
            enqueue(q, buyOre); 
        }
        if (bloop->clayCost <= c->ore && c->r2 < bloop->obsidianCost[1]) {
            state *buyClay = createState(t-1, c->r1, c->r2 + 1, c->r3, c->r4, c->ore - bloop->clayCost + c->r1, c->clay + c->r2, c->obsidian + c->r3, c->geode + c->r4);
            enqueue(q, buyClay); 
        }
        if (bloop->obsidianCost[0] <= c->ore && bloop->obsidianCost[1] <= c->clay && c->r3 < bloop->geodeCost[1]) {
            state *buyObsidian = createState(t-1, c->r1, c->r2, c->r3 + 1, c->r4, c->ore - bloop->obsidianCost[0] + c->r1, c->clay - bloop->obsidianCost[1] + c->r2, c->obsidian + c->r3, c->geode + c->r4);
            enqueue(q, buyObsidian); 
        }
        if (bloop->geodeCost[0] <= c->ore && bloop->geodeCost[1] <= c->obsidian) {
            state *buyGeode = createState(t-1, c->r1, c->r2, c->r3, c->r4 + 1, c->ore - bloop->geodeCost[0] + c->r1, c->clay + c->r2, c->obsidian - bloop->geodeCost[1] + c->r3, c->geode + c->r4);
            appendLeft(q, buyGeode); 
        }

    }
    return best;
    
}


bprint *createBlueprint(int ore, int clay, int obs[2], int geode[2]) {
    bprint *result = calloc(1, sizeof(bprint));
    result->oreCost = ore;
    result->clayCost = clay;
    result->obsidianCost[0] = obs[0];
    result->obsidianCost[1] = obs[1];
    result->geodeCost[0] = geode[0];
    result->geodeCost[1] = geode[1];
    return result;
}

bprint **parseInput(char *f, int *numBlueprints) {
    FILE *fp = fopen(f, "r");
    bprint **result = calloc(30, sizeof(bprint*));
    int buff = 4900;
    char *line = malloc(buff);
    
    int num, curr = 0, ore = 0, clay = 0;
    int obs[2], geode[2];
    while (fgets(line, buff, fp)) {
        ore = 0; clay = 0, obs[0] = 0, obs[1] = 0, geode[0] = 0, geode[1] = 0;
        result[curr] = calloc(1, sizeof(bprint));
        while (!isdigit(*line)) ++line;
        while (isdigit(*line)) ++line;
        while (!isdigit(*line)) ++line;
        while (isdigit(*line))
            ore = ore*10 + *line++ - '0';
        while (!isdigit(*line)) ++line;
        while (isdigit(*line))
            clay = clay*10 + *line++ - '0';
        while (!isdigit(*line)) ++line;
        while (isdigit(*line))
            obs[0] = obs[0]*10 + *line++ - '0';
        while (!isdigit(*line)) ++line;
        while (isdigit(*line))
            obs[1] = obs[1]*10 + *line++ - '0';
        while (!isdigit(*line)) ++line;
        while (isdigit(*line))
            geode[0] = geode[0]*10 + *line++ - '0';
        while (!isdigit(*line)) ++line;
        while (isdigit(*line))
            geode[1] = geode[1]*10 + *line++ - '0';
        result[curr++] = createBlueprint(ore, clay, obs, geode);
    }
    *numBlueprints = curr;
    fclose(fp);
    return result;
}

int main(int argc, char **argv) {
    char *filename = argv[1] ? argv[1] : "example.txt";
    int numberBlueprints = 0;
    bprint** blueprints = parseInput(filename, &numberBlueprints);

    int numMinutes = 24;
    //int* geodeCounts = simulateRobotFactory(blueprints, numberBlueprints, numMinutes);
    solve(blueprints[0]);


    return 0;
}