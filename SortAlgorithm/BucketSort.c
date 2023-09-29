#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 4;

typedef float ElemType;

void swap(ElemType *x, ElemType *y) {
    ElemType temp = *x;
    *x = *y;
    *y = temp;

    return ;
}

int medianThree(ElemType *array, int left, int right) {
    int med = (left + right) / 2;

    if ((array[left] <= array[med]) ^ (array[left] <= array[right])) {
        return left;
    } else if ((array[med] <= array[left]) ^ (array[med] <= array[right])) {
        return med;
    } else {
        return right;
    }
}


int partition(ElemType *array, int left, int right) {
    int mid = medianThree(array, left, right);
    if (mid != left)
        swap(&array[left], &array[mid]);
    
    int begin = left;
    int end = right;

    while (begin < end) {

        while (begin < end && array[end] >= array[left]) {
            end--;
        }
        while (begin < end && array[begin] <= array[left]) {
            begin++;
        }

        swap(&array[begin], &array[end]);
    }
    swap(&array[begin], &array[left]);


    return begin;
}

void quickSort(ElemType *array, int begin, int end) {
    if (begin >= end)
        return ;

    int left = begin;
    int right = end;

    while (left < right) {
        int pivot = partition(array, left, right);

        if (pivot - left < pivot - right) {
            quickSort(array, left, pivot - 1);
            left = pivot + 1;
        } else {
            quickSort (array, pivot + 1, right);
            right = pivot - 1;
        }
    }

    return ;
}


void bucketSort(ElemType *array, int size) {
    int bucketNum = size / 2;
    ElemType **bucket;
    bucket = calloc(bucketNum, sizeof(ElemType *));

    for (int i = 0; i < bucketNum; i++) {
        bucket[i] = calloc(size, sizeof(ElemType));
    }

    // 将待排序数据按照有序顺序存储到不同的桶中
    for (int i = 0; i < size; i++) {
        int index = array[i] * bucketNum;
        int bIndex = 0;

        while (bucket[index][bIndex] > 0 && bucket[index][bIndex] < array[i]) {
            bIndex++;
        }

        ElemType temp = array[i];
        while (bIndex < size && bucket[index][bIndex] > 0) {
            swap(&temp, &bucket[index][bIndex]);
            bIndex++;
        }

        bucket[index][bIndex] = temp;
    }

    // // 对每个桶进行排序
    // for (int i = 0; i < bucketNum; i++) {
    //     // 找到桶中最后一个有数据的下标
    //     int trueIndex = size - 1;
    //     for (trueIndex; trueIndex >= 0; trueIndex--) {
    //         if (bucket[i][trueIndex])
    //             break;
    //     }
    //     // 该桶中无任何数据
    //     if (trueIndex < 0) {
    //         continue;
    //     }
    //     // 对每个桶内数据进行排序
    //     quickSort(bucket[i], 0, trueIndex);
    // }

    for (int aIndex = 0, i = 0; i < bucketNum; i++) {
        for (int j = 0; j < size; j++) {
            if (bucket[i][j]) {
                array[aIndex++] = bucket[i][j];
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", array[i]);
    }
    putchar('\n');

    for (int i = 0; i < bucketNum; i++) {
        printf("line: %d\n", __LINE__);
        free(bucket[i]);
    }
    free(bucket);

}

int main()
{
    ElemType bucketArray[10] = {0.49, 0.96, 0.82, 0.09, 0.57, 0.43, 0.91, 0.75, 0.15, 0.37};

    // quickSort(bucketArray, 0, 10);
    bucketSort(bucketArray, 10);

    for (int i = 0; i < 10; i++) {
        printf("%.2f ", bucketArray[i]);
    }
    putchar('\n');

    return 0;
}


