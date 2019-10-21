#pragma once

typedef int HPDataType;

typedef int(*PCOM)(HPDataType, HPDataType);
int Less(HPDataType left, HPDataType right);	// 按小比较
int Greater(HPDataType left, HPDataType right);	// 按大比较

typedef struct Heap
{
	HPDataType* _array;
	int _capacity;
	int _size;
	PCOM compare;
}Heap;

void HeapInit(Heap* hp, HPDataType* array, int size, PCOM compare);
void HeapInitEmpty(Heap* hp, int capacity, PCOM compare);
void HeapInsert(Heap* hp, HPDataType data);
void HeapErase(Heap* hp);
int HeapSize(Heap* hp);
int HeapEmpty(Heap* hp);
HPDataType HeapTop(Heap* hp);
void HeapDestroy(Heap* hp);

void HeapSort(int* array, int size);


void test();