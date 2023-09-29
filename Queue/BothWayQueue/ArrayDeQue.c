#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ArrayDeQue.h"


/*
    createArrayDeQue: 创建双向循环队列
        @capacity: 队列容量
        @retval: 队列头指针
*/
ADQue *createArrayDeQue(int capacity) {
    ADQue *queue = (ADQue *)malloc(sizeof(queue));
    queue->array = (ElemType *)malloc(sizeof(ElemType) * capacity);
    queue->capacity = capacity;
    queue->front = 0;
    queue->queSize = 0;

    return queue;
}

/*
    destructArrayDeQue: 析构队列
        @queue: 队列头指针
        @retval: 无
*/
void destructArrayDeQue(ADQue *queue) {
    assert(queue);
    assert(queue->array);

    free(queue->array);
    queue->array = NULL;

    free(queue);

    return ;
}

/*
    isEmpty: 队列是否为空
        @queue: 队列头指针
        @retval: 1为空, 0为非空
*/
int isEmpty(ADQue *queue) {
    return !queue->queSize;
}

/*
    capacity: 获取队列容量
        @queue: 队列头指针
        @retval: 队列容量
*/
int capacity(ADQue *queue) {
    assert(queue);
    return queue->capacity;
}

/*
    size: 队列元素个数
        @queue: 队列头指针
        @retval: 队列元素个数
*/
int size(ADQue *queue) {
    assert(queue);
    return queue->queSize;
}



/*
    peekFirst: 获取头部元素
        @queue: 队列头指针
        @retval: 头部元素
*/
ElemType peekFirst(ADQue *queue) {
    assert(queue);
    return queue->array[queue->front];
}

/*
    peekLast: 获取尾部元素
        @queue: 队列头指针
        @retval: 尾部元素
*/
ElemType peekLast(ADQue *queue) {
    assert(queue);
    int rear = subscript(queue, queue->front + queue->queSize - 1);
    return queue->array[rear];
}


/*
    subscript: 下标
        @queue: 队列头指针
        @increment: 增量
        @retval: 下标
*/
int subscript(ADQue *queue, int increment) {
    int index = (increment + queue->capacity) % queue->capacity;
    return index;
}

/*
    pushFirst: 头部入队
        @queue: 队列头指针
        @value: 入队值
        @retval: 无
*/
void pushFirst(ADQue *queue, int value) {
    assert(queue);
    if (queue->queSize >= queue->capacity){
        printf("队列已满, ( %d )无法入队\n", value);
        return ;
    }

    // int index = (increment + queue->queSize) % queue->capacity;
    queue->front= subscript(queue, queue->front - 1);
    queue->array[queue->front] = value;

    queue->queSize++;
    return ;
}

/*
    pushLast: 尾部入队
        @queue: 队列头指针
        @value: 入队值
        @retval: 无
*/
void pushLast(ADQue *queue, int value) {
    assert(queue);
    if (queue->queSize >= queue->capacity){
        printf("队列已满, ( %d )无法入队\n", value);
        return ;
    }

    int rear = subscript(queue, queue->front + queue->queSize);
    queue->array[rear] = value;

    queue->queSize++;
    return ;
}

/*
    popFirst: 头部出队
        @queue: 队列头指针
        @retval: 无
*/
void popFirst(ADQue *queue) {
    assert(queue);
    if (!queue->queSize) {
        printf("队列为空, 无法出队\n");
        return ;
    }

    queue->front = subscript(queue, queue->front + 1);

    queue->queSize--;
    return ;
}

/*
    popLast: 尾部出队
        @queue: 队列头指针
        @retval: 无
*/
void popLast(ADQue *queue) {
    assert(queue);
    if (!queue->queSize) {
        printf("队列为空, 无法出队\n");
        return ;
    }

    queue->queSize--;
    return ;
}

/*
    printADeQue: 打印队列
        @queue: 队列头指针
        @retval: 无
*/
void printADeQue(ADQue *queue) {
    assert(queue);
    assert(queue->queSize);

    int forTime = 0;
    printf("打印队列为: \n");
    while (forTime < queue->queSize) {
        int current = subscript(queue, queue->front + forTime);
        printf("%d \n",  queue->array[current]);

        forTime++;
    }

    return ;
}












