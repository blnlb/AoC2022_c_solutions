#ifndef QUEUE
#define QUEUE

#include <stdlib.h>
#include <stdbool.h>
#include "state.h"

#define MAXSIZE 1000000

typedef struct statequeue {
    state** states;
    int length;
    int front;
    int back;
} queue;

queue *queueInit() {
    queue* result = (queue*)calloc(1, sizeof(queue));
    result->front = -1;
    result->back = -1;
    result->states = (state**)calloc(MAXSIZE, sizeof(state*));
    for (int i = 0; i < MAXSIZE; ++i) {
        result->states[i] = (state*)calloc(1, sizeof(state));
    }
    return result;
}

void enqueue(queue *q, state *item);
state *dequeue(queue *q);
bool isEmpty(queue *q);
bool isFull(queue *q);

bool isFull(queue *q) {
    return (q->back >= MAXSIZE - 1);
}
bool isEmpty(queue *q) {
    return (q->back < q->front || q->front == -1);
}

void enqueue(queue *q, state *item) {
    if (isFull(q)) {
        printf("This queue is full, bitch!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->states[++(q->back)] = item;
}


void appendLeft(queue *q, state *s) {
    if (isFull(q)) {
        printf("Can't append left. The queue is effing full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front=0;
        q->states[++(q->back)] = s;
        return;
    }
    ++q->back;
    for (int i = q->back; i > 0; --i) {
        q->states[i] = q->states[i-1];
    }
    q->states[q->front] = s;
}

// shifting the q, to save memory
state *dequeue(queue *q) {
    if (isEmpty(q)) {
        printf("Nothing to dq.\n");
        return NULL;
    }
    state *selected = q->states[q->front];
    for (int i = 0; i < q->back; ++i) {
        q->states[i] = q->states[i+1];
    }
    --(q->back);
    if (q->back < q->front) {
        q->front = -1;
        q->back = -1;
    }
    return selected;
}



#endif