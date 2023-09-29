#include "SeqQueue.h"

/*
	InitQueue:初始化一个队列
*/
SqQueue* InitQueue(int max_len)
{
	SqQueue* q = malloc(sizeof(*q));
	q->data = malloc(max_len*sizeof(QElemType));

	q->front = q->rear = 0;
	q->max_len = max_len;
	q->avail_len = 0;
	return q;
}

/*
	DestoryQueue:销毁一个队列
*/
void DestoryQueue(SqQueue** q)
{
	if(NULL == *q) return;
	if((*q)->data) free((*q)->data);

	(*q)->data=NULL;
	free(*q);
	*q = NULL;
}

/*
	ClearQueue:清空一个队列
*/
void ClearQueue(SqQueue* q)
{
	if(q == NULL) return ;
	q->front = q->rear = 0;
	q->avail_len = 0;
}

/*
	QueueIsEmpty:判断一个队列是否为空
*/
int QueueIsEmpty(SqQueue* q)
{
	if(NULL == q || q->data == NULL) return 1;
	return (q->avail_len == 0)?1:0;
}

/*
	QueueLength:队列中元素的个数，即长度
*/
int QueueLength(SqQueue* q)
{
	if(NULL == q || q->data == NULL) return 0;
	return q->avail_len;
}

/*
	GetHead:获取队头的元素，但是不出队
*/
int GetHead(SqQueue* q,QElemType* e)
{
	if(q == NULL || q->data == NULL || q->avail_len == 0) return 0;
	*e = q->data[q->front];
	return 1;
}

/*
	EnQueue:入队
*/
int EnQueue(SqQueue* q,QElemType e)
{
	if(q == NULL || q->data == NULL || q->avail_len == q->max_len) return 0;
	q->data[q->rear] = e;
	q->rear++;
	if(q->rear==q->max_len) q->rear=0;
	q->avail_len++;
	return 1;
}

/*	
	DeQueue:出队
*/
int DeQueue(SqQueue* q,QElemType* e)
{
	if(q == NULL || q->data == NULL || q->avail_len==0) return 0;
	*e = q->data[q->front];
	q->front++;
	if(q->front==q->max_len) q->front=0;
	q->avail_len--;
	return 1;
}



