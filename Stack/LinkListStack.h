#include <stdbool.h>
#ifndef __LINK_LIST_SATCK_H__
#define __LINK_LIST_STACK_H__


typedef int ElemType;

typedef struct LinkedListStack{
    struct ListNode *top;
    int size;
}LStack;

typedef struct ListNode{
    struct ListNode *next;
    ElemType value;
}LNode;

extern LStack *createStack();
extern bool destructStack(LStack *stack);
extern bool isEmpty(LStack *stack);
extern int size(LStack *stack);
extern ElemType peek(LStack *stack);
extern LStack *push(LStack *stack, ElemType value);
extern ElemType pop(LStack *stack);


#endif














