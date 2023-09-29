#include <stdbool.h>
#ifndef __CIRCLE_BOTH_SORT_LIST_H__
#define __CIRCLE_BOTH_SORT_LIST_H__

typedef int ElemType;

typedef struct CircleBothSortHead{
    struct CircleBothSortNode *first;
    struct CircleBothSortNode *last;
    int nodeNums;
}CBSHead;

typedef struct CircleBothSortNode{
    struct CircleBothSortNode *prev;
    struct CircleBothSortNode *next;
    ElemType value;
}CBSNode;

extern CBSHead *addNode(CBSHead *head, ElemType value, CBSNode *insert);
extern CBSHead *createList();
extern void printList(CBSHead *head);
extern bool destroyList(CBSHead *head);
extern CBSHead *delNode(CBSHead *head, ElemType targetData);
extern CBSHead *changeNode(CBSHead *head, ElemType sourceData, ElemType targetData);
extern int searchNode(CBSHead *head, ElemType targetData);

#endif