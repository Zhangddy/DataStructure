#pragma once
// 顺序表结构:
// 数组
// 静态顺序表: 
#if 0
typedef int DataType;
#define MAX_SIZE 100

struct SeqList
{
	DataType _array[MAX_SIZE];	// 用来存储顺序表中的元素
	size_t _size;	// 顺序表中有效空间的个数
};
#endif

// 动态的顺序表
typedef int DataType;

typedef struct SeqList
{
	DataType* _array;
	int _capacity;	// 顺序表的总大小
	int _size;		// 顺序表中有效元素的个数
}SeqList, *PSeq;

void SeqListInit(PSeq ps, int capacity);
void SeqListPushBack(PSeq ps, DataType data);
void SeqListPopBack(PSeq ps);
void SeqListPushFront(PSeq ps, DataType data);
void SeqListPopFront(PSeq ps);
void SeqListInsert(PSeq ps, int pos, DataType data);
void SeqListErase(PSeq ps, int pos);
int SeqListFind(PSeq ps, DataType data);
int SeqListSize(PSeq ps);
int SeqListCapacity(PSeq ps);
void SeqListClear(PSeq ps);
void SeqListRemove(PSeq ps, DataType data);
int SeqListEmpty(PSeq ps);
void SeqListDestroy(PSeq ps);
void CheckCapacity(PSeq ps);
void SeqListModify(PSeq ps, int pos, DataType data);
void SeqListPrint(PSeq ps);

/////////////////////////////////////
//常见的一些附加功能
void SeqListRemoveAll(PSeq ps, DataType data);
void SeqListBubbleSort(PSeq ps);