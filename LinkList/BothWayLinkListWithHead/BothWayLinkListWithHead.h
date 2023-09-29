#include <stdbool.h>

#ifndef __BOTH_WAY_LINK_LIST_WITH_HEAD_H__
#define __BOTH_WAY_LINK_LIST_WITH_HEAD_H__

typedef int ElemType;

struct BothHead{
    struct BothNode *first;
    struct BothNode *last;
    int nodeNums;
};

struct BothNode{
    struct BothNode *next;
    struct BothNode *prev;
    ElemType value;
};

extern struct BothHead *createList();
extern void printList(struct BothHead *head);
extern bool destoryList(struct BothHead *head);
extern struct BothHead *addNode(struct BothHead *head, ElemType value);
extern struct BothHead *delNode(struct BothHead *head, ElemType value);
extern struct BothHead *changeNode(struct BothHead *head, ElemType sourceData, ElemType targetData);
extern int searchNode(struct BothHead *head, ElemType value);

#endif