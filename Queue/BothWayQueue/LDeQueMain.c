#include <stdio.h>
#include "LinkDeQue.h"

int main()
{
    DLQue *queue = createDeQue();

    if (isEmptyDQ(queue))
        printf("双向队列为空\n");
    else
        printf("双向队列不为空\n");

    int flag = 0;
    while (1){
        int inputValue = 0;
        scanf("%d", &inputValue);

        if (inputValue == 0)
            break;

        flag++;
        // 偶数则在队列头入队
        if (flag % 2){
            pushFirstDQ(queue, inputValue);
        }
        else{
            pushLastDQ(queue, inputValue);
        }
    }

    printf("队列中元素个数: %d\n", sizeDQ(queue));
    printDQ(queue);

    printf("头部元素: %d\n", peekFirstDQ(queue));
    printf("尾部元素: %d\n", peekLastDQ(queue));

    printf("队列头部出队\n");
    popFirstDQ(queue);

    printf("队列尾部出队\n");
    popLastDQ(queue);

    printDQ(queue);

    destructDeQue(queue);

/*
9
2
7
4
5
6
3
8
1
10
99
99
0

*/
    return 0;
}