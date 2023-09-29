#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "LinkQueue.h"


/*
    createLinkQueue: 创建链式队列
        @retval: 队列头指针
*/
LQueue *createLinkQueue(){
    LQueue *queue = (LQueue *)malloc(sizeof(queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->nodeNum = 0;

    return queue;
}

/*
    destructLinkQueue: 析构队列
        @queue: 队列头指针
        @retval: 无
*/
void destructLinkQueue(LQueue *queue){
    assert(queue);
    if (!queue->nodeNum){
        free(queue);
    }
    else{
        QNode *traversal = queue->front;

        while (traversal){
            queue->front = queue->front->next;
            free(traversal);
            traversal = queue->front;
            queue->nodeNum--;
        }
    }

}

/*
    size: 队列大小
        @queue: 队列头指针
        @retval: 队列大小
*/
int size(LQueue *queue){
    assert(queue);

    return queue->nodeNum;
}

/*
    isEmpty: 判断队列是否为空
        @queue: 队列头指针
        @retval: true为队列空
*/
bool isEmpty(LQueue *queue){
    return !queue->nodeNum;
}

/*
    peek: 获取队列待出队值
        @queue: 队列头指针
        @retval: 队列头部值
*/
ElemType peek(LQueue *queue){
    assert(queue);
    assert(queue->front);
    return queue->front->value;
}


/*
    push: 入队
        @queue: 队列头指针
        @value: 待入队值
        @retval: 无
*/
void push(LQueue *queue, ElemType value){
    assert(queue);

    QNode *newNode = (QNode *)malloc(sizeof(newNode));
    newNode->next = NULL;
    newNode->value = value;

    if (!queue->nodeNum){
        queue->front = newNode;
        queue->rear = newNode;
    }
    else{
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->nodeNum++;
}

/*
    pop: 出队
        @queue: 队列头指针
        @retval: 无
*/
void pop(LQueue *queue){
    assert(queue);
    assert(queue->nodeNum);

    QNode *delNode = queue->front;
    queue->front = queue->front->next;

    delNode->next = NULL;
    free(delNode);
    delNode = NULL;

    queue->nodeNum--;

}


/*
    print: 打印整个链表
        @queue: 队列头指针
        @retval: 无
*/
void print(LQueue *queue){
    assert(queue);
    assert(queue->nodeNum);

    printf("打印队列: ");
    QNode *printValue = queue->front;
    while(printValue){
        printf("%d ", printValue->value);
        printValue = printValue->next;
    }
    printf("\n");

}