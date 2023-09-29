#include <stdio.h>
#include <stdbool.h>
#include "LinkListStack.h"


int main(){
    LStack *stack = createStack();

    if (isEmpty(stack))
        printf("Stack is empty stack!!!\n\n");
    else
        printf("Stack is unempty stack!!!\n\n");

    while (1){
        ElemType value = 0;
        scanf("%d", &value);

        if (value == 0)
            break;

        stack = push(stack, value);
    }

    printf("\nStack top value: %d\n\n", peek(stack));

    while (stack->size){
        printf("Stack pop: %d\n", pop(stack));
    }
    printf("\n");

    if (destructStack(stack))
        printf("destruct stack complete!!!\n");
    else
        printf("destruct stack failed-_-\n");

/*
12
34
78
56
23
99
39
98
45
76
0

*/

    return 0;
}




