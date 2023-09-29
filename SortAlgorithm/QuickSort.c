#include <stdio.h>


/*
    swap: 交换x和y的值
        @x: 待交换变量
        @y: 待交换变量
        @retval: 无返回值
*/
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int medianThree(int *array, int left, int mid, int right) {
    // 异或选取中位数返回

    if ((array[left] < array[mid]) ^ (array[left] < array[right])) {
        return left;
    } else if ((array[mid] < array[left]) ^ (array[mid] < array[right])) {
        return mid;
    } else {
        return right;
    }
}

// 哨兵划分
int partition(int *array, int left, int right) {
    int med = medianThree(array, left, (left + right) / 2, right);
    swap(&array[left], &array[med]);

    int start = left;
    int end = right;

    while (start < end) {
        while (start < end && array[end] >= array[left]) {
            end--;
        }
        while (start < end && array[start] <= array[left]) {
            start++;
        }

        swap(&array[start], &array[end]);
    }
    swap(&array[start], &array[left]);

    return start;
}

/*
    leftRightQuickSort: 快速排序(左右指针法, 递归)
        @array: 待排序部分
        @left: 待排序部分的最左边下标
        @right: 待排序部分的最右边下标
        @retval: 无返回值
*/
void leftRightQuickSort(int *array, int begin, int end) {
    if (begin >= end)
        return ;

    int pivot = partition(array, begin, end);

    leftRightQuickSort(array, begin, pivot - 1);
    leftRightQuickSort(array, pivot + 1, end);

    return ;
}

/*
    quickSOrtTailCall: 尾递归优化后, 左右子树中短的一方进行递归, 长的一方重新进行哨兵划分
    
*/
void quickSortTailCall(int *array, int begin, int end) {
    if (begin >= end)
        return ;
    int left = begin;
    int right = end;

    while (left < right) {

        int pivot = partition(array, left, right);

        if (pivot - left < right - pivot) {
            quickSortTailCall(array, left, pivot - 1);
            left = pivot + 1;
        } else {
            quickSortTailCall(array, pivot + 1, right);
            right = pivot - 1;
        }
    }

}


int main()
{
    // 快速排序(左右指针法, 递归)
    int leftRightQuickSortArray[10] = {12, 38, 74, 17, 80, 71, 50, 92, 51, 13};
    // int leftRightQuickSortArray[10] = {57, 28, 58, 32, 86, 7, 78, 68, 73, 72};
    // int leftRightQuickSortArray[10] = {33, 61, 69, 2, 84, 15, 14, 17, 50, 73};
    // int leftRightQuickSortArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // 打印未排序前的数组
    printf("未优化未排序: ");
    for(int i = 0; i < 10; ++i){
        printf("%d ", leftRightQuickSortArray[i]);
    }
    printf("\n");

    // 调用快速排序函数对数组重新排序
    leftRightQuickSort(leftRightQuickSortArray,0, 9);

    // 打印排序后的数组
    printf("未优化已排序: ");
    for(int i = 0; i < 10; ++i){
        printf("%d ", leftRightQuickSortArray[i]);
    }
    printf("\n\n");

    // 快速排序(尾递归优化)
    int TailCallArray[10] = {12, 38, 74, 17, 80, 71, 50, 92, 51, 13};
    // int leftRightQuickSortArray[10] = {57, 28, 58, 32, 86, 7, 78, 68, 73, 72};
    // int leftRightQuickSortArray[10] = {33, 61, 69, 2, 84, 15, 14, 17, 50, 73};
    // int leftRightQuickSortArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // 打印未排序前的数组
    printf("优化后未排序: ");
    for(int i = 0; i < 10; ++i){
        printf("%d ", TailCallArray[i]);
    }
    printf("\n");

    // 调用快速排序函数对数组重新排序
    quickSortTailCall(TailCallArray,0, 9);

    // 打印排序后的数组
    printf("优化后已排序: ");
    for(int i = 0; i < 10; ++i){
        printf("%d ", TailCallArray[i]);
    }
    printf("\n");

    return 0;
}
