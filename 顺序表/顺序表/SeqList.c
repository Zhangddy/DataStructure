#include "SeqList.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>

void SeqListInit(PSeq ps, int capacity)
{
	ps->_array = (DataType*)malloc(sizeof(DataType) * capacity);
	if (NULL == ps->_array)
	{
		assert(ps);	// 只会在debug下才会有效
		return;		// 直接return 以后野指针会被free
	}
	ps->_capacity = 0;
	ps->_size = 0;
}

void SeqListPushBack(PSeq ps, DataType data)
{
	assert(ps);
	//CheckCapacity(ps);

	ps->_array[ps->_size] = data;
	ps->_size++;
}

void SeqListPopBack(PSeq ps)
{
	assert(ps);
	if (SeqListEmpty(ps))
	{
		return;
	}
	ps->_size--;
}

void SeqListPushFront(PSeq ps, DataType data)
{
	assert(ps);
	// CheckCapacity(ps);
	// 将顺序表中的所有元素统一向后移动一位
	for (int i = ps->_size - 1; i >= 0; i--)
	{
		ps->_array[i + 1] = ps->_array[i];
	}

	// 插入元素
	ps->_array[0] = data;
	ps->_size++;
}

void SeqListPopFront(PSeq ps)
{
	if (SeqListEmpty(ps))
	{
		return;
	}

	for (int i = 1; i < ps->_size; i++)
	{
		ps->_array[i - 1] = ps->_array[i];
	}
	ps->_size--;
}

void SeqListInsert(PSeq ps, int pos, DataType data)
{
	assert(ps);
	if (pos < 0 || pos > ps->_size)
	{
		return;
	}

	// CheckCapacity(ps);

	for (int i = ps->_size - 1; i >= pos; i--)
	{
		ps->_array[i + 1] = ps->_array[i];
	}

	ps->_array[pos] = data;
	ps->_size++;
}

void SeqListErase(PSeq ps, int pos)
{
	assert(ps);
	if (pos < 0 || pos >= ps->_size)
	{
		return;
	}

	for (int i = pos + 1; i < ps->_size; ++i)
	{
		ps->_array[i - 1] = ps->_array[i];
	}
	ps->_size--;
}

int SeqListEmpty(PSeq ps)
{
	assert(ps);
	return 0 == ps->_size;
}


void SeqListDestroy(PSeq ps)
{
	if (ps->_array)
	{
		free(ps->_array);
		ps->_array = NULL;
		ps->_capacity = 0;
		ps->_size = 0;
	}
}

void SeqListPrint(PSeq ps)
{
	for (int i = 0; i < ps->_size; ++i)
	{
		printf("%d", ps->_array[i]);
	}
	printf("\n");
}