#include <stdio.h>
#include "Heap.h"


int main()
{
    // int heapArray[INT_MAX] = {9, 8, 6, 6, 7, 5, 2, 1, 4, 3, 6, 2};
    int heapArray[INT_MAX] = {1, 3, 2, 6, 4, 2, 6, 8, 7, 9, 6, 5};

    MaxHeap *heap = newMaxHeap(heapArray, 12);

    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    putchar('\n');

    push(heap, 7);

    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    putchar('\n');

    pop(heap);

    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    putchar('\n');


    return 0;
}