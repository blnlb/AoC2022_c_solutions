#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

typedef struct monkey {
    int *num;
    char *id;
    char **dependencies;
    char operation;
} monkey;

monkey *createMonkey(char *id, int *num, char op, char* dp1, char*dp2) {
    monkey *result = (monkey*)calloc(1, sizeof(monkey));
    result->id = (char*)malloc(5);
    memcpy(result->id, id, 4);
    if (num) {
        result->num = (int*)calloc(1, sizeof(int));   
        memcpy(result->num, num, sizeof(int));
    }
    else num = NULL;
    result->operation = op;
    result->dependencies = (char**)calloc(2, sizeof(char*));
    
    if (dp1) {
        result->dependencies[0] = (char*)malloc(5);
        result->dependencies[1] = (char*)malloc(5);
        memcpy(result->dependencies[0], dp1, 4);
        memcpy(result->dependencies[1], dp2, 4);
    } else {
        dp1 = NULL;
        dp2 = NULL;
    }
    return result;
}



monkey **parseP1(char *f, int *total) {
    FILE *fp = fopen(f, "r");
    int buff = 40020;
    char *line = malloc(buff);


    monkey **monkeys = calloc(3000, sizeof(monkey));
    *total = 0;
    char *id = malloc(5), *dp1 = malloc(5), *dp2 = malloc(5);
    char op = ' ';
    int num = 0;
    while(fgets(line, buff, fp)) {
        strncpy(id, line, 4);
        line += 6;
        if (isdigit(*line)) {
            num = 0;
            while (isdigit(*line)) {
                num = num * 10 + *line++ - '0';
            }
            monkeys[(*total)++] = createMonkey(id, &num, ' ', NULL, NULL);
        }
        else {
            strncpy(dp1, line, 4);
            strncpy(dp2, line + 7, 4);
            op = *(line + 5);
            monkeys[(*total)++] = createMonkey(id, NULL, op, dp1, dp2);
        }
    }

    return monkeys;
    fclose(fp);
}

long part1(monkey **monkeys, int numMonkeys, char *id) {
    for (int i = 0; i < numMonkeys; ++i) {
        if (!strncmp(monkeys[i]->id, id, 4)) {
            if (monkeys[i]->num) 
                return (long)*(monkeys[i]->num);
            else {
                long m1 = part1(monkeys, numMonkeys, monkeys[i]->dependencies[0]);
                long m2 = part1(monkeys, numMonkeys, monkeys[i]->dependencies[1]);
                switch ((monkeys[i]->operation)) {
                    case '+':
                        return m1 + m2;
                    case '-':
                        return m1 - m2;
                    case '*':
                        return m1*m2;
                    case '/':
                        return m1/m2;
                }
            }
        }
    }
    printf("You shouldn't see this.");
    return LONG_MIN;
}

long part2(monkey **monkeys, int numMonkeys, char *id, char *lastid) {
    for (int i = 0; i < numMonkeys; ++i) {
        if (!strncmp(monkeys[i]->id, id, 4)) {
            if (monkeys[i]->num && strncmp(id, "humn", 4)) {
                return (long)*monkeys[i]->num;
            }
        }
    }
    for (int i = 0; i < numMonkeys; ++i) {
        if (!strncmp(monkeys[i]->id, id, 4)) {
            if (monkeys[i]->dependencies[0] && 
            strncmp(monkeys[i]->id, "root", 4) &&
            strncmp(monkeys[i]->dependencies[0], lastid, 4) &&
            strncmp(monkeys[i]->dependencies[1], lastid, 4)) {
                return part1(monkeys, numMonkeys, id);
            }
        }
    }
    for (int i = 0; i < numMonkeys; ++i) {
        if (monkeys[i]->dependencies[0] && !strncmp(monkeys[i]->dependencies[0], id, 4)) {
            if (!strncmp(monkeys[i]->id, "root", 4)) {
                return part1(monkeys, numMonkeys, monkeys[i]->dependencies[1]);
            }
            long m1 = part2(monkeys, numMonkeys, monkeys[i]->id, id);
            long m2 = part2(monkeys, numMonkeys, monkeys[i]->dependencies[1], id);
            switch ((monkeys[i]->operation)) {
                case '+':
                    return m1 - m2;
                case '-':
                    return m1 + m2;
                case '*':
                    return m1/m2;
                case '/':
                    return m1*m2;
            }
        }
        else if (monkeys[i]->dependencies[1] && !strncmp(monkeys[i]->dependencies[1], id, 4)) {
            if (!strncmp(monkeys[i]->id, "root", 4)) {
                return part1(monkeys, numMonkeys, monkeys[i]->dependencies[0]);
            }
            long m1 = part2(monkeys, numMonkeys, monkeys[i]->id, id);
            long m2 = part2(monkeys, numMonkeys, monkeys[i]->dependencies[0], id);
            switch ((monkeys[i]->operation)) {
                case '+':
                    return m1 - m2;
                case '-':
                    return m2 - m1;
                case '*':
                    return m1/m2;
                case '/':
                    return m2/m1;
            }
        }
    }
    printf("You shouldn't see this.");
    return LONG_MIN;
}