#include <stdio.h>
#include <stdbool.h>
#include "SingleSortLinkList.h"


// 冒泡升序排列
void bubbleSortArray(int *array, int length){
    for(int i = 0; i < length - 1; i++){
        for(int j = 0; j < length - 1 - i; j++){
            if(array[j] > array[j + 1]){
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    struct SortHead *SortList = createHead();
    printList(SortList);
    
    SortList = addNodeToList(SortList, 20);
    printf("\n添加后:\n");
    printList(SortList);
    
    SortList = delNode(SortList, 5);
    printf("\n删除后:\n");
    printList(SortList);

    SortList = changeValue(SortList, 12, 88);
    printf("\n修改后:\n");
    printList(SortList);

    printf("\n查找%d: %d个\n", 1, searchValue(SortList, 88));

    if (destroyList(SortList))
        printf("destroy complete\n");
    else
        printf("destroy failed\n");

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
    
    int sortArray[] = {12, 34, 78, 56, 23, 99, 34, 98, 45,76};
    int arrayLen = sizeof(sortArray) / sizeof(sortArray[0]);
    
    bubbleSortArray(sortArray, arrayLen);

    for (int i = 0; i < arrayLen; i++)
        printf("%d ", sortArray[i]);
    printf("\n");
    
    
    return 0;
}