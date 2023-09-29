#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "SequenceStack.h"
#define INT_MAX 65536

/*
    createStack: 创建顺序栈
        @retval: 栈的指针
*/
SStack *createStack(){
    SStack *stack = malloc(sizeof(*stack));
    stack->size = 0;
    stack->array = malloc(sizeof(int) * INT_MAX);

    return stack;
}

/*
    destructStack: 析构栈
        @stack: 栈指针
        @retval: true代表析构成功
*/
bool destructStack(SStack *stack){
    free(stack->array);
    stack->array = NULL;
    free(stack);
    stack = NULL;
    if (stack == NULL)
        return true;
    else
        return false;
}   

/*
    size: 栈内元素个数
        @stack: 栈指针
        @retval: 栈内元素个数
*/
int size(SStack *stack){
    assert(stack);
    return stack->size;
}

/*
    isEmpty: 判断是否为空栈
        @stack: 栈指针
        @retval: 空栈返回true
*/
bool isEmpty(SStack *stack){
    return !(stack->size);
}

/*
    peek: 
        @stack: 
        @retval: 
*/ 
Elemtype peek(SStack *stack){
    assert(stack);
    int topIndex = stack->size - 1;
    return stack->array[topIndex];
}

/*  
    push: 入栈操作
        @stack: 栈指针
        @inputvalue: 入栈元素
        @retval: 栈指针
*/
SStack *push(SStack *stack, Elemtype inputValue){
    assert(stack);
    assert(stack->size < INT_MAX);
    int topIndex = stack->size;
    stack->array[topIndex] = inputValue;
    stack->size++;

    return stack;
}

/*
    pop: 出栈操作
        @stack: 栈指针
        @retval: 出栈元素
*/
Elemtype pop(SStack *stack){
    assert(stack);
    assert(stack->size > 0);
    Elemtype retValue = peek(stack);
    stack->size--;

    return retValue;

}








