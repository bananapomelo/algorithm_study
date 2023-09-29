#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

/* 随机数 */
int randomAccess(int *nums, int size){
    int randomIndex = rand() % size;
    int randomNum = nums[randomIndex];
    return randomNum;
}

/* 扩展数组长度 */
int *arrayExtend(int *originArray, int size, int enlarge){
    int *extendArray = (int *)malloc(sizeof(*extendArray) * (size + enlarge));
    for (int i = 0; i < size; i++)
        extendArray[i] = originArray[i];

    for (int i = size; i < size + enlarge; i++)
        extendArray[i] = 0;
    
    return extendArray;
}

/* 数组增加元素 */
void insert(int *array, int size, int num, int index){
    for (int i = size -1; i > index; i--)
        array[i] = array[i - 1];
    array[index] = num;
}

/* 数组减少元素 */
void removeData(int *array, int size, int index){
    for(int i = index; i < size - 1; i++){
        array[i] = array[i+1];
    }
}

int main()
{
    int num[5] = {9, 21, 41, 23, 44};
    srand((unsigned)time(NULL));
    printf("%d\n", randomAccess(num, 5));
    
    /* 扩展数组长度 */
    int oldArray[10] = {9, 8, 7, 4, 5, 6, 2, 1, 3, 9};
    int arrayLength = sizeof(oldArray) / sizeof(int);
    int *newArray = arrayExtend(oldArray, arrayLength, 10);
    arrayLength = arrayLength + 10;
    printf("newArray: ");
    for (int i = 0; i < arrayLength; i++){
        printf("%d ", newArray[i]);
    }
    printf("\n");
    free(newArray);

    int insertArray[7] = {1, 3, 4, 5, 6};
    insert(insertArray, 7, 2, 1);
    for(int i = 0; i < 7; i++)
        printf("insertArray[%d] = %d\n", i, insertArray[i]);

    removeData(insertArray, 7, 1);
    for(int i = 0; i < 7; i++)
        printf("insertArray[%d] = %d\n", i, insertArray[i]);

    return 0;
}
