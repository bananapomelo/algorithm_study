#include <stdbool.h>

#ifndef __SEQUENCE_STACK_H__
#define __SEQUENCE_STACK_H__

// typedef int Elemtype;
typedef int Elemtype;

typedef struct SequenceArrayStack{
    Elemtype *array;
    int size;
}SStack;

extern SStack *createStack();
extern bool destructStack(SStack *stack);
extern int size(SStack *stack);
extern bool isEmpty(SStack *stack);
extern Elemtype peek(SStack *stack);
extern SStack *push(SStack *stack, Elemtype inputValue);
extern Elemtype pop(SStack *stack);




#endif