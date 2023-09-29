#ifndef __ARRAYDEQUE_H__
#define __ARRAYDEQUE_H__

typedef int ElemType;

typedef struct ArrayDoubleEndedQueue {
    ElemType *array;
    int front;
    int queSize;
    int capacity;
}ADQue;

extern ADQue *createArrayDeQue(int capacity);
extern void destructArrayDeQue(ADQue *queue);
extern int isEmpty(ADQue *queue);
extern int capacity(ADQue *queue);
extern int size(ADQue *queue);
extern int subscript(ADQue *queue, int increment);
extern ElemType peekFirst(ADQue *queue);
extern ElemType peekLast(ADQue *queue);
extern void pushFirst(ADQue *queue, int value);
extern void pushLast(ADQue *queue, int value);
extern void popFirst(ADQue *queue);
extern void popLast(ADQue *queue);
extern void printADeQue(ADQue *queue);


#endif