#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LinkDeQue.h"

/*
    createDeQue: 创建双向链式队列
        @retval: 队列头指针
*/
DLQue *createDeQue(){
    DLQue *queue = (DLQue *)malloc(sizeof(queue));
    queue->first = NULL;
    queue->last = NULL;
    queue->nodeNum = 0;

    return queue;
}

/*
    destructDeQue: 销毁双向链式队列
        @queue: 队列头指针
        @retval: 无
*/
void destructDeQue(DLQue *queue){
    assert(queue);
    DLNode *traversal = queue->first;

    while (traversal){
        queue->first = queue->first->next;
        traversal->next = NULL;
        if (queue->first)
            queue->first->prev = NULL;
        free(traversal);
        traversal = queue->first;

        queue->nodeNum--;
    }
    free(queue);
    queue = NULL;

    return ;
}

/*
    sizeDQ: 队列元素数量
        @queue: 队列头指针
        @retval: 队列元素数量
*/
int sizeDQ(DLQue *queue){
    return queue->nodeNum;
}

/*
    isEmptyDQ: 队列是否为空
        @queue: 队列头指针
        @retval: 队列是否为空
*/
int isEmptyDQ(DLQue *queue){
    return !queue->nodeNum;
}

/*
    peekFirstDQ: 获取队列头元素
        @queue: 队列头指针
        @retval: 队列头元素值
*/
ElemType peekFirstDQ(DLQue *queue){
    return queue->first->value;
}

/*
    peekLastDQ: 获取队列尾部元素
        @queue: 队列头指针
        @retval: 队列尾元素值
*/
ElemType peekLastDQ(DLQue *queue){
    return queue->last->value;
}

/*
    pushFirstDQ: 队列头部入队
        @queue: 队列头指针
        @value: 入队值
        @retval: 无
*/
void pushFirstDQ(DLQue *queue, ElemType value){
    assert(queue);

    DLNode *node = (DLNode *)malloc(sizeof(node));
    node->prev = NULL;
    node->next = NULL;
    node->value = value;

    if (!queue->nodeNum){
        queue->first = node;
        queue->last = node;

    }
    else{
        node->next = queue->first;
        queue->first->prev = node;
        queue->first = node;
    }

    queue->nodeNum++;

    return ;
}

/*
    pushLastDQ: 队列尾部入队
        @queue: 队列头指针
        @value: 入队值
        @retval: 无
*/
void pushLastDQ(DLQue *queue, ElemType value){
    assert(queue);

    DLNode *node = (DLNode *)malloc(sizeof(node));
    node->prev = NULL;
    node->next = NULL;
    node->value = value;

    if (!queue->nodeNum){
        queue->first = node;
        queue->last = node;
    }
    else{
        queue->last->next = node;
        node->prev = queue->last;
        queue->last = node;
    }

    queue->nodeNum++;

    return ;
}

/*
    popFirstDQ: 队列头部出队
        @queue: 队列头指针
        @retval: 无
*/
void popFirstDQ(DLQue *queue){
    assert(queue);
    assert(queue->nodeNum);

    DLNode *delNode = queue->first;

    if (queue->nodeNum != 1){
        queue->first = queue->first->next;
        queue->first->prev = NULL;
        delNode->next = NULL;
    }

    free(delNode);
    delNode = NULL;
    queue->nodeNum--;

    return ;
}

/*
    popLastDQ: 队列尾部出队
        @queue: 队列头指针
        @retval: 无
*/
void popLastDQ(DLQue *queue){
    assert(queue);
    assert(queue->nodeNum);

    DLNode *delNode = queue->last;

    if (queue->nodeNum != 1){
        queue->last = queue->last->prev;
        queue->last->next = NULL;
        delNode->prev = NULL;
        
    }

    free(delNode);
    delNode = NULL;
    queue->nodeNum--;

    return ;
}

/*
    printDQ: 打印队列
        @queue: 队列头指针
        @retval: 无
*/
void printDQ(DLQue *queue){
    assert(queue);
    assert(queue->nodeNum);

    DLNode *traversal = queue->first;
    
    printf("打印双向队列: ");
    while (traversal){
        printf("%d ", traversal->value);
        traversal = traversal->next;
    }
    printf("\n");

    return ;
}
