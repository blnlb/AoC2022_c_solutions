#include "monkey.h"
#include <math.h>

typedef struct monkey
{
    uint *items;
    ulong numInspected;
    int numItems;
    Opb newOp;
    Opi test;
} monkey;

monkey *createMonkey(uint init_set[], int len, Opb op, Opi test)
{
    monkey *result = malloc(sizeof(monkey));
    result->items = calloc(36, sizeof(uint));
    memcpy(result->items, init_set, len * sizeof(uint));
    result->numItems = len;
    result->numInspected = 0;
    result->newOp = op;
    result->test = test;
    return result;
}

void destroyMonkey(monkey* monk) {
    free(monk->items);
    free(monk);
}

void deQueue(int curr, monkey **monkeys)
{
    uint oldValue, newValue;
    monkey *currMonkey = monkeys[curr], *newMonkey;
    for (int i = 0; i < currMonkey->numItems; ++i)
    {
        oldValue = currMonkey->items[i];
        newValue = currMonkey->newOp(oldValue);
        newMonkey = monkeys[currMonkey->test(newValue)];
        newMonkey->items[(newMonkey->numItems)++] = newValue;
        currMonkey->numInspected += 1;
    }
    currMonkey->numItems = 0;
}

uint m0(uint n)
{
    return ((n % LCM) * 17) % LCM;
}

uint m1(uint n)
{
    // this calculation was the single source of all my issues.
    // turns out we can handle the (LCM-1)*(LCM-1) problem
    // with a ulong. But we need to convert in each place first.
    ulong res = (ulong)(n % LCM) * (ulong)(n % LCM);
    return (uint)(res % LCM);
}



uint m2(uint n)
{
    return (n + 7) % LCM;
}

uint m3(uint n)
{
    return (n + 4) % LCM;
}

uint m4(uint n)
{
    return (n + 5) % LCM;
}

uint m5(uint n)
{
    return (n + 6) % LCM;
}

uint m6(uint n)
{
    return ((n % LCM) * 13) % LCM;
}

uint m7(uint n)
{
    return (n + 2) % LCM;
}

int t0(uint n)
{
    return (n % 2) ? 6 : 2;
}

int t1(uint n)
{
    return (n % 7) ? 2 : 0;
}

int t2(uint n)
{
    return (n % 13) ? 6 : 7;
}

int t3(uint n)
{
    return (n % 5) ? 5 : 4;
}

int t4(uint n)
{
    return (n % 3) ? 5 : 1;
}

int t5(uint n)
{
    return (n % 19) ? 0 : 1;
}

int t6(uint n)
{
    return (n % 11) ? 7 : 3;
}

int t7(uint n)
{
    return (n % 17) ? 3 : 4;
}