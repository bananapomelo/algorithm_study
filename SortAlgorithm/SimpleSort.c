#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_NUMS 10

/* 
    1.排序算法
    2.选择排序
    3.冒泡排序
    4.插入排序
    5.快速排序
    6.归并排序
    7.堆排序
    8.桶排序
    9.计数排序
    10.基数排序
*/
void bubbleSortArray(int *array, int length);
void selectSort(int *array, int lenth);
void insertSort(int *array, int len);
void swap(int *x, int *y);
void leftRightQuickSort(int *array, int left, int right);

void ShellSort(int* arr, int n);

int main()
{
    // 冒泡排序
    int bubbleArray[] = {12, 34, 78, 56, 23, 99, 34, 98, 45,76};
    int arrayLen = sizeof(bubbleArray) / sizeof(bubbleArray[0]);
    
    bubbleSortArray(bubbleArray, arrayLen);

    printf("Bubble sorted: ");
    for (int i = 0; i < arrayLen; i++)
        printf("%d ", bubbleArray[i]);
    printf("\n");


    // 选择排序
    int selectArray [] = {98, 34, 78, 56, 23, 99, 39, 12, 45, 76};
    // int selectArray [] = {9, 3, 7, 2, 6, 1, 5, 8};
    arrayLen = sizeof(selectArray) / sizeof(selectArray[0]);
    selectSort(selectArray, arrayLen);
    printf("Select sorted: ");
    for (int i = 0; i < arrayLen; i++){
        printf("%d ", selectArray[i]);
    }
    printf("\n");

    // 生成随机数种子
    srand((unsigned)time(NULL));
    

    // 插入排序
    int *insertArray = (int *)malloc(sizeof(*insertArray) * ARRAY_NUMS);
    for(int i = 0; i < ARRAY_NUMS; ++i){
        insertArray[i] = rand() % (100-5+1);
    }

    insertSort(insertArray, ARRAY_NUMS);
    printf("Insert Sorted: ");
    for(int i = 0; i < ARRAY_NUMS; ++i){
        printf("%d ", insertArray[i]);
    }
    printf("\n");

    
    // 快速排序(左右指针, 递归)
    int *leftRightQuickSortArray = (int *)malloc(sizeof(*leftRightQuickSortArray) * ARRAY_NUMS);
    for(int i = 0; i < ARRAY_NUMS; ++i){
        leftRightQuickSortArray[i] = rand() % (100-5+1);
    }

    printf("Left and right quick unso: ");
    for(int i = 0; i < ARRAY_NUMS; ++i){
        printf("%d ", leftRightQuickSortArray[i]);
    }
    printf("\n");

    leftRightQuickSort(leftRightQuickSortArray,0, ARRAY_NUMS - 1);
    printf("Left and right quick sort: ");
    for(int i = 0; i < ARRAY_NUMS; ++i){
        printf("%d ", leftRightQuickSortArray[i]);
    }
    printf("\n");


    // int *leftRightQuickSortArray = (int *)malloc(sizeof(*leftRightQuickSortArray) * ARRAY_NUMS);
    // for(int i = 0; i < ARRAY_NUMS; ++i){
    //     leftRightQuickSortArray[i] = rand() % (100-5+1);
    // }

    // printf("Left and right quick unso: ");
    // for(int i = 0; i < ARRAY_NUMS; ++i){
    //     printf("%d ", leftRightQuickSortArray[i]);
    // }
    // printf("\n");

    // ShellSort()


}

// 冒泡排序(升序)
void bubbleSortArray(int *array, int length){
    for (int i = 0; i < length - 1; i++) {
        int flag = 0;
        for (int j = 0; j < length - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                flag = 1;
            }
        }

        if (!flag)
            break;
    }
    
    return ;
}

// 选择排序(升序)
void selectSort(int *array, int length){
    for (int i = 0; i < length - 1; i++) {
        int index = i;
        for (int j = i + 1; j < length; j++) {
            if (array[j] < array[index]){
                index = j;
            }
        }
        if (index != i) {
            swap(&array[i], &array[index]);
        }
    }
}

// 插入排序(升序)
void insertSort(int *array, int len){
    for (int i = 1; i < len - 1; i++) {
        int base = array[i], j = i - 1;
        while (j >= 0 && array[j] > base) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = base;
    }

    return ;
}

/*
    swap: 交换x和y的值
        @x: 待交换变量
        @y: 待交换变量
*/
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

/*
    leftRightQuickSort: 快速排序(左右指针, 递归)
        @array: 待排序部分
        @left: 待排序部分的最左边下标
        @right: 待排序部分的最右边下标
*/
void leftRightQuickSort(int *array, int begin, int end){
    if (begin >= end)
        return;

    // 不动起点和终点, 新增变量用于判断
    int left = begin;
    int right = end;
    int baseValue = array[begin];

    while (left < right){
        // 注意: 以最左边的值为基准, 那就先从右指针开始走, 反之从左指针走
        // 因为: 5      4       7      8   时, 
        //             ^       ^
        //             |       |
        //            left    right
        // left在4位置, right在7位置, left和right必定相遇, 必须让left == right时, 
        //      array[right] < 5, 所以只能右指针先走

        // 找到第一个比基准值小的数
        while (array[right] >= baseValue && left < right)
            --right;

        // 找到第一个比基准值大的数
        while (array[left] <= baseValue && left < right)
            ++left;

        // 交换
        swap(&array[left], &array[right]);
    }

    // 当left == right时, left左边的值(包括left)都小于等于基准值, right右边的值都大于等于基准值
    // 所以只需要将基准值和left交换即可
    swap(&array[begin], &array[right]);

    leftRightQuickSort(array, begin, right - 1);
    leftRightQuickSort(array, right + 1, end);
}