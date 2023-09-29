#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BothWayLinkListWithHead.h"

void selectSort(int *array, int len);

int main()
{
    struct BothHead *head = createList();
    printf("\n\n初始化后:\n");
    printList(head);

    

    head = addNode(head, 88);
    printf("\n\n添加后:\n");
    printList(head);

    head = delNode(head, 12);
    head = delNode(head, 99);
    head = delNode(head, 78);
    printf("\n\n删除后:\n");
    printList(head);

    head = changeNode(head, 34, 85);
    

    int searchNums = 0;
    searchNums = searchNode(head, 39);
    printf("\n\n查找后: %d\n", searchNums);

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

    if (destoryList(head))
        printf("destoryList complete!!!\n");
    else
        printf("destoryList failed - -!\n");

    // 选择排序
    int selectArray [] = {98, 34, 78, 56, 23, 99, 39, 12, 45, 76};
    // int selectArray [] = {9, 3, 7, 2, 6, 1, 5, 8};
    int arrayLen = sizeof(selectArray) / sizeof(selectArray[0]);
    selectSort(selectArray, arrayLen);
    for (int i = 0; i < arrayLen; i++){
        printf("%d ", selectArray[i]);
    }
    printf("\n");


    return 0;
}

void selectSort(int *array, int len){
    for (int i = 0; i < len - 1; i++){
        int min = array[i];
        int minIndex = i;
        for (int j = i + 1; j < len; j++){
            if (min > array[j]){
                min = array[j];
                minIndex = j;
            }
        }
        int temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}
