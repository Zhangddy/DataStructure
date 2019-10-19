#pragma once

typedef int SDataType;

typedef struct Stack
{
	SDataType* _array;
	int _capacity;
	int _size;	// Ԫ�ظ���, ���һ��Ԫ����һ����λ��
}Stack;

void StackInit(Stack* ps);
void StackPush(Stack* ps, SDataType data);
void StackPop(Stack* ps);
SDataType StackTop(Stack* ps);
int StackSize(Stack* ps);
int StackEmpty(Stack* ps);
void StackDestroy(Stack* ps);