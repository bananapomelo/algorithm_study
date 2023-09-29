#include <stdio.h>
#include <stdbool.h>
#include "CircleBothSortList.h"


int main()
{
    CBSHead *head = createList();
    printf("\n\n初始化后:\n");
    printList(head);

    head = addNode(head, 88, NULL);
    printf("\n\n添加后:\n");
    printList(head);

    head = delNode(head, 45);
    printf("\n\n删除后:\n");
    printList(head);

    head = changeNode(head, 39, 89);
    printf("\n\n修改后:\n");
    printList(head);

    int equalNum = searchNode(head, 99);
    printf("\n\n查找后:%d\n",equalNum);

    if (destroyList(head))
        printf("\n\ndestroy list success ^_^\n");
    else
        printf("\n\ndestroy list failed \n");


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










