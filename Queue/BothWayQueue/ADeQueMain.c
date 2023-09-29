#include <stdio.h>
#include "ArrayDeQue.h"

int main() {
    ADQue *queue = createArrayDeQue(11);
    
    if (!isEmpty(queue))
        printf("该队列为空\n");
    else
        printf("该队列非空\n");

    printf("该队列容量为: %d\n", capacity(queue));

    int flag = 0;
    printf("输入入队元素: \n");
    while (1) {
        int inputValue = 0;
        scanf("%d", &inputValue);
        if (!inputValue)
            break;

        if (flag++ < 9)
            pushLast(queue, inputValue);
        else
            pushFirst(queue, inputValue);
    }
    printf("队首值: %d\n", peekFirst(queue));
    printf("队尾值: %d\n", peekLast(queue));

    printf("队列中元素个数为: %d\n", size(queue));

    popFirst(queue);
    popLast(queue);

    printf("line: %d\n", __LINE__);
    printADeQue(queue);

    destructArrayDeQue(queue);


/*
2
3
4
5
6
7
8
9
98
1
99
0

*/
    return 0;
}



























