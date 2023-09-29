#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "LinkListStack.h"

/*
    createStack: 创建链式空栈
        @retval: 栈顶指针
*/
LStack *createStack(){
    LStack *stack = malloc(sizeof(*stack));
    stack->top = NULL;
    stack->size = 0;
    
    return stack;
}

/*
    destructStack: 销毁链式栈
        @stack: 栈顶指针
        @retval: 是否成功销毁
*/
bool destructStack(LStack *stack){
    assert(stack);
    LNode *traversal = stack->top;

    while(traversal){
        stack->top = stack->top->next;
        free(traversal);
        traversal = stack->top;
        stack->size--;
    }

    if (stack->top == NULL && stack->size == 0)
        return true;
    else
        return false;
}

/*
    isEmpty: 是否是空栈
        @stack: 栈顶指针
        @retval: 返回真为空栈
*/
bool isEmpty(LStack *stack){
    assert(stack);
    return stack->size == 0;
}

/*
    size: 返回栈的长度
        @stack: 栈顶指针
        @retval: 栈的长度
*/
int size(LStack *stack){
    assert(stack);
    return stack->size;
}

/*
    peek: 获取栈顶元素
        @stack: 栈顶指针
        @retval: 栈顶元素值
*/
ElemType peek(LStack *stack){
    assert(stack);
    assert(size(stack));
    return stack->top->value;
}

/*
    push: 入栈
        @stack: 栈顶指针
        @value: 入栈的值
        @retval: 栈顶指针
*/
LStack *push(LStack *stack, ElemType value){
    assert(stack);
    LNode *newNode = malloc(sizeof(*newNode));
    newNode->next = NULL;
    newNode->value = value;

    if (isEmpty(stack)){
        stack->top = newNode;
    }
    else{
        newNode->next = stack->top;
        stack->top = newNode;
    }
    stack->size++;

    return stack;
}

/*
    pop: 出栈
        @stack: 栈顶指针
        @retval: 出栈的值
*/
ElemType pop(LStack *stack){
    assert(stack);
    if (isEmpty(stack)){
        printf("Stack is empty!!!\n");
        return 0;
    }
    
    LNode *popNode = stack->top;
    stack->top = stack->top->next;
    ElemType retValue = popNode->value;
    popNode->next = NULL;
    free(popNode);
    popNode = NULL;

    stack->size--;

    return retValue;
}



































