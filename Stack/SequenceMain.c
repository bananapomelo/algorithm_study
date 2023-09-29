#include <stdio.h>
#include <stdbool.h>
#include "SequenceStack.h"

int main()
{
    SStack *stack = createStack();
    if (isEmpty(stack))
        printf("Stack is empty\n");
    else
        printf("Stack is not empty\n");

    while (1){
        int inputValue = 0;
        scanf("%d", &inputValue);
        if (inputValue == 0)
            break;
        
        push(stack, inputValue);
    }

    printf("\nStack size = %d\n", size(stack));

    printf("\nStack top value = %d\n", peek(stack));
    
    

    int stackSize = size(stack);
    printf("\n");
    for(int index = 0; index < stackSize; index++){
        printf("Stack value = %d\n", pop(stack));
    }   

    if (destructStack(stack))
        printf("\nDestruct stack complete!!!\n");
    else    
        printf("\nDestruct stack failed-_-\n");
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