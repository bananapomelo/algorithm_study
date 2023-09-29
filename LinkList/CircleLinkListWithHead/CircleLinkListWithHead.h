#include <stdbool.h>
#ifndef __CIRCLE_LINK_LIST_WITH_HEAD_H__
#define __CIRCLE_LINK_LIST_WITH_HEAD_H__

typedef int ElemType;

typedef struct CirCleLinkListHead{
    struct CirCleLinkListNode *first;
    struct CirCleLinkListNode *last;
    int nodeNums;
}CSHead;

typedef struct CirCleLinkListNode{
    struct CirCleLinkListNode *next;
    ElemType value;
}CSNode;

extern CSHead *createList();
extern CSHead *addNode(CSHead *head, ElemType value);
extern CSHead *delNode(CSHead *head, ElemType value);
extern CSHead *changeNode(CSHead *head, ElemType sourceData, ElemType targetData);
extern int searchNode(CSHead *head, ElemType value);
extern void printList(CSHead *head);
extern void proveCircle(CSHead *head);
extern bool destroyList(CSHead *head);


#endif