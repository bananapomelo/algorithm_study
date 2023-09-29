#include <stdio.h>
#include <stdbool.h>
#include "ArrayQueue.h"

int main()
{
    AQueue * queue = createArrayQueue(5);

    if (isEmpty(queue)){
        printf("该队列为空队列\n");
    }
    else{
        printf("该队列不为空\n");
    }

    printf("队列容量为: %d\n", capacity(queue));

    while (1){
        ElemType inputValue = 0;
        scanf("%d", &inputValue);
        if (!inputValue)
            break;

        push(queue, inputValue);
    }

    printf("队列中元素个数: %d\n", size(queue));

    printf("队头元素为: %d\n", peek(queue));
    pop(queue);
    
    printf("队列中元素个数: %d\n", size(queue));


    print(queue);

/*
1
2
3
4
5
6
7
8
9
0

*/

    return 0;
}




