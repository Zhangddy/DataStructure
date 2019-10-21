#include "heap.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>

void swap(HPDataType* child, HPDataType* parent)
{
	HPDataType tmp;
	tmp = *child;
	*child = *parent;
	*parent = tmp;
}

// parentΪҪ�����Ľڵ�
void AdjustDown(HPDataType* array, int size, int parent)
{
	// Ĭ����child���parent������, 
	// ��Ϊ: ��ȫ������ĳ���ڵ����ֻ��һ������, �ú���һ������˫�׵�����
	int child = parent * 2 + 1;
	while (child < size)
	{
		// ��˫�׺����н�С�ĺ��� ����
		if (child + 1 < size && array[child] > array[child + 1])
		{
			child++;
		}

		if (array[child] < array[parent])
		{
			swap(&array[child], &array[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			return;
		}
	}
}

// ����Ԫ�ذ���ȫ��������˳��洢��ʽ�洢 ��һ��һά������
void HeapInit(Heap* hp, HPDataType* array, int size)
{
	assert(hp);
	hp->_array = (HPDataType*)malloc(sizeof(HPDataType) * size);
	if (NULL == hp->_array)
	{
		assert(0);
		return;
	}
	hp->_capacity = size;
	for (int i = 0; i < size; ++i)
	{
		hp->_array[i] = array[i];
	}
	hp->_size = size;

	// �ѵ�����: ����ĳ���ڵ��ֵ���ǲ����ڻ�С���丸�ڵ��ֵ��������
	// ���е���
	// ���µ���---�����ѵĹؼ�һ��
	// ���µ����㷨��һ��ǰ�᣺��������������һ���ѣ����ܵ���

	// ����ȫ�������е�����һ����Ҷ�ӽڵ�, �Ӵ����ϰ�ÿһ���ڵ��µĶ������ɶ�
	// һֱ�����ڵ�
	int root = (size - 2) >> 1; // ���һ���ڵ��±�Ϊsize - 1; ��˫�׽ڵ�Ϊ (k - 1) /2
	for (; root >= 0; --root)
	{
		AdjustDown(hp->_array, size, root);
	}	
}

void AdjustUP(HPDataType* array, int size, int child)
{
	int parent = (child - 1) / 2;
	while (child)
	{
		if (array[parent] > array[child])
		{
			swap(&array[parent], &array[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			return;
		}
	}
}

void CheakCapacity(Heap* hp)
{
	assert(hp);
	if (hp->_size == hp->_capacity)
	{
		int newCapacity = 2 * hp->_capacity;
		HPDataType* pTemp = (HPDataType*)malloc(sizeof(HPDataType) * newCapacity);
		if (NULL == pTemp)
		{
			assert(0);
			return;
		}
		hp->_capacity = newCapacity;
		for (int i = 0; i < hp->_size; ++i)
		{
			pTemp[i] = hp->_array[i];
		}
		free(hp->_array);
		hp->_array = pTemp;
	}
}

void HeapInsert(Heap* hp, HPDataType data)
{
	assert(hp);
	CheakCapacity(hp);
	hp->_array[hp->_size] = data;
	hp->_size++;
	AdjustUP(hp->_array, hp->_size, hp->_size - 1);
}

// Ӧ��ɾ���Ѷ���, ��Ϊ�Ѷ��������ľ�����С��
// �Ѷ������һ������, size--, ����һ�����µ����㷨
void HeapErase(Heap* hp)
{
	assert(hp);
	if (HeapEmpty(hp))
	{
		return;
	}
	swap(&hp->_array[0], &hp->_array[hp->_size - 1]);
	hp->_size -= 1;
	AdjustDown(hp->_array, hp->_size, 0);
}

int HeapSize(Heap* hp)
{
	assert(hp);
	return hp->_size;
}

int HeapEmpty(Heap* hp)
{
	assert(hp);
	return 0 == hp->_size;
}

HPDataType HeapTop(Heap* hp)
{
	assert(hp);
	return hp->_array[0];
}

void HeapDestroy(Heap* hp)
{
	assert(hp);
	if (hp->_array)
	{
		free(hp->_array);
		hp->_array = NULL;
		hp->_size = hp->_capacity = 0;
	}
}

void HeapAdjust(int* array, int size, int parent)
{
	int child = parent * 2 + 1;
	
	while (child < size)
	{
		if (child + 1 < size && array[child] < array[child + 1])
		{
			child += 1;
		}
		if (array[child] > array[parent])
		{
			swap(&array[child], &array[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			return;
		}
	}
}

void HeapSort(int* array, int size)
{
	// 1.������, ��������򽨴��, ����С��

	int root = ((size - 2) >> 1);
	for (; root >= 0; --root)
	{
		HeapAdjust(array, size, root);
	}

	// 2. ����, �ö�ɾ����˼��

	int end = size - 1;
	while (end)
	{
		swap(&array[0], &array[end]);
		HeapAdjust(array, end, 0);
		end--;
	}
}

void test()
{
	Heap h;
	int a[] = { 2,3,8,0,9,1,7,4,6,5 };
	//HeapInit(&h, a, sizeof(a) / sizeof(a[0]));

	//printf("% d , %d \n", HeapSize(&h), HeapTop(&h));
	//HeapInsert(&h, 0);
	//printf("% d , %d \n", HeapSize(&h), HeapTop(&h));
	//HeapDestroy(&h);
	HeapSort(a, sizeof(a) / sizeof(a[0]));
}