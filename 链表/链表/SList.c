#include "SList.h"
#include <assert.h>
#include <stdio.h>
#include <malloc.h>

void SListInit(SList* s)
{
	assert(s);
	s->_pHead = NULL;
}

void SListDestory(SList* s)
{
	assert(s);
	PNode pCur = s->_pHead;
	while (pCur)
	{
		SListPopFront(s);
		pCur = s->_pHead;
	}
}

// ���ڴ���һ���½ڵ�
PNode BuySListNode(SDataType data)
{
	PNode pCur = (PNode)malloc(sizeof(Node));
	pCur->_data = data;
	pCur->_pNext = NULL;
	return pCur;
}

void SListPushBack(SList* s, SDataType data)
{
	assert(s);
	PNode pNewPNode = BuySListNode(data);
	if (NULL == s->_pHead)
	{
		// ������
		s->_pHead = pNewPNode;
	}
	else
	{
		// ����ǿ�
		// �����������һ���ڵ�
		PNode pCur = s->_pHead;
		while (pCur->_pNext)
		{
			pCur = pCur->_pNext;
		}
		pCur->_pNext = pNewPNode;
	}
}

void SListPopBack(SList* s)
{
	assert(s);
	if (NULL == s->_pHead)	// ������
	{
		return;
	}
	else if (NULL == s->_pHead->_pNext)	// ֻ��һ���ڵ�
	{
		free(s->_pHead);
		s->_pHead = NULL;
	}
	else	// ����ڵ�
	{
		PNode pPre = NULL;
		PNode pCur = s->_pHead;
		while (pCur->_pNext)
		{
			pPre = pCur;
			pCur = pCur->_pNext;
		}

		free(pCur);
		pPre->_pNext = NULL;
	}
}

void SListPushFront(SList* s, SDataType data)
{
	assert(s);
	PNode pNewNode = BuySListNode(data);
	pNewNode->_pNext = s->_pHead;
	s->_pHead = pNewNode;
}

void SListPopFront(SList* s)
{
	assert(s);
	if (NULL == s->_pHead)
	{
		return;
	}
	PNode pDelNode = s->_pHead;
	s->_pHead = pDelNode->_pNext;
	free(pDelNode);
}

void SListInsert(PNode pos, SDataType data)
{
	if (NULL == pos)
	{
		return;
	}
	PNode pNewNode = BuySListNode(data);
	pNewNode->_pNext = pos->_pNext;
	pos->_pNext = pNewNode;
}

void SListErase(SList* s, PNode pos)
{
	// ɾ��Posָ��, �����ҵ�ǰһ��
	assert(s);
	if (NULL == pos || NULL == s->_pHead)
	{
		return;
	}
	if (pos == s->_pHead)
	{
		s->_pHead = pos->_pNext;
	}
	else
	{
		PNode pPrePos = s->_pHead;
		while (pPrePos && pPrePos->_pNext != pos) // �ҵ�posǰһ��
		{										  // �ж�pPrePos�Ƿ����, Ϊ�˷�ֹpos������s����һ������
			pPrePos = pPrePos->_pNext;
		}
		if (pPrePos)
		{
			pPrePos->_pNext = pos->_pNext;
		}
	}
	free(pos);
}

PNode SListFind(SList* s, SDataType data)
{
	assert(s);
	PNode pCur = s->_pHead;
	while (pCur)
	{
		if (pCur->_data == data)
		{
			return pCur;
		}
		pCur = pCur->_pNext;
	}
	return NULL;
}

// �Ƴ������е�һ��ֵΪdata��Ԫ��
void SListRemove(SList* s, SDataType data)
{
	assert(s);
	if (NULL == s->_pHead)
	{
		return;
	}
	PNode pCur = s->_pHead;
	PNode pPre = NULL;
	while (pCur)
	{
		if (pCur->_data == data)
		{
			if (pCur == s->_pHead)
			{
				s->_pHead->_pNext = pCur->_pNext;
			}
			else
			{
				pPre->_pNext = pCur->_pNext;
			}
			free(pCur);
			return;
		}
		else
		{
			pPre = pCur;
			pCur = pCur->_pNext;
		}
	}
}

void SListRemoveAll(SList* s, SDataType data)
{
	assert(s);
	if (NULL == s->_pHead)
	{
		return;
	}
	PNode pCur = s->_pHead;
	PNode pPre = NULL;
	while (pCur)
	{
		if (pCur->_data == data)
		{
			if (NULL == pPre)
			{
				s->_pHead->_pNext = pCur->_pNext;
				free(pCur);
				pCur = s->_pHead;
			}
			else
			{
				pPre->_pNext = pCur->_pNext;
				free(pCur);
				pCur = pPre->_pNext;
			}
		}
		else
		{
			pPre = pCur;
			pCur = pCur->_pNext;
		}
	}
}

size_t SListSize(SList* s)
{
	assert(s);
	size_t count = 0;
	PNode pCur = s->_pHead;
	while (pCur)
	{
		count++;
		pCur = pCur->_pNext;
	}
	return count;

}
int SListEmpty(SList* s)
{
	assert(s);
	return NULL == s->_pHead;
}

void PrintSList(SList* s)
{
	assert(s);
	PNode pCur = s->_pHead;
	while (pCur)
	{
		printf("%d--->", pCur->_data);
		pCur = pCur->_pNext;
	}
	printf("NULL\n");
}

void ReversePrint(PNode pHead)
{
	// ���������ӡ
	if (pHead)
	{
		ReversePrint(pHead->_pNext);
		printf("%d \n", pHead->_data);
	}
}


void TestSlist()
{
	SList s;
	SListInit(&s);
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);
	SListPushBack(&s, 4);
	SListPushBack(&s, 3);
	SListPushBack(&s, 3);
	ReversePrint(s._pHead);
	PrintSList(&s);

	SListDestory(&s);

}