#include <stdbool.h>
#include "ListTree.h"

#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__


typedef TNode * TreeData;

typedef struct LinkQueue{
    struct QueueNode *front;
    struct QueueNode *rear;
    int nodeNum;
}LQueue;

typedef struct QueueNode{
    struct QueueNode *next;
    TreeData value;
}QNode;

extern LQueue *createLinkQueue();
extern void destructLinkQueue(LQueue *queue);
extern int size(LQueue *queue);
extern bool isEmpty(LQueue *queue);
extern TreeData peek(LQueue *queue);
extern void push(LQueue *queue, TreeData value);
extern TreeData pop(LQueue *queue);
extern void print(LQueue *queue);


#endif