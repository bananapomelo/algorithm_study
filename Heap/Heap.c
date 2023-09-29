#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Heap.h"

/*
    newMaxHeap: 创建堆的结构体
        @heapArray: 层次遍历的堆
        @length: 元素长度
        @retval: 返回堆指针
*/
MaxHeap *newMaxHeap(ElemType *heapArray, int length) {
    MaxHeap *mHeap = (MaxHeap *)malloc(sizeof(*mHeap));
    mHeap->size = length;
    mHeap->data = (ElemType *)malloc(sizeof(ElemType) * INT_MAX);
    printf("line: %d\n", __LINE__);

    memcpy(mHeap->data, heapArray, length * sizeof(int));
    printf("line: %d\n", __LINE__);
    for (int i = length - 1; i >= 0; i--) {
        siftDown(mHeap, i);
    }

    return mHeap;
}

/*
    left: 获取左子节点索引
        @index: 当前节点
        @retval: 左子节点索引
*/
int left(int index) {
    return index * 2 + 1;
}

/*
    right: 获取右子节点索引
        @index: 当前节点
        @retval: 右子节点索引
*/
int right(int index) {
    return index * 2 + 2;
}

/*
    parent: 获取父结点索引
        @index: 当前节点
        @retval:  父结点索引
*/
int parent(int index) {
    return (index - 1) / 2;
}

/*
    size: 堆中元素个数
        @heap: 堆指针
        @retval: 堆中元素个数
*/
int size(MaxHeap *heap) {
    return heap->size;
}

/*
    peek: 获取堆顶元素
        @heap: 堆指针
        @retval: 堆顶元素
*/
ElemType peek(MaxHeap *heap) {
    return heap->data[0];
}

/*
    isEmpty: 判断是否是空堆
        @heap: 堆指针
        @retval: 空堆返回真
*/
int isEmpty(MaxHeap *heap) {
    return !heap->size;
}

/*
    swap: 交换元素
        @data: 数组
        @x: 待交换元素
        @y: 待交换元素
        @retval: 空
*/
void swap(ElemType *data, int x, int y) {
    int t = data[x];
    data[x] = data[y];
    data[y] = t;

    return ;
}

/*
    siftUp: 从堆底向上堆化
        @heap: 堆指针
        @downIndex: 堆底索引
        @retval: 空
*/
void siftUp(MaxHeap *heap, int downIndex) {
    while (1) {
        int parentIndex = parent(downIndex);
        
        if (downIndex <= 0 || heap->data[downIndex] <= heap->data[parentIndex]) {
            break;
        }

        if (heap->data[downIndex] > heap->data[parentIndex]) {
            swap(heap->data, parentIndex, downIndex);
        }

        downIndex = parentIndex;
    }

    return ;
}

/*
    siftDown: 从堆顶向下堆化
        @heap: 堆指针
        @upIndex: 堆顶索引
        @retval: 空
*/
void siftDown(MaxHeap *heap, int upIndex) {
    while (1) {
        int leftI = left(upIndex);
        int rightI = right(upIndex);
        int max = upIndex;

        if (leftI < size(heap) - 1 && heap->data[leftI] > heap->data[max]) {
            max = leftI;
        }

        if (rightI < size(heap) - 1 && heap->data[rightI] > heap->data[max]) {
            max = rightI;
        }

        if (max == upIndex)
            break;

        swap(heap->data, max, upIndex);
        upIndex = max;
    }

    return ;
}

/*
    push: 入堆, 之后进行由底向上堆化
        @heap: 堆指针
        @value: 入堆元素
        @retval: 空
*/
void push(MaxHeap *heap, ElemType value) {
    if (heap->size > INT_MAX) {
        printf("Heap is pull, not push data\n");
        return ;
    }

    heap->data[heap->size] = value;
    heap->size++;

    siftUp(heap, heap->size - 1);

    return ;
}

/*
    pop: 出堆, 之后由上向下堆化
        @heap: 堆指针
        @retval: 返回是否成功出堆
*/
ElemType pop(MaxHeap *heap) {
    if (heap->size < 0) {
        printf("Heap is empty, not pop value\n");
        return 0;
    }

    swap(heap->data, 0, heap->size - 1);
    heap->size--;
    siftDown(heap, 0);
    
    return 1;
}
































