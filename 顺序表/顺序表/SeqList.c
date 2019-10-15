#include "SeqList.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>

void SeqListInit(PSeq ps, int capacity)
{
	ps->_array = (DataType*)malloc(sizeof(DataType) * capacity);
	if (NULL == ps->_array)
	{
		assert(ps);	// ֻ����debug�²Ż���Ч
		return;		// ֱ��return �Ժ�Ұָ��ᱻfree
	}
	ps->_capacity = capacity;
	ps->_size = 0;
}

void SeqListPushBack(PSeq ps, DataType data)
{
#if 0
	assert(ps);
	CheckCapacity(ps);

	ps->_array[ps->_size] = data;
	ps->_size++;
#endif
	SeqListInsert(ps, ps->_size, data);
}

void SeqListPopBack(PSeq ps)
{
#if 0
	assert(ps);
	if (SeqListEmpty(ps))
	{
		return;
	}
	ps->_size--;
#endif
	SeqListErase(ps, ps->_size - 1);
}

void SeqListPushFront(PSeq ps, DataType data)
{
#if 0
	assert(ps);
	CheckCapacity(ps);
	// ��˳����е�����Ԫ��ͳһ����ƶ�һλ
	for (int i = ps->_size - 1; i >= 0; i--)
	{
		ps->_array[i + 1] = ps->_array[i];
	}

	// ����Ԫ��
	ps->_array[0] = data;
	ps->_size++;
#endif
	SeqListInsert(ps, 0, data);
}

void SeqListPopFront(PSeq ps)
{
#if 0
	if (SeqListEmpty(ps))
	{
		return;
	}

	for (int i = 1; i < ps->_size; i++)
	{
		ps->_array[i - 1] = ps->_array[i];
	}
	ps->_size--;
#endif
	SeqListErase(ps, 0);
}

void SeqListInsert(PSeq ps, int pos, DataType data)
{
	assert(ps);
	if (pos < 0 || pos > ps->_size)
	{
		return;
	}

	CheckCapacity(ps);

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

int SeqListFind(PSeq ps, DataType data)
{
	assert(ps);

	for (int i = 0; i < ps->_size; ++i)
	{
		if (ps->_array[i] == data)
		{
			return i;
		}
	}
	return -1;
}
int SeqListSize(PSeq ps)
{
	assert(ps);
	return ps->_size;
}
int SeqListCapacity(PSeq ps)
{
	assert(ps);
	return ps->_capacity;
}

void SeqListClear(PSeq ps)
{
	assert(ps);
	ps->_size = 0;
}

void SeqListRemove(PSeq ps, DataType data)
{
	SeqListErase(ps, SeqListFind(ps, data));
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

void CheckCapacity(PSeq ps)
{
	assert(ps);
	if (ps->_size == ps->_capacity)
	{
		// ˳������Ѿ�û�пռ���
		// realloc(ps, size);
		int newCapacity = 2 * ps->_capacity;

		DataType* pTemp = (DataType*)malloc(newCapacity * sizeof(DataType));
		if (NULL == pTemp)
		{
			assert(pTemp);
			return;
		}
		//memcpy()
		for (int i = 0; i < ps->_size; ++i)
		{
			pTemp[i] = ps->_array[i];
		}

		free(ps->_array);
		ps->_array = pTemp;
		ps->_capacity = newCapacity;
	}
}

void SeqListModify(PSeq ps, int pos, DataType data)
{
	assert(ps);
	if (pos < 0 || pos > ps->_size - 1)
	{
		return;
	}
	ps->_array[pos] = data;
}

void SeqListPrint(PSeq ps)
{
	for (int i = 0; i < ps->_size; ++i)
	{
		printf("%d", ps->_array[i]);
	}
	printf("\n");
}

//////////////////////////////////////////

//�Ƴ�����ֵΪdata��Ԫ��
void SeqListRemoveAll(PSeq ps, DataType data)
{
#if 0
	int pos = -1;
	while (-1 != (pos = SeqListFind(ps, data)))
	{
		SeqListErase(ps, pos);
	}
	//ʱ�临�Ӷ�̫��
#endif
	// ����Ҫ��ʱ�临�Ӷȣ�O(N) �ռ临�Ӷ� O(1) 
	assert(ps);
	int count = 0;	// ��ǰλ��ǰ��յĸ���
	for (int i = 0; i < ps->_size; ++i)
	{
		if (data == ps->_array[i])
		{
			++count;
		}
		else
		{
			ps->_array[i - count] = ps->_array[i];
		}
	}
	ps->_size -= count;
}

void SeqListBubbleSort(PSeq ps)
{
	DataType tmp;
	for (int i = 0; i < ps->_size - 1; ++i)
	{
		for (int j = 0; j < ps->_size - 1 - i; ++j)
		{
			if (ps->_array[j] > ps->_array[j + 1])
			{
				tmp = ps->_array[j];
				ps->_array[j] = ps->_array[j + 1];
				ps->_array[j + 1] = tmp;
			}
		}
	}
}