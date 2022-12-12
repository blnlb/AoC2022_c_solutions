#ifndef MONKEY_HEAD
#define MONKEY_HEAD

typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct monkey monkey;
typedef int (*Opi)(uint n);
typedef uint (*Opb)(uint n);

//global
uint LCM = 9699690;

uint set0[4] = {85, 79, 63, 72};
uint set1[8] = {53, 94, 65, 81, 93, 73, 57, 92};
uint set2[2] = {62, 63};
uint set3[3] = {57, 92, 56};
uint set4[4] = {67};
uint set5[6] = {85, 56, 66, 72, 57, 99};
uint set6[5] = {86, 65, 98, 97, 69};
uint set7[7] = {87, 68, 92, 66, 91, 50, 68};

monkey *createMonkey(uint[], int, Opb, Opi);
void destroyMonkey(monkey*);
uint m0(uint n);
uint m1(uint n);
uint m2(uint n);
uint m3(uint n);
uint m4(uint n);
uint m5(uint n);
uint m6(uint n);
uint m7(uint n);
int t0(uint n);
int t1(uint n);
int t2(uint n);
int t3(uint n);
int t4(uint n);
int t5(uint n);
int t6(uint n);
int t7(uint n);

#endif