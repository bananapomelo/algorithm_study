#include <stdio.h>
#include <unistd.h>
#include "CircleLinkListWithHead.h"

int main()
{
    CSHead * head = createList();
    /*  printList( )为打印整个链表一次
        proveCircle()用于证明是循环链表, 会按照时间间隔多次打印  */
    printf("\n\n初始化后: \n");
    printList(head);
    // proveCircle(head); 
    printf("\n\n");   

    head = addNode(head, 22);
    printf("添加后: \n");
    printList(head);
    printf("\n\n");   

    head = delNode(head, 23);
    printf("删除后: \n");
    printList(head);
    printf("\n\n");   

    head = changeNode(head, 22, 88);
    printf("排序后: \n");
    printList(head);
    printf("\n\n");   
 

    


    if (destroyList(head))
        printf("destory List Complete ^_^\n");

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