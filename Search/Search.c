#include <stdio.h>

/*
    二分查找适用于有序数组，大数据量，时间复杂度为logn，
    小数据量适合线性查找，因为二分查找需要加法减法和1~3次判断，而线性查找只需要判断即可
    二分查找不适用于链式结构
    如果数组是无序的， 更适用于线性查找因为排序算法的时间复杂度通常为O(nlogn), 复杂度比查找算法高
*/

// 二分查找(双闭区间)
int binarySearch(int *array, int len, int target) {
    int head = 0, rear = len - 1;

    while (head <= rear) {
        int mid = (head + (rear - head) / 2);

        if (target < array[mid]) {
            rear = mid - 1;
        } else if (target > array[mid]) {
            head = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

/* 二分查找最左一个元素 */
int binarySearchLeftEdge(int *array, int len, int target) {
    int start = 0, end = len - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (array[mid] > target) {
            end = mid - 1;
        } else if (array[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    if (start < len && array[start] == target) {
        return start;
    }

    return -1;
}

/* 二分查找最右一个元素 */
int binarySearchRightEdge(int *array, int len, int target) {
    int start = 0, end = len - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (array[mid] > target) {
            end = mid - 1;
        } else if (array[mid] < target) {
            start = mid + 1;
        } else {
            start = mid + 1;
        }
    }

    if (end < len && array[end] == target) {
        return end;
    }

    return -1;
}

int main()
{
    
    int SearchArray[9] = {1, 6, 6, 6, 6, 6, 10, 12, 32};
    int len = 9;
    int ret = binarySearch(SearchArray, len, 6);

    if (ret != -1)
        printf("search value index: %d\n", ret);
    else
        printf("Not found!!!\n");

    ret = binarySearchLeftEdge(SearchArray, len, 6);

    if (ret != -1)
        printf("search value left index: %d\n", ret);
    else
        printf("Not found!!!\n");

    ret = binarySearchRightEdge(SearchArray, len, 6);

    if (ret != -1)
        printf("search value right index: %d\n", ret);
    else
        printf("Not found!!!\n");

}