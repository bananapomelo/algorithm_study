#include <stdbool.h>

#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__


typedef int ElemType;

typedef struct LinkQueue{
    struct QueueNode *front;
    struct QueueNode *rear;
    int nodeNum;
}LQueue;

typedef struct QueueNode{
    struct QueueNode *next;
    ElemType value;
}QNode;

extern LQueue *createLinkQueue();
extern void destructLinkQueue(LQueue *queue);
extern int size(LQueue *queue);
extern bool isEmpty(LQueue *queue);
extern ElemType peek(LQueue *queue);
extern void push(LQueue *queue, ElemType value);
extern void pop(LQueue *queue);
extern void print(LQueue *queue);


#endif