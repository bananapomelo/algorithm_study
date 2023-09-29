#include <stdio.h>
#include <string.h>

// 对左右数组进行有序合并
void merge(int *array, int left, int mid, int right) {
    int temp[right - left + 1]; // 创建临时数组用于有序合并
    memset(temp, 0, right - left + 1); // 给临时数组赋初值(注意是给临时数组赋初值)

    for (int i = left; i <= right; i++) {
        temp[i - left] = array[i]; // 赋值真实数组值
    }

    int leftStart = left - left, leftEnd = mid - left;  // 左子数组的下标
    int rightStart = mid - left + 1, rightEnd = right - left; // 右子数组的下标

    for (int i = left; i <= right; i++) {
        if (leftStart > leftEnd) { // 如果左子数组没有值了, 直接用右子数组覆盖原数组
            array[i] = temp[rightStart++];
        } else if (rightStart > rightEnd || temp[leftStart] <= temp[rightStart]) { // 右子数组没有值, 或者左子数组值比右子数组小
            array[i] = temp[leftStart++];
        } else {  // 右子数组比左子数组值小
            array[i] = temp[rightStart++];
        }
    }

    return ;
}

void mergeSort(int *array, int left, int right) {
    if (left >= right)
        return ;

    int mid = (left + right) / 2;

    mergeSort(array, left, mid); // 递归左子数组
    mergeSort(array, mid + 1, right); // 递归右子数组
    merge(array, left, mid, right); // 合并数组

    return ;
}
int main()
{
    // 归并排序(先拆分再合并)
    int mergeArray[10] = {12, 38, 74, 17, 80, 71, 50, 92, 51, 13};
    // int mergeArray[10] = {57, 28, 58, 32, 86, 7, 78, 68, 73, 72};
    // int mergeArray[10] = {33, 61, 69, 2, 84, 15, 14, 17, 50, 73};
    // int mergeArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // 打印未排序前的数组
    printf("未排序: ");
    for(int i = 0; i < 10; ++i){
        printf("%d ", mergeArray[i]);
    }
    printf("\n");

    // 调用归并排序函数对数组重新排序
    mergeSort(mergeArray,0, 9);

    // 打印排序后的数组
    printf("已排序: ");
    for(int i = 0; i < 10; ++i){
        printf("%d ", mergeArray[i]);
    }
    printf("\n\n");


}

