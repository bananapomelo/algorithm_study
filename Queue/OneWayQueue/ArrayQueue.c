#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "ArrayQueue.h"


/*
    createArrayQyeye: 创建循环队列
        @capacity: 队列容量
        @retval: 队列头指针
*/
AQueue *createArrayQueue(int capacity){
    AQueue *queue = (AQueue *)malloc(sizeof(queue));
    queue->capacity = capacity;
    queue->array = (ElemType *)malloc(sizeof(ElemType) * queue->capacity);
    queue->front = 0;
    queue->queSize = 0;

    return queue;
}

/*
    delArrayQueue: 析构循环队列
        @queue: 队列头指针
        @retval: 无
*/
void delArrayQueue(AQueue *queue){
    assert(queue);
    if (queue->array){
        free(queue->array);
        queue->array = NULL;
    }
    
    free(queue);
    queue = NULL;
}

/*
    capacity: 获取队列容量
        @queue: 队列头指针
        @retval: 队列容量
*/
int capacity(AQueue *queue){
    assert(queue);
    return queue->capacity;
}

/*
    size: 已入队数
        @queue: 队列头指针
        @retval: 已入队数
*/
int size(AQueue *queue){
    assert(queue);
    return queue->queSize;
}

/*
    isEmpty: 判断是否是空队列
        @queue: 队列头指针
        @retval: true为空
*/
bool isEmpty(AQueue *queue){
    assert(queue);
    return !queue->queSize;
}

/*
    peek: 获取队列头元素
        @queue: 队列头指针
        @retval: 队列头元素值
*/
ElemType peek(AQueue *queue){
    assert(queue);
    assert(!isEmpty(queue));

    return queue->array[queue->front];
}

/*
    push: 入队
        @queue: 队列头指针
        @retval: 无
*/
void push(AQueue *queue, ElemType value){
    assert(queue);
    if (queue->queSize == queue->capacity){
        printf("队列已满, 无法存储!!!\n");
        return ;
    }

    // 循环队尾下标: 队尾下标 = (队头下标 + 元素个数) % 容量
    int rear = (queue->front + queue->queSize) % queue->capacity;

    queue->array[rear] = value;
    printf("rear: %d, value: %d\n", rear, queue->array[rear]);
    queue->queSize++;

    return ;
}

/*
    pop: 出队
        @queue: 队列头指针
        @retval: 无
*/
void pop(AQueue *queue){
    assert(queue);
    if (!queue->queSize){
        printf("队列为空, 无法继续出队!!!\n");
        return ;
    }
    queue->array[queue->front] = 0;

    queue->front = (queue->front + 1) % queue->capacity;
    queue->queSize--;
}

/*
    print: 打印队列元素
        @queue: 队列头指针
        @retval: 无
*/
void print(AQueue *queue){
    assert(queue);
    assert(queue->queSize);

    int traversal = queue->front;

    printf("打印序列为: ");
    while(queue->queSize--){
        printf("%d ", queue->array[traversal]);
        traversal = (traversal + 1) % queue->capacity;
    }

    printf("\n");
}
