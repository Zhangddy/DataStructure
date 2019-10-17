#include "DList.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

void DListInit(PDLNode* pHead)
{
	assert(pHead);

	*pHead = (PDLNode)malloc(sizeof(DLNode));

	if (NULL == *pHead)
	{
		assert(0);
		return;
	}

	(*pHead)->_pNext = *pHead;
	(*pHead)->_pPre = *pHead;
}

void DListDestroy(PDLNode* pHead)
{
	// 改变指向, 二级指针
	DListClear(*pHead);
	free(*pHead);
	(*pHead) = NULL;
}

PDLNode BuyDListNode(DLDataType data)
{
	PDLNode pNewNode = (PDLNode)malloc(sizeof(DLNode));
	if (NULL == pNewNode)
	{
		assert(0);
		return NULL;
	}
	pNewNode->_data = data;
	pNewNode->_pNext = NULL;
	pNewNode->_pPre = NULL;
	return pNewNode;
}

void DListPushBack(PDLNode pHead, DLDataType data)
{
	assert(pHead);
	PDLNode pNewNode = BuyDListNode(data);
	pNewNode->_pPre = pHead->_pPre;
	pNewNode->_pNext = pHead;
	pHead->_pPre = pNewNode;
	pNewNode->_pPre->_pNext = pNewNode;
	
}
void DListPopBack(PDLNode pHead)
{
	assert(pHead);
	if (pHead->_pNext == pHead)
	{
		return;
	}
	PDLNode pDelNode = pHead->_pPre;
	pDelNode->_pPre->_pNext = pDelNode->_pNext;
	pDelNode->_pNext->_pPre = pDelNode->_pPre;
	free(pDelNode);
}

void DListPushFront(PDLNode pHead, DLDataType data)
{
	assert(pHead);
	PDLNode pNewNode = BuyDListNode(data);
	pNewNode->_pPre = pHead;
	pNewNode->_pNext = pHead->_pNext;
	pHead->_pNext = pNewNode;
	pNewNode->_pNext->_pPre = pNewNode;
}

void DListPopFront(PDLNode pHead)
{
	assert(pHead);
	if (pHead->_pNext == pHead)
	{
		return;
	}

	PDLNode pDelNode = pHead->_pNext;
	pDelNode->_pNext->_pPre = pHead;
	pHead->_pNext = pDelNode->_pNext;
	free(pDelNode);
}
void DListInsert(PDLNode pos, DLDataType data)
{
	if (NULL == pos)
	{
		return;
	}
	PDLNode pNewNode = BuyDListNode(data);

	pNewNode->_pPre = pos->_pPre;
	pNewNode->_pNext = pos;
	pNewNode->_pPre->_pNext = pNewNode;
	pNewNode->_pNext->_pPre = pNewNode;
	
}

void DListErase(PDLNode pos)
{
	if (NULL == pos)
	{
		return;
	}
	pos->_pPre->_pNext = pos->_pNext;
	pos->_pNext->_pPre = pos->_pPre;
	free(pos);
}
void DListClear(PDLNode pHead)
{
	// 清空, 不删除头结点
	assert(pHead);
	PDLNode pCur = pHead->_pNext;
	while (pCur != pHead)
	{
		pHead->_pNext = pCur->_pNext;
		free(pCur);
		pCur = pHead->_pNext;
	}
	pHead->_pNext = pHead;
	pHead->_pPre = pHead;
}

void PrintDList(PDLNode pHead)
{
	PDLNode pCur = pHead;
	while (pCur->_pNext && pCur->_pNext != pHead)
	{
		printf("%d  ", pCur->_pNext->_data);
		pCur = pCur->_pNext;
	}
}

void TestDList()
{
	PDLNode pHead = NULL;
	DListInit(&pHead);
	DListPushBack(pHead, 1);
	DListPushBack(pHead, 2);
	DListPushBack(pHead, 3);
	DListPushBack(pHead, 4);
	DListPushBack(pHead, 5);
	PrintDList(pHead);
	DListDestroy(&pHead);
}