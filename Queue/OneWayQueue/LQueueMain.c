#include <stdio.h>
#include <stdbool.h>
#include "LinkQueue.h"

int main()
{
    LQueue *queue = createLinkQueue();

    if (isEmpty(queue))
        printf("Link queue is empty!!!\n");
    else
        printf("Link queue is not empty!!!\n");

    while (1){
        ElemType inputValue = 0;
        scanf("%d", &inputValue);
    
        if (!inputValue)
            break;

        push(queue, inputValue);
    }

    printf("peek: %d\n", peek(queue));

    pop(queue);
    printf("pop complete\n");

    print(queue);

    destructLinkQueue(queue);

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
