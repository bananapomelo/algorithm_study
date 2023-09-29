#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef int QElemType;//队列数据的类型 queue

typedef struct SqQueue
{
	//QElemType data[1024];
  QElemType *data;//指向一段连续的存储空间 来存储队列中的元素
  int front;
  int rear;
  
  int max_len;//表示队列的最大的长度
  int avail_len;//表示当前队列有多少个元素
  	// avail_len 空队列
  	//avail_len == maxlen 满队列
}SqQueue;

/*函数声明*/
SqQueue* InitQueue(int max_len);
void DestoryQueue(SqQueue** q);
void ClearQueue(SqQueue* q);
int QueueIsEmpty(SqQueue* q);
int QueueLength(SqQueue* q);
int GetHead(SqQueue* q,QElemType* e);
int EnQueue(SqQueue* q,QElemType e);
int DeQueue(SqQueue* q,QElemType* e);

#endif 