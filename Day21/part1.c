#include <stdlib.h>
#include "monkey.h"

int main(int argc, char **argv) {
    char *filename = argv[1] ? argv[1] : "input.txt";
    int total = 0;
    monkey **monkeys = parseP1(filename, &total);
    long p1 = part1(monkeys, total, "root");
    printf("Part 1: %ld\n", p1);

    long p2 = part2(monkeys, total, "humn", "humn");
    printf("Part 2: %ld\n", p2);


    return 0;
}