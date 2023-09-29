#ifndef __SINGLE_SORT_LINK_LIST_H__
#define __SINGLE_SORT_LINK_LIST_H__
#include <stdbool.h>

typedef int ElemType;

struct SortHead{
    struct SortNode *first;
    struct SortNode *last;
    int nodeNums;
};

struct SortNode{
    ElemType value;
    struct SortNode *next;
};


extern struct SortHead *createHead ();
extern void printList (struct SortHead *head);
extern bool destroyList (struct SortHead *head);
extern struct SortHead *addNodeToList (struct SortHead *head, ElemType value);
extern struct SortHead *delNode (struct SortHead *head, ElemType value);
extern struct SortHead * changeValue (struct SortHead *head, ElemType originalData, ElemType targetData);
extern int searchValue (struct SortHead *head, ElemType targetData);


#endif