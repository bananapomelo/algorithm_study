#ifndef __HEAP_H__
#define __HEAP_H__
#define INT_MAX 13

typedef int ElemType;

typedef struct MaxHeap {
    ElemType *data;    
    int size;
}MaxHeap;

extern MaxHeap *newMaxHeap(ElemType *heapArray, int length);
extern int left(int index);
extern int right(int index);
extern int parent(int index);
extern int size(MaxHeap *heap);
extern ElemType peek(MaxHeap *heap);
extern int isEmpty(MaxHeap *heap);
extern void swap(ElemType *data, int x, int y);
extern void siftUp(MaxHeap *heap, int downIndex);
extern void siftDown(MaxHeap *heap, int upIndex);
extern void push(MaxHeap *heap, ElemType value);
extern ElemType pop(MaxHeap *heap);


#endif