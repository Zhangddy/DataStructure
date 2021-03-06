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

// parent为要调整的节点
void AdjustDown(HPDataType* array, int size, int parent)
{
	// 默认让child标记parent的左孩子, 
	// 因为: 完全二叉树某个节点如果只有一个孩子, 该孩子一定是其双亲的左孩子
	int child = parent * 2 + 1;
	while (child < size)
	{
		// 找双亲孩子中较小的孩子 交换
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

// 所有元素按完全二叉树的顺序存储方式存储 在一个一维数组中
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

	// 堆的特性: 堆中某个节点的值总是不大于或不小于其父节点的值还不满足
	// 进行调整
	// 向下调整---创建堆的关键一步
	// 向下调整算法有一个前提：左右子树必须是一个堆，才能调整

	// 找完全二叉树中倒数第一个非叶子节点, 从此向上把每一个节点下的都调整成堆
	// 一直到跟节点
	int root = (size - 2) >> 1; // 最后一个节点下标为size - 1; 其双亲节点为 (k - 1) /2
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

// 应该删除堆顶的, 因为堆顶不是最大的就是最小的
// 堆顶与最后一个交换, size--, 再来一次向下调整算法
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
	// 1.建立堆, 如果是升序建大堆, 降序建小堆

	int root = ((size - 2) >> 1);
	for (; root >= 0; --root)
	{
		HeapAdjust(array, size, root);
	}

	// 2. 排序, 用堆删除的思想

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