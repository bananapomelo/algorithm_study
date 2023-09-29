#include <stdbool.h>

#ifndef __ARRAYQUEUE_H__
#define __ARRAYQUEUE_H__

typedef int ElemType;

typedef struct ArrayQueue{
    ElemType *array;
    int front;
    int queSize; // 队列中元素个数, 用于计算队尾下标
    int capacity;
}AQueue;

extern AQueue *createArrayQueue(int capacity);
extern void delArrayQueue(AQueue *queue);
extern int capacity(AQueue *queue);
extern int size(AQueue *queue);
extern bool isEmpty(AQueue *queue);
extern ElemType peek(AQueue *queue);
extern void push(AQueue *queue, ElemType value);
extern void pop(AQueue *queue);
extern void print(AQueue *queue);



#endif