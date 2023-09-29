#include <stdio.h>

void swap(int *array, int x, int y) {
    int temp = array[x];
    array[x] = array[y];
    array[y] = temp;

    return ;
}

void siftDown(int *array, int start, int heapSize) {
    while (1) {
        int left = start * 2 + 1;
        int right = start * 2 + 2;
        int maxIndex = start; 

        if (left < heapSize && array[left] > array[maxIndex]) {
            maxIndex = left;
        }
        if (right < heapSize && array[right] > array[maxIndex]) {
            maxIndex = right;
        }

        if (maxIndex == start){
            break;
        }

        swap(array, start, maxIndex);

        start = maxIndex;
    }
}

void heapSort(int *array, int heapSize) {
    for (int current = heapSize / 2 - 1; current >= 0; --current) {
        siftDown(array, current, heapSize);
    }

    printf("大根堆: ");
    for (int i = 0; i < 12; i++) {
        printf("%d ", array[i]);
    }
    putchar('\n');

    for (int i = heapSize - 1; i >= 0; i--) {
        swap(array, 0, i);
        siftDown(array, 0, i);
    }

    return ;
}



int main()
{
    int heapArray[12] = {1, 3, 2, 6, 4, 2, 6, 8, 7, 9, 6, 5};

    printf("原始版: ");
    for (int i = 0; i < 12; i++) {
        printf("%d ", heapArray[i]);
    }
    putchar('\n');

    heapSort(heapArray, 12);

    printf("堆排序: ");
    for (int i = 0; i < 12; i++) {
        printf("%d ", heapArray[i]);
    }
    putchar('\n');

    return 0;
}

