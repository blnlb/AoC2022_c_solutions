#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

#include <stdlib.h>
#include <stdio.h>

struct nod {
    struct nod *next;
    int val;
};

typedef struct nod nod;

nod* createNode(int val) {
    nod* result = calloc(1, sizeof(nod));
    result->next = NULL;
    result->val = val;
    return result;
}

void heapify(int *list, int *len, int i) {
    if (*len == 1) {
        return;
    } else {
        int ptr;
        int largest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        if (left < *len && list[left] > list[largest])
            largest = left;
        if (right < *len && list[right] > list[largest])
            largest = right;

        if (largest != i) {
            int ptr = list[i];
            list[i] = list[largest];
            list[largest] = ptr;
            heapify(list, len, largest);
        }
    }
}

void deleteNode(int *list, int *len, int val) {
    int i;
    for (i = 0; i < *len; ++i) {
        if (list[i] == val) break;
    }
    int ptr = list[i];
    list[i] = list[*len - 1];
    list[*len - 1] = ptr;
    (*len)--;
    for (i = *len / 2 - 1; i >=0; --i) {
        heapify(list, len, i);
    }
}

void penqueue(int *list, int val, int *len) {
        list[*len++] = val;
    if ((*len) - 1) {
        for (int i = *len/2 - 1; i >=0; --i) {
            heapify(list, len, i);
        }
    }
}


#endif