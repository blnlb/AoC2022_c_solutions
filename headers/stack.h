#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAXELEM 56

struct stack {
    int top;
    char item[MAXELEM];
};
typedef struct stack st;

st *initStack() {
    st *s = malloc(sizeof(st));
    s->top = -1;
    return s;
}

bool isEmpty(st *s) {
    return s->top < 0;
}
bool isFull(st *s) {
    return (s->top >= MAXELEM - 1);
}

void push(st *s, char a) {
    if (isFull(s)) printf("Stack full error\n");
    s->item[++(s->top)] = a;
}

char pop(st *s) {
    if (isEmpty(s)) printf("Stack empty error\n");
    return s->item[(s->top)--];
}

void printStack(st *s) {
  for (int i = 0; i < s->top + 1; i++) {
    printf("%c ", s->item[i]);
  }
  printf("\n");
}

void insertAtBottom(st *s, char a) {
    if (isEmpty(s)) {
        push(s, a);
    } else {
        char t = pop(s);
        insertAtBottom(s, a);
        push(s, t);
    }
}

void reverse(st *s) {
    if (!isEmpty(s)) {
        char top = pop(s);
        reverse(s);

        insertAtBottom(s, top);
    }
}