#pragma once

typedef int HPDataType;

typedef struct Heap
{
	HPDataType* _array;
	int _capacity;
	int _size;
}Heap;
// ”ÎÀ≥–Ú±Ìœ‡À∆

void HeapInit(Heap* hp, HPDataType* array, int size);
void HeapInsert(Heap* hp, HPDataType data);
void HeapErase(Heap* hp);
int HeapSize(Heap* hp);
int HeapEmpty(Heap* hp);
HPDataType HeapTop(Heap* hp);
void HeapDestroy(Heap* hp);

void HeapSort(int* array, int size);


void test();
