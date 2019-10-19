#include "Stack.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>

void StackInit(Stack* ps)
{
	assert(ps);
	ps->_array = (SDataType*)malloc(3 * sizeof(SDataType));
	if (NULL == ps->_array)
	{
		assert(0);
		return;
	}
	ps->_size = 0;
	ps->_capacity = 3;
}

void CheckCapacity(Stack* ps)
{
	assert(ps);
	if (ps->_size == ps->_capacity)
	{
		int newCapacity = ps->_capacity * 2;
		SDataType* pTemp = (SDataType*)malloc(newCapacity * sizeof(SDataType));
		if (NULL == pTemp)
		{
			assert(0);
			return;
		}
		for (int i = 0; i < ps->_size; ++i)
		{
			pTemp[i] = ps->_array[i];
		}
		free(ps->_array);
		ps->_array = pTemp;
		ps->_capacity = newCapacity;
	}
}

void StackPush(Stack* ps, SDataType data)
{
	assert(ps);
	CheckCapacity(ps);
	ps->_array[ps->_size++] = data;
}

void StackPop(Stack* ps)
{
	assert(ps);
	if (StackEmpty(ps))
	{
		return;
	}
	else
	{
		ps->_size--;
	}
}

SDataType StackTop(Stack* ps)
{
	assert(ps);
	return ps->_array[ps->_size - 1];
}

int StackSize(Stack* ps)
{
	assert(ps);
	return ps->_size;
}

int StackEmpty(Stack* ps)
{
	assert(ps);
	return ps->_size == 0;
}

void StackDestroy(Stack* ps) 
{
	assert(ps);
	if (ps->_array)
	{
		free(ps->_array);
		ps->_capacity = 0;
		ps->_size = 0;
		ps->_array = NULL;
	}
}



void test()
{
	Stack s;
	StackInit(&s);
	StackPush(&s, 1);
	StackPush(&s, 2);
	StackPush(&s, 3);
	printf("%d ,%d", StackSize(&s), StackTop(&s));
	StackPush(&s, 1);
	StackPush(&s, 2);
	StackPop(&s);
	StackPop(&s);
	StackPop(&s);
	StackPop(&s);

	printf(",%d ,%d", StackSize(&s), StackTop(&s));

	StackDestroy(&s);
}