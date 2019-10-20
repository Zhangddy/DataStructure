#include "Queue.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>

void QueueInit(Queue* q)
{
	assert(q);
	q->_back = q->_front = NULL;
}

QNode* BuyQNode(QDataType data)
{
	QNode* pCur = (QNode*)malloc(sizeof(QNode));
	if (NULL == pCur)
	{
		assert(0);
		return NULL;
	}
	pCur->_data = data;
	pCur->_pNext = NULL;
	return pCur;
}

void QueuePush(Queue* q, QDataType data)
{
	assert(q);
	QNode* newQNode = BuyQNode(data);
	
	if (QueueEmpty(q))
	{
		q->_front = q->_back = newQNode;
	}
	else
	{
		q->_back->_pNext = newQNode;
		q->_back = newQNode;
	}
}

void QueuePop(Queue* q)
{
	assert(q);
	
	if (QueueEmpty(q))
	{
		return;
	}
	QNode* pDelNode = q->_front;
	if (NULL == pDelNode->_pNext)
	{
		q->_front = q->_back = NULL;
	}
	else
	{
		q->_front = q->_front->_pNext;
	}
	free(pDelNode);
}

QDataType QueueFront(Queue* q)
{
	assert(q);
	return q->_front->_data;
}

QDataType QueueBack(Queue* q)
{
	assert(q);
	return q->_back->_data;
}

int QueueSize(Queue* q)
{
	assert(q);
	QNode* pCur = q->_front;
	int size = 0;
	while (pCur)
	{
		pCur = pCur->_pNext;
		size++;
	}
	return size;
}

int QueueEmpty(Queue* q)
{
	assert(q);
	return NULL == q->_front;
}

void QueueDestroy(Queue* q)
{
	assert(q);
	QNode* pCur = q->_front;

	while (pCur)
	{
		q->_front = q->_front->_pNext;
		free(pCur);
		pCur = q->_front;
	}
	q->_front = q->_back = NULL;
}

void test()
{
	Queue que;
	QueueInit(&que);
	QueuePush(&que, 1);
	QueuePush(&que, 2);
	QueuePush(&que, 3);
	QueuePush(&que, 4);
	QueuePush(&que, 5);
	printf("%d %d %d \n", QueueFront(&que), QueueBack(&que), QueueSize(&que));
	QueuePop(&que);
	QueuePop(&que);
	QueuePush(&que, 6);
	printf("%d %d %d \n", QueueFront(&que), QueueBack(&que), QueueSize(&que));

	QueueDestroy(&que);
}