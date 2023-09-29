#ifndef __LINKDEQUE_H__
#define __LINKDEQUE_H__

typedef int ElemType;

typedef struct DoubleEndedLinkQueue{
    struct DeQueLinkNode *first;
    struct DeQueLinkNode *last;
    int nodeNum;
}DLQue;

typedef struct DeQueLinkNode{
    struct DeQueLinkNode *prev;
    struct DeQueLinkNode *next;
    ElemType value;
}DLNode;

extern DLQue *createDeQue();
extern void destructDeQue(DLQue *queue);
extern int sizeDQ(DLQue *queue);
extern int isEmptyDQ(DLQue *queue);
extern ElemType peekFirstDQ(DLQue *queue);
extern ElemType peekLastDQ(DLQue *queue);
extern void pushFirstDQ(DLQue *queue, ElemType value);
extern void pushLastDQ(DLQue *queue, ElemType value);
extern void popFirstDQ(DLQue *queue);
extern void popLastDQ(DLQue *queue);
extern void printDQ(DLQue *queue);





#endif

